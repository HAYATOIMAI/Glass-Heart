
/*****************************************************************//**
 * @file   StateIdle.cpp
 * @brief  �A�C�h����ԃN���X�̏���
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateIdle.h"
#include <AppFrame.h>
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"

using namespace GlassHeart::State;

void StateIdle::Enter() {
	_owner.SetForwardSpeed(0.0f);
	_owner.GetModelAnime().ChangeAnime("MO_SDChar_idle", true);
}

void StateIdle::Input(AppFrame::InputManager& input) {
	if (input.GetJoyPad().GetXinputThumbLX()) {
		_owner.GetStateManage().PushBack("Run");
	}
	if (input.GetJoyPad().GetXTriggerButtonA() && _cnt == 0) {
		_cnt = 60;
		_owner.GetStateManage().PushBack("Jump");
	}
}

void StateIdle::Update() {
	// �󒆂̑���Ɛڂ��Ă��邩
	if (_owner.GetCollision().GetStand().HitFlag == 1) {
		// �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
		if (_owner.GetCrName() == "White") {
			_owner.SetPosition(_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 300, 0 }));
		}
		else if (_owner.GetCrName() == "Black") {
			_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 7, 0 }));
		}
	}
	// �󒆂̑���Ɛڂ��Ă��Ȃ�������n��̑���ɖ߂�
	if (_owner.GetCollision().GetStand().HitFlag == 0) {
		_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 }));
	}

	if (_cnt > 0) {
		--_cnt;
	}
}
