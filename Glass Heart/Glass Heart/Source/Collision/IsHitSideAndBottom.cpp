#include "IsHitSideAndBottom.h"
#include "IsHitFloor.h"
#include "../Object/ObjectBase.h"
#include "CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include "../Player/Player.h"

namespace {
	constexpr auto Stage = "Stage";
	constexpr auto NavMesh_B = "BThroughFloor_NavMesh";
	constexpr auto NavMesh_W = "WThroughFloor_NavMesh";
	constexpr auto FloorMesh = "Floor_NavMesh";
	constexpr auto Round = 20.0f;
}

GlassHeart::Collision::IsHitSideAndBottom::IsHitSideAndBottom(Object::ObjectBase& owner) : _owner{owner} {
}

VECTOR GlassHeart::Collision::IsHitSideAndBottom::CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, 
	const std::uint_fast8_t state) {

	auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles("Stage");
	auto newPos = VAdd(pos, forward);
	auto c1 = VAdd(newPos, { 0.f, 140.f - Round, 0.f });
	auto c2 = VAdd(newPos, { 0.f, 1.f + Round, 0.f });
	// 色によって判定するメッシュを変更
	switch (state) {
	case 0:
		_bWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "BThroughWall_NavMesh"), c1, c2, Round);
		// 当たっていたら現在の位置を返す
		if (_bWallThrough.HitNum > 0) {
			return pos;
		}
		_sideBottom = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "Wall_NavMesh"), c1, c2, Round);
		break;
	case 1:
		_wWallThrough = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "WThroughWall_NavMesh"), c1, c2, Round);
		// 当たっていたら現在の位置を返す
		if (_wWallThrough.HitNum > 0) {
			return pos;
		}
		_sideBottom = MV1CollCheck_Capsule(handle, MV1SearchFrame(handle, "Wall_NavMesh"), c1, c2, Round);
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