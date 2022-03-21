
/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  プレイヤーの落下状態
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateJumpFall.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include <numbers>

namespace {
    constexpr auto StraifVector = 3.0f; // ストレイフ用X軸移動量
    constexpr auto Gravity = -0.2f;  //!< 重力加速度
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

using namespace GlassHeart;

State::StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void State::StateJumpFall::Enter() {
    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
    auto& game = _owner.GetGame();
    game.GetSoundManager().StopSound("run");
}

void State::StateJumpFall::Input(AppFrame::InputManager& input) {
    _owner.SetForwardSpeed(0.f);
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000 && input.GetJoyPad().GetAnalogStickLX() > 1) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
        _owner.SetForwardSpeed(StraifVector);
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= -5000 && input.GetJoyPad().GetAnalogStickLX() < 1) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
        _owner.SetForwardSpeed(StraifVector);
    }
}
/** 更新処理 */
void State::StateJumpFall::Update() {
    // 入力制限の為カウンタを減少
    if (_cnt > 0) {
        --_cnt;
    }

    auto pos = _owner.GetPosition();

    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;
    _owner.SetJumpVelocity(jumpVelocity);

    forward.y = jumpVelocity.y;

    int state = static_cast<int> (_owner.GetColourState());
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);

    pos = _owner.GetCollision().CheckJumpStand(pos, { 0.f, forward.y, 0.f }, state);

    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        _owner.GetStateManage().GoToState("Idle");
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {

        if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
            _owner.GetStateManage().GoToState("Idle");
        }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
           _owner.GetStateManage().GoToState("Idle");
        }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
  
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
        }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        pos = _owner.GetCollision().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
  
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            // SetPosition(VGet(_position.x, _position.y, _position.z));

        }
    }

    _owner.SetPosition(pos);
}
void State::StateJumpFall::Landing() {
}