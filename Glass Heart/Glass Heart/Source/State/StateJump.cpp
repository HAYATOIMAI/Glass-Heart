
/*****************************************************************//**
 * @file   StateJump.cpp
 * @brief  ジャンプ状態クラスの処理
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJump.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>

namespace {
    constexpr auto DegreeToRadian = DX_PI_F / 180.0f;
}

using namespace GlassHeart::State;

StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {
    _jumpStartPosition = VGet(0.0f, 0.0f, 0.0f);
    _jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
}

void StateJump::Enter() {
    _owner.SetForwardSpeed(5.0f);
    _owner.GetModelAnime().ChangeAnime("MO_SDChar_jumpStart", true);
}

void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputUp()) {
        _owner.GetStateManage().PushBack("Run");
    }
    if (input.GetJoyPad().GetXinputButtonA()) {
        return;
    }
}

void StateJump::Update() {

    auto T = false;
    if (isJump) {
        JumpFunction(T);
    }
}

void StateJump::JumpFunction(const bool isJumpStart) {
    if (isJumpStart){
        JumpStart();
    }

    auto jumpposition = JumpProcess();

    if (isJumpStart || jumpposition.y) {
        _owner.SetPosition(jumpposition);
    }
    else {
        JumpEnd(jumpposition);
    }
}

void StateJump::JumpStart() {

}

VECTOR StateJump::JumpProcess() {
    VECTOR jumpposition = VAdd(_jumpStartPosition, _jumpVelocity);

    _jumpVelocity.y -= _gravity;

    return jumpposition;
}

void StateJump::JumpEnd(const VECTOR& jumppos) {
}
