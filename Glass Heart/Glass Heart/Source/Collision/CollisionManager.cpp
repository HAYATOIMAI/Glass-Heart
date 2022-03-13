
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

using namespace GlassHeart;

/** コンストラクタ */
Collision::CollisionManager::CollisionManager(Object::ObjectBase& owner) : _owner{ owner } {}
/** 床との当たり判定 */
VECTOR Collision::CollisionManager::CheckHitFloor(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _floor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);
  
    if (_floor.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    else if (_floor.HitFlag == 1) {
        // 衝突あれば移動する
        newPos = _floor.HitPosition;
    }
   
    return  newPos;
}
// 空中の足場との当たり判定
VECTOR Collision::CollisionManager::CheckJumpStand(const VECTOR& pos, const VECTOR& forward) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
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
/**  底面や側面との当たり判定 */
VECTOR Collision::CollisionManager::CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward) {

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
VECTOR Collision::CollisionManager::CheckThroughWMesh(const VECTOR& pos, const VECTOR& forward) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
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

VECTOR Collision::CollisionManager::CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward) {

    auto round = 13.0f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { -18.f, 15.f, 0.f });
    auto c2 = VAdd(newPos, { -18.f, 42.f, 0.f });
    _wDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "WDeath_NavMesh"), c1, c2,round);

    if (_wDeath.HitNum == 0) {
        // 衝突なし移動しない
        return pos;
}
    else if (_wDeath.HitNum >= 1) {
        // 衝突あれば移動する
        newPos = VSub(pos, forward);
    }
    return  newPos;
}
VECTOR Collision::CollisionManager::CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward) {

    auto round = 13.0f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { -18.f, 42.f, 0.f });
    auto c2 = VAdd(newPos, { -18.f, 42.f, 0.f });
    /*auto c1 = VAdd(newPos, { -8.f, 10.f, 0.f });
    auto c2 = VAdd(newPos, { -18.f, 20.f, 0.f });*/
    _bDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "BDeath_NavMesh"), c1, c2, round);

    if (_bDeath.HitNum == 0) {
        return pos;
    }
    else if (_bDeath.HitNum >= 1) {
        // 衝突あれば移動する
        newPos = VSub(pos, forward);
    }
    return newPos;
}
VECTOR Collision::CollisionManager::CheckThroughBMesh(const VECTOR& pos, const VECTOR& forward) {

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
VECTOR Collision::CollisionManager::CheckThroughWWallMesh(const VECTOR& pos, const VECTOR& forward) {

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
VECTOR Collision::CollisionManager::CheckThroughBWallMesh(const VECTOR& pos, const VECTOR& forward) {

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
VECTOR Collision::CollisionManager::CheckFall(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _fall = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);

    if (_fall.HitFlag == 0) {
        newPos = VAdd(pos, forward);
    }
    else if (_fall.HitFlag == 1) {
        newPos = _fall.HitPosition;
    }
    return newPos;
}

void GlassHeart::Collision::CollisionManager::RenderCircle(const VECTOR circlePos, float range, unsigned int color) {
    for (float i = 0.0f; i < 360.0f; i++) {

        float radian = DX_PI_F / 180 * i;
        float x = range * std::cos(radian);
        float z = range * std::sin(radian);

        VECTOR move = { x, 0.0f, z };

        VECTOR newPos = VAdd(circlePos, move);
        DrawPixel3D(newPos, color);

    }
}
bool Collision::CollisionManager::CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target)  {
    _radius1 = owner.GetRadius();
    _radius2 = target.GetRadius();

    auto differVec = VSub(target.GetPosition(), owner.GetPosition());

    auto length = sqrt(differVec.x * differVec.x + differVec.z * differVec.z);

    if (length < _radius1 + _radius2) {

        return true;

    }

    return false;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckHitSecondFloor(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage2");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _secondFloor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);

    if (_secondFloor.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    else if (_secondFloor.HitFlag == 1) {
        // 衝突あれば移動する
        newPos = _secondFloor.HitPosition;
    }

    return  newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckHitSecondJumpStand(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage2");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _seconsdStand = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);

    if (_seconsdStand.HitFlag == 0) {
        // 衝突なし移動しない
        return pos;
    }
    else if (_seconsdStand.HitFlag == 1) {
        // 衝突あれば移動する
        newPos = _seconsdStand.HitPosition;
    }

    return  newPos;
}
VECTOR GlassHeart::Collision::CollisionManager::CheckHitSecondFall(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage2");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _secondFall = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);

    if (_secondFall.HitFlag == 0) {
        newPos = VAdd(pos, forward);
    }
    else if (_secondFall.HitFlag == 1) {
        newPos = _secondFall.HitPosition;
    }
    return newPos;
}

VECTOR GlassHeart::Collision::CollisionManager::CheckHitSecondThroughWMesh(const VECTOR& pos, const VECTOR& forward) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage2");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _secondWThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "BThroughFloor_NavMesh"), start, end);

    if (_secondWThrough.HitFlag == 0) {
        return pos;
    }
    else if (_secondWThrough.HitFlag == 1) {
        newPos = _secondWThrough.HitPosition;
    }
    return newPos;
}

VECTOR GlassHeart::Collision::CollisionManager::CheckHitSecondThroughBMesh(const VECTOR& pos, const VECTOR& forward) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage2");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(newPos, { 0.f, 10.f, 0.f });
    auto end = VAdd(newPos, { 0.f, -100.f, 0.f });
    _secondBThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "WThroughFloor_NavMesh"), start, end);

    if (_secondBThrough.HitFlag == 0) {
        return pos;
    }
    else if (_secondBThrough.HitFlag == 1) {
        newPos = _secondBThrough.HitPosition;
    }
    return newPos;
}
