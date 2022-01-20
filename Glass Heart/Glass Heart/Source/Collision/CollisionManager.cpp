
/*****************************************************************//**
 * @file   CollisionManager.cpp
 * @brief  �R���W�����}�l�[�W���[�N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "CollisionManager.h"
#include "../Object/ObjectBase.h"
#include "../Object/ObjectServer.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include <AppFrame.h>

using namespace GlassHeart::Collision;

Sphere::Sphere(const VECTOR& center, float radius)
    :center(center)
    , radius(radius) {
}

bool Sphere::Contains(const VECTOR& point) const {
    auto distSq = VSquareSize(VSub(center, point));
    return distSq <= (radius * radius);
}

bool GlassHeart::Collision::Intersect(const Sphere& a, const Sphere& b)
{
    auto distSq = VSquareSize(VSub(a.center, b.center));
    float sumRadii = a.radius + b.radius;
    return distSq <= (sumRadii * sumRadii);
}


CollisionManager::CollisionManager(GlassHeart::Object::ObjectBase& owner) : _owner{ owner } {
    _report = std::make_unique<Report>();
}

void CollisionManager::EnemyFromPlayer() {
    // �E��̃t���[��(28��)�̈ʒu�ɋ���ݒ�
    auto handle = _owner.GetModelAnime().GetHandle();
    auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
    auto pos = VTransform({ 0, 0, 0 }, mat);
    auto playerSphere = Sphere(pos, 20);

    for (auto&& obj : _owner.GetObjectServer().GetObjectLists()) {
        if (obj->GetObjectType() != GlassHeart::Object::ObjectBase::ObjectType::Enemy) {
            continue;
        }
        if (obj->GetCollision().GetReport().id == ReportId::HitFromPlayer) {
            continue;
        }
        // �G�l�~�[���̋���ݒ�
        auto enemySphere = Sphere(obj->GetPosition(), 50);
        enemySphere.center.y += 40; //�@������Ȃ̂Œ��S��40�グ��
        // ���Ƌ��̏Փ˔���
        if (Intersect(playerSphere, enemySphere)) {
            obj->GetCollision().SetReport({ ReportId::HitFromPlayer, _owner.GetPosition() });
        }
    }
}

void CollisionManager::PlayerFromEnemy() {
    // ��̃t���[��(28��)�̈ʒu�ɋ���ݒ�
    auto handle = _owner.GetModelAnime().GetHandle();
    auto mat = MV1GetFrameLocalWorldMatrix(handle, 28);
    auto pos = VTransform({ 0, 0, 0 }, mat);
    auto enemySphere = Sphere(pos, 20);

    for (auto&& obj : _owner.GetObjectServer().GetObjectLists()) {

        if (obj->GetObjectType() != GlassHeart::Object::ObjectBase::ObjectType::Player) {
            continue;
        }
        if (obj->GetCollision().GetReport().id == ReportId::HitFromEnemy) {
            continue;
        }
        auto playerSphere = Sphere(obj->GetPosition(), 50);
        playerSphere.center.y += 40;   //�@������Ȃ̂Œ��S��40�グ��
        if (Intersect(enemySphere, playerSphere)) {
            obj->GetCollision().SetReport({ ReportId::HitFromEnemy, _owner.GetPosition() });
        }
    }
}
VECTOR CollisionManager::CheckTerrain(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Test");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0, 100, 0 });
    auto end = VAdd(newPos, { 0, -10000, 0 });
    _mcrp = MV1CollCheck_Line(handle, 1, start, end);

    if (_mcrp.HitFlag == 0) {
        // �Փ˂Ȃ��ړ����Ȃ�
        return pos;
    }
    // �Փ˂���Έړ�����
    newPos = _mcrp.HitPosition;
    return  newPos;
}

