
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
VECTOR Collision::CollisionManager::CheckHitFloor(const VECTOR& pos, const VECTOR& forward, int state) {
    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(pos, { 0.f, 1.f, 0.f });
    auto end = VAdd(pos, { 0.f, forward.y, 0.f });
    // 色によって判定するメッシュを変更
    switch (state) {
    case 0:
        _bThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "BThroughFloor_NavMesh"), start, end);
        if (_bThrough.HitFlag == 1) {
            // 当たっていたら位置を返す
            return pos;
        }
        _floor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);
        break;
    case 1:
        _wThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "WThroughFloor_NavMesh"), start, end);
        if (_wThrough.HitFlag == 1) {
            // 当たっていたら位置を返す
            return pos;
        }
        _floor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);
        break;
    default:
        break;
    }

    if (_floor.HitFlag == 0) {
        // 衝突なし
        return newPos;
    }
    // 当たっていたら位置を返す
    return  pos;

}
// 空中の足場との当たり判定
VECTOR Collision::CollisionManager::CheckJumpStand(const VECTOR& pos, const VECTOR& forward, int state) {

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto start = VAdd(pos, { 0.f, 0.f, 0.f });
    auto end = VAdd(pos, { 0.f, forward.y, 0.f });
     // 色によって判定するメッシュを変更
    switch (state) {
    case 0:
        _bThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "BThroughFloor_NavMesh"), start, end);

        if (_bThrough.HitFlag == 0) {
            // 衝突なし
        }
        else if (_bThrough.HitFlag == 1) {
            // 衝突あれば当たった位置に移動
            newPos = _bThrough.HitPosition;
        }
        _stand = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);
        break;
    case 1:
        _wThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "WThroughFloor_NavMesh"), start, end);
        if (_wThrough.HitFlag == 0) {
            // 衝突なし
        }
        else if (_wThrough.HitFlag == 1) {
            // 衝突あれば当たった位置に移動
            newPos = _wThrough.HitPosition;
        }
        _stand = MV1CollCheck_Line(handle, MV1SearchFrame(handle, "Floor_NavMesh"), start, end);
        break;
    default:
        break;
    }
    if (_stand.HitFlag == 0) {
        // 衝突なし
        return newPos;
    }
    else if (_stand.HitFlag == 1) {
        // 衝突あれば当たった位置に移動
        newPos = _stand.HitPosition;
    }

    return  newPos;
}
/**  底面や側面との当たり判定 */
VECTOR Collision::CollisionManager::CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, int state) {

    auto round = 20.0f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { 0.f, 140.f - round,0.f });
    auto c2 = VAdd(newPos, { 0.f, 1.f + round, 0.f });
    // 色によって判定するメッシュを変更
    switch (state) {
    case 0:
        _bWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "BThroughWall_NavMesh"), c1, c2, round);
        // 当たっていたら位置ベクトルを返す
        if (_bWallThrough.HitNum > 0) {
            return pos;
        }

        _sideBottom = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "Wall_NavMesh"), c1, c2, round);
        break;
    case 1:
        _wWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "WThroughWall_NavMesh"), c1, c2, round);
        // 当たっていたら位置ベクトルを返す
        if (_wWallThrough.HitNum > 0) {
            return pos;
        }

        _sideBottom = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "Wall_NavMesh"), c1, c2, round);
        break;
    default:
        break;
    }
    // 衝突無し
    if (_sideBottom.HitNum == 0) {
        return newPos;
    }
    return pos;
}
/** 白いデスメッシュとの当たり判定 */
VECTOR Collision::CollisionManager::CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward) {

    auto round = 20.0f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { 0.f, 140.f,0.f });
    auto c2 = VAdd(newPos, { 0.f, 1.f, 0.f });
    _wDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "WDeath_NavMesh"), c1, c2,round);

    if (_wDeath.HitNum == 0) {
        // 衝突なし
        return pos;
}
    else if (_wDeath.HitNum >= 1) {
        // 衝突あれば移動する
        newPos = VAdd(pos, forward);
    }
    return  newPos;
}
/** 黒いデスメッシュとの当たり判定 */
VECTOR Collision::CollisionManager::CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward) {

    auto round = 20.0f;

    auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
    auto newPos = VAdd(pos, forward);
    auto c1 = VAdd(newPos, { 0.f, 140.f,0.f });
    auto c2 = VAdd(newPos, { 0.f, 1.f, 0.f });
    _bDeath = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "BDeath_NavMesh"), c1, c2, round);

    if (_bDeath.HitNum == 0) {
        // 衝突なし
        return pos;
    }
    else if (_bDeath.HitNum >= 1) {
        // 衝突あれば移動する
        newPos = VAdd(pos, forward);
    }
    return newPos;
}
/** デバッグ用当たり判定描画処理 */
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
/** チェックポイントとプレイヤーの当たり判定 */
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
