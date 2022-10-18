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
}

GlassHeart::Collision::IsHitFloor::IsHitFloor(Object::ObjectBase& owner) :_owner{ owner } {
	_floor.HitFlag = 0;
	_bThrough.HitFlag = 0;
	_wThrough.HitFlag = 0;
}
VECTOR GlassHeart::Collision::IsHitFloor::CheckHitFloor(const VECTOR& pos, const VECTOR& forward, const std::uint_fast8_t state) {
	auto [handle, no] = _owner.GetGame().GetResourceServer().GetModles(Stage);
	auto newPos = VAdd(pos, forward);
	auto start = VAdd(pos, { 0.f, 1.f, 0.f });
	auto end = VAdd(pos, { 0.f, forward.y, 0.f });
	// �F�ɂ���Ĕ��肷�郁�b�V����ύX
	switch (state) {
	case 0:
		_bThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, NavMesh_B), start, end);
		if (_bThrough.HitFlag == 1) {
			// �������Ă�����ʒu��Ԃ�
			return pos;
		}
		_floor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, FloorMesh), start, end);
		break;
	case 1:
		_wThrough = MV1CollCheck_Line(handle, MV1SearchFrame(handle, NavMesh_W), start, end);
		if (_wThrough.HitFlag == 1) {
			// �������Ă�����ʒu��Ԃ�
			return pos;
		}
		_floor = MV1CollCheck_Line(handle, MV1SearchFrame(handle, FloorMesh), start, end);
		break;
	default:
		break;
	}

	if (_floor.HitFlag == 0) {
		// �Փ˂Ȃ�
		return newPos;
	}
	// �������Ă�����ʒu��Ԃ�
	return  pos;
}