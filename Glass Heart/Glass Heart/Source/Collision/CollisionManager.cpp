
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
VECTOR GlassHeart::Collision::CollisionManager::CheckTerrain(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("TestStage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0, 0, 0 });
    auto end = VAdd(newPos, { 0, -10, 0 });
    _mcrp = MV1CollCheck_Line(handle, 4, start, end);

    if (_mcrp.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    if (_mcrp.HitFlag == 1) {
        // 衝突あれば移動する
        newPos = _mcrp.HitPosition;
    }
   
    return  newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckJumpStand(const VECTOR& pos, const VECTOR& forward) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("TestStage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0, 30, 0 });
    auto end = VAdd(newPos, { 0, -100, 0 });
    _stand = MV1CollCheck_Line(handle, 4, start, end);

    if (_stand.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    if (_stand.HitFlag == 1)  {
        // 衝突あれば移動する
        newPos = _stand.HitPosition;
    }

    return  newPos;
}
/** 壁との当たり判定 */
VECTOR GlassHeart::Collision::CollisionManager::CheckHitWall(const VECTOR& pos, const VECTOR& forward) {

    auto wall = 7;
    auto round = 6.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("TestStage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { -8.f, 0.f, 0.f });
    auto c2 = VAdd(newPos, { -8.f, 0.f, 0.f });
    _collpol = MV1CollCheck_Capsule(handle, wall, c1, c2, round);

    if (_collpol.HitNum == 0) {
        // 衝突無し
        return pos;
    }
    if (_collpol.HitNum >= 1) {
        // 衝突有り 押し戻す
        newPos = VSub(pos, forward);
    }

#ifdef _DEBUG
    _debugNum1 = c1;
    _debugNum2 = c2;
#endif // _DEBUG

    return newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckHitCeiling(const VECTOR& pos, const VECTOR& forward) {

    auto round = 4.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Teststage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 10.f, 40.f, 5.f });
    auto end = VAdd(newPos, { 10.f, -10.f, 5.f });
    _ceiling = MV1CollCheck_Line(handle, 7, start, end);

    if (_ceiling.HitFlag == 0) {
        return pos;
    }
    if (_ceiling.HitFlag == 1) {
        newPos = _ceiling.HitPosition;
    }

    return newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckHitDeathFloor(const VECTOR& pos, const VECTOR& forward) {

    auto round = 6.5f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("TestStage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { -8.f, 0.f, 0 });
    auto end = VAdd(newPos, { -8.f, 0.f, 0 });
    _death = MV1CollCheck_Capsule(handle, 8, start, end, round);

    if(_death.HitNum == 0) {
        // 衝突なし移動しない
        return pos;
    }
    else if (_death.HitNum >= 1) {
    // 衝突あれば移動する
        newPos = VSub(pos, forward);
    }

    return  newPos;
}
/** デバッグ用当たり判定表示 */
void GlassHeart::Collision::CollisionManager::Render(){
    DrawCapsule3D(_debugNum1, _debugNum2, 0.5f, 10, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
}

