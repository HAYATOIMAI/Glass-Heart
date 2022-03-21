
/*****************************************************************//**
 * @file   StateIdle.cpp
 * @brief  �A�C�h����ԃN���X�̏���
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateIdle.h"
#include <AppFrame.h>
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"

using namespace GlassHeart;

void State::StateIdle::Enter() {

	if (_resetFlag == false) {
		_owner.SetWhite();
		_resetFlag = true;
	}

	_owner.SetForwardSpeed(0.0f);
	// �ҋ@���[�V�������Đ�
	_owner.GetModelAnime().ChangeAnime("idle", true);
}

void State::StateIdle::Input(AppFrame::InputManager& input) {
	auto& game = _owner.GetGame();

	if (input.GetJoyPad().GetXinputThumbLX()) {
		game.GetSoundManager().PlayLoop("run");
		_owner.GetStateManage().PushBack("Run");
	}
	else if (!input.GetJoyPad().GetXinputThumbLX()) {
		game.GetSoundManager().StopSound("run");
	}
	if (input.GetJoyPad().GetXTriggerButtonA() && _cnt == 0) {
		game.GetSoundManager().Play("jump");
		_cnt = 5;
		_owner.GetStateManage().PushBack("Jump");
	}
}

void State::StateIdle::Update() {
	// ���͐����̈׃J�E���^������
	if (_cnt > 0) {
		--_cnt;
	}
}
