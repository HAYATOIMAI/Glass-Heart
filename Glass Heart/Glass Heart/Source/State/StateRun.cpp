
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

using namespace GlassHeart;

namespace {
    constexpr auto DefaultSpeed = 3.5f; //!< 歩行スピード
}

void State::StateRun::Enter() {
    _owner.SetForwardSpeed(DefaultSpeed);
    _owner.GetModelAnime().ChangeAnime("dash", true);
}

void State::StateRun::Input(AppFrame::InputManager& input) {
    // Aボタンが押されたらジャンプ状態へ移行
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _owner.GetStateManage().PushBack("Jump");
    }
    if (input.GetJoyPad().GetAnalogStickLX() >= 3000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() >= 30000) {
            _owner.SetForwardSpeed(DefaultSpeed * 1.0f);
        }
    }
    else if (input.GetJoyPad().GetAnalogStickLX() <= -3000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() <= -30000) {
            _owner.SetForwardSpeed(DefaultSpeed * 1.0f);
        }
    }
    else {
        _owner.GetStateManage().PopBack();
    }
 
}

void State::StateRun::Update() {

    _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));

    _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });   

    if (_owner.GetCollision().GetStand().HitFlag == 1)  {
        
        if (_owner.GetCollision().GetStand().HitFlag == 0) {
            auto x = _owner.GetCollision().GetStand().HitPosition.x - _owner.GetLastPosition().x;
           // _owner.SetPosition(VGet(_owner.GetPosition().x + x, _owner.GetPosition().y, _owner.GetPosition().z));
            //_owner.GetStateManage().PushBack("Fall");

        }
    }
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::Black)  {

            //_owner.GetStateManage().PushBack("Fall");
        }
    }
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {

            //_owner.GetStateManage().PushBack("Fall");
        }
    }

    auto pos = _owner.GetPosition();
    // リスポーン処理
    if (_owner.GetCollision().GetDeathMesh().HitNum >= 1) {

        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(pos);
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
        }
        // _owner.GetStateManage().PushBack("Dead");
    }
}
