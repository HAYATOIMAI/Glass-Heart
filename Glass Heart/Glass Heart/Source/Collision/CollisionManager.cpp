
/*********************************************************************
 * @file   CollisionManager.cpp
 * @brief  コリジョンマネージャークラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "CollisionManager.h"
#include "../Object/ObjectBase.h"
#include "../Object/ObjectServer.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include <AppFrame.h>
/** 球体の当たり判定 */
GlassHeart::Collision::Sphere::Sphere(const VECTOR& center, float radius)
    :center(center)
    , radius(radius) {
}

bool GlassHeart::Collision::Sphere::Contains(const VECTOR& point) const {
    auto distSq = VSquareSize(VSub(center, point));
    return distSq <= (radius * radius);
}

bool GlassHeart::Collision::Intersect(const Sphere& a, const Sphere& b)
{
    auto distSq = VSquareSize(VSub(a.center, b.center));
    float sumRadii = a.radius + b.radius;
    return distSq <= (sumRadii * sumRadii);
}
/** コンストラクタ */
GlassHeart::Collision::CollisionManager::CollisionManager(GlassHeart::Object::ObjectBase& owner) : _owner{ owner } {
    _report = std::make_unique<Report>();
}
/** 床との当たり判定 */
VECTOR GlassHeart::Collision::CollisionManager::CheckHitFloor(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0, 10, 0 });
    auto end = VAdd(newPos, { 0, -100, 0 });
    _mcrp = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);

    if (_mcrp.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    else if (_mcrp.HitFlag == 1) {
        // 衝突あれば移動する
        newPos = _mcrp.HitPosition;
    }
   
    return  newPos;
}
// 空中の足場との当たり判定
VECTOR GlassHeart::Collision::CollisionManager::CheckJumpStand(const VECTOR& pos, const VECTOR& forward) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -200.f, 0.f });
    _stand = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);

    if (_stand.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    else if (_stand.HitFlag == 1)  {
        // 衝突あれば移動する
        newPos = _stand.HitPosition;
    }

    return  newPos;
}
/** 壁との当たり判定 */
VECTOR GlassHeart::Collision::CollisionManager::CheckHitWall(const VECTOR& pos, const VECTOR& forward) {
    auto round = 10.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { -8.f, 10.f, 0.f });
    auto c2 = VAdd(newPos, { -18.f, 20.f, 0.f });
    _collpol = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "Wall_NavMesh"), c1, c2, round);

    if (_collpol.HitNum == 0) {
        // 衝突無し
        return pos;
    }
    else if (_collpol.HitNum >= 1) {
        // 衝突有り 押し戻す
        newPos = VSub(pos, forward);
    }

    return newPos;
}
/**  底面や側面との当たり判定 */
VECTOR GlassHeart::Collision::CollisionManager::CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward) {

    auto round = 6.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { -8.f, 40.f, 0.f });
    auto c2 = VAdd(newPos, { -8.f, 120.f, 0.f });
    _sideBottom = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "Wall_NavMesh"), c1, c2, round);

    if (_sideBottom .HitNum == 0) {
        return pos;
    }
    else if (_sideBottom.HitNum >= 1) {
       newPos = VSub(pos, forward);
    }

    return newPos;
}
/** 白色の壁との当たり判定 */
VECTOR GlassHeart::Collision::CollisionManager::CheckThroughWMesh(const VECTOR& pos, const VECTOR& forward) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -200.f, 0.f });
    _wThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "WThroughFloor_NavMesh"), start, end);

    if (_wThrough.HitFlag == 0) {
        // 衝突無し
        return pos;
    }
    else if (_wThrough.HitFlag == 1) {
        // 衝突あれば移動する
        newPos = _wThrough.HitPosition;
    }

    return newPos;
}

VECTOR GlassHeart::Collision::CollisionManager::CheckHitDeathFloor(const VECTOR& pos, const VECTOR& forward) {

    //auto round = 6.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto c2 = VAdd(newPos, { 0.f, -100.f, 0.f });
    _death = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Death_Mesh"), c1, c2);

    if(_death.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    else if (_death.HitFlag == 1) {
    // 衝突あれば移動する
        newPos = _death.HitPosition;
    }

    return  newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckThroughBMesh(const VECTOR& pos, const VECTOR& forward) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _bThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "BThroughFloor_NavMesh"), start, end);

    if (_bThrough.HitFlag == 0) {
        return pos;
    }
    else  if (_bThrough.HitFlag == 1) {
        newPos = _bThrough.HitPosition;
    }

    return newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckThroughWWallMesh(const VECTOR& pos, const VECTOR& forward) {

    auto round = 6.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { -8.f, 40.f, 0.f });
    auto c2 = VAdd(newPos, { -8.f, 120.f, 0.f });
    _wWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "WThroughWall_NavMesh"), c1, c2, round);

    if (_wWallThrough.HitNum == 0) {
        // 衝突無し
        return pos;
    }
    else if (_wWallThrough.HitNum >= 1) {
        // 衝突有り 押し戻す
        newPos = VSub(pos, forward);
    }

    return newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckThroughBWallMesh(const VECTOR& pos, const VECTOR& forward) {

    auto round = 6.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { -8.f, 40.f, 0.f });
    auto c2 = VAdd(newPos, { -8.f, 120.f, 0.f });
    _bWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "BThroughWall_NavMesh"), c1, c2, round);

    if (_bWallThrough.HitNum == 0) {
        return pos;
    }
    else if (_bWallThrough.HitNum >= 1) {
        // 衝突有り 押し戻す
        newPos = VSub(pos, forward);
    }

    return newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckPlayerCapsule(const VECTOR& pos, const VECTOR& forward) {

    auto round = 106.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Player");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { 100.f, pos.y, 200.f });
    auto c2 = VAdd(newPos, { 100.f, pos.y -100.f, 200.f });
    _playercap = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "CollisionNavMesh"), c1, c2, round);

    if (_playercap.HitNum == 0)  {
        return pos;
    }
    else if (_playercap.HitNum >= 1) {
        newPos = VSub(pos, forward);
    }

    return  newPos;
}
void GlassHeart::Collision::CollisionManager::RenderCircle(const VECTOR circlePos, float range, int red, int green, int blue) {
    for (float i = 0.0; i < 360.0; i++) {

        float radian = DX_PI / 180 * i;
        float x = range * std::cos(radian);
        float z = range * std::sin(radian);

        VECTOR move = { x, 0.0f, z };

        VECTOR newPos = VAdd(circlePos, move);
        DrawPixel3D(newPos, GetColor(red, green, blue));

    }
}
bool GlassHeart::Collision::CollisionManager::CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target)  {
    _radius1 = owner.GetRadius();
    _radius2 = target.GetRadius();

    auto differVec = VSub(target.GetPosition(), owner.GetPosition());

    auto length = sqrt(differVec.x * differVec.x + differVec.z * differVec.z);

    if (length < _radius1 + _radius2) {

        return true;

    }

    return false;
}
/** デバッグ用当たり判定表示 */
void GlassHeart::Collision::CollisionManager::Render(){
    DrawCapsule3D(_debugNum1, _debugNum2, 0.5f, 10, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
}

