
/*****************************************************************//**
 * @file   StateRun.cpp
 * @brief  走り状態クラスの処理
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateRun.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>
#include <numbers>

using namespace GlassHeart::State;

namespace {
    constexpr auto DefaultSpeed = 3.5f;
}

void StateRun::Enter() {
    _owner.SetForwardSpeed(DefaultSpeed);
    _owner.GetModelAnime().ChangeAnime("dash", true);
}

void StateRun::Input(AppFrame::InputManager& input) {

    if (input.GetJoyPad().GetAnalogStickLX() >= 3000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() >= 10000) {
            _owner.SetForwardSpeed(DefaultSpeed * 1.0f);
        }
    }
    else if (input.GetJoyPad().GetAnalogStickLX() <= -3000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() <= -10000) {
            _owner.SetForwardSpeed(DefaultSpeed * 1.0f);
        }
    }
    else if (input.GetJoyPad().GetXTriggerButtonA()) {
        _owner.GetStateManage().PushBack("Jump");
    }
    else {
        _owner.GetStateManage().PopBack();
    }
}

void StateRun::Update() {

    _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));

    // リスポーン処理
    if (_owner.GetCollision().GetDeathMesh().HitFlag == 1) {

        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetDeathMesh().HitPosition);
        }
        // _owner.GetStateManage().PushBack("Dead");
    }
}
