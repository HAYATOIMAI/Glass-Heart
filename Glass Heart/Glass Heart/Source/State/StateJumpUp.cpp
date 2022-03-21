
/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief  上昇状態の宣言
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJumpUp.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <numbers>

namespace {
    constexpr auto StraifVector = 6.5f;                                          //!< ストレイフ用X軸移動量
    constexpr auto JumpVecY = 24.5f;                                             //!< Y軸移動量ベクトル
    constexpr auto Gravity = -0.8f;                                              //!< 重力加速度
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f); //!< 左方向の角度
}

using namespace GlassHeart;

State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** 入り口処理 */
void State::StateJumpUp::Enter() {
    // ジャンプ速度設定
    VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    _owner.SetJumpVelocity(jumpbase);
    // ジャンプ中のアニメーションを再生
    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}
/** 入力処理 */
void State::StateJumpUp::Input(AppFrame::InputManager& input) {
   
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
void State::StateJumpUp::Update() {

    auto pos = _owner.GetPosition();
    // 移動量ベクトルを取得
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
    // ジャンプ上昇処理
    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;

    forward.y = jumpVelocity.y;
    // プレイヤーの色を取得
    int state = static_cast<int> (_owner.GetColourState());
    // 空中の足場の底面と側面判定処理
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { 0.f, forward.y, 0.f }, state);
    //　当たっていたら落下
    if (_owner.GetCollision().GetSideAndBottom().HitNum > 0) {
        jumpVelocity.y = 0;

    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        // 空中の足場とプレイヤーの色が異なっていたら落下
        if (_owner.GetCollision().GetWWallThroughMesh().HitNum > 0) {
            jumpVelocity.y = 0;
        }
    }
    // 空中の足場とプレイヤーの色が異なっていたら落下
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        if (_owner.GetCollision().GetBWallThroughMesh().HitNum > 0) {
            jumpVelocity.y = 0;
        }
    }
    // 死亡判定を取るメッシュと当たり判定
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
    // プレイヤーの色が異なっていたらリスポーン処理
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
           // _owner.GetStateManage().PushBack("Dead");
        }
    }
    // プレイヤーの色が異なっていたらリスポーン処理
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
        pos = _owner.GetCollision().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
    // プレイヤーの色が異なっていたらリスポーン処理
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        }
    }
    // 座標更新
    _owner.SetPosition(pos);

    //移動ベクトルがマイナスになったら下降状態に移行
    if (jumpVelocity.y <= 0) {
        _owner.GetStateManage().PushBack("JumpFall");
    }

    _owner.SetJumpVelocity(jumpVelocity);
}
