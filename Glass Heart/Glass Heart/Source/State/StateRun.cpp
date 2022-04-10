
/*****************************************************************//**
 * @file   StateRun.cpp
 * @brief  走り状態クラスの処理
 *
 * @author Hayato Imai, 
 * @date   January 2022
 *********************************************************************/
#include "StateRun.h"
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>
#include <numbers>

using namespace GlassHeart;

namespace {
    constexpr auto DefaultSpeed = 8.5f / 1.5f; //!< 歩行スピード
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

void State::StateRun::Enter() {
    _owner.SetForwardSpeed(DefaultSpeed);
    // 走りアニメーションを再生
    _owner.GetModelAnime().ChangeAnime("dash", true);
}

void State::StateRun::Input(AppFrame::InputManager& input) {
    auto& game = _owner.GetGame();
    // Aボタンが押されたらジャンプ状態へ移行
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        game.GetSoundManager().Play("jump");
        _owner.GetStateManage().PushBack("Jump");
    }
    // スティック入力があれば移動
    if (input.GetJoyPad().GetAnalogStickLX() >= 3000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
    }
    else if (input.GetJoyPad().GetAnalogStickLX() <= -3000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
    }
    else {
        // 何も入力が無ければアイドル状態へ移行
        _owner.GetStateManage().PopBack();
    }
}
/** 更新処理 */
void State::StateRun::Update() {
    // 移動処理
    _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));
}
