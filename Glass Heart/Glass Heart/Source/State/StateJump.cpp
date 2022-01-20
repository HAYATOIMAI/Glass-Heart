
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
#include "../Collision/CollisionManager.h"
#include <numbers>
#include <AppFrame.h>

namespace {
    constexpr auto DegreeToRadian = std::numbers::pi_v<float> / 180.0f;
}

using namespace GlassHeart::State;

StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {
    _jumpStartPosition = VGet(0.0f, 0.0f, 0.0f);
    _jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
    _lastPosition = _owner.GetPosition();
}

void StateJump::Enter() {
    _owner.SetForwardSpeed(5.0f);
    _owner.GetModelAnime().ChangeAnime("MO_SDChar_jumpStart", true);
}

void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        _owner.GetStateManage().PushBack("Run");
    }
    if (input.GetJoyPad().GetXinputButtonA()) {
        _isJump = true;
        if (_isJump) {
            JumpFunction(_isJump);
        }
        return;
    }
    _owner.GetStateManage().PopBack();
}

void StateJump::Update() {
    _owner.GetPosition() = _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });
    _lastPosition = _owner.GetPosition();
}

void StateJump::JumpFunction(const bool isJumpStart) {
    if (isJumpStart) {
        JumpStart();
    }

    auto jumpposition = JumpProcess();

    if (isJumpStart || jumpposition.y > _groundY) {
        _owner.SetPosition(jumpposition);
    }
    else {
        JumpEnd(jumpposition);
        _isJump = false;
    }
}

void StateJump::JumpStart() {
    _jumpTimer = 0.0;
    _jumpStartPosition = _owner.GetPosition();

    VECTOR jumpbase = VGet(0.0f, 0.0f, static_cast<float>(-_jumpPower));
    MATRIX jump_rotate = MMult(MGetRotX(static_cast<float>(_jumpAngle) * DegreeToRadian), MGetRotY(_owner.GetRotation().y * DegreeToRadian));

    _jumpVelocity = VTransform(jumpbase, jump_rotate);
}

VECTOR StateJump::JumpProcess() {
    VECTOR jumpposition = VAdd(_jumpStartPosition, _jumpVelocity);

    _jumpVelocity.y -= _gravity;

    return jumpposition;
}

bool StateJump::JumpEnd(const VECTOR& jumppos) {
    if (_lastPosition.y < jumppos.y) {
        return false;
    }

    return false;
}
