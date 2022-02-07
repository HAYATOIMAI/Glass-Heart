
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
    constexpr auto DefaultSpeed = 10.0f;
}

void StateRun::Enter() {
    _owner.SetForwardSpeed(DefaultSpeed);
    _owner.GetModelAnime().ChangeAnime("MO_SDChar_run", true);
}

void StateRun::Input(AppFrame::InputManager& input) {

    if (input.GetJoyPad().GetAnalogStickLX() >= 3000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() >= 10000)	{
            _owner.SetForwardSpeed(DefaultSpeed * 2.0f);
        }
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= 3000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() <= 10000) {
            _owner.SetForwardSpeed(DefaultSpeed * 2.0f);
        }
    }
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _owner.GetStateManage().PushBack("Jump");
    }
    _owner.GetStateManage().PopBack();
}

void StateRun::Update() {
    _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));
}
