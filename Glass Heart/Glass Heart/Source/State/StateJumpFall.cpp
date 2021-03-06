
/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  ジャンプ下降状態の宣言
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
    constexpr auto StraifVector = 6.5f;                                          //!< ストレイフ用X軸移動量
    constexpr auto Gravity = -0.6f;                                              //!< 重力加速度
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f); //!< 左方向の角度
}

using namespace GlassHeart;
/** 入り口処理 */
void State::StateJumpFall::Enter() {
    // 落下中のアニメーションを再生
    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
    // SEの再生を停止
    auto& game = _owner.GetGame();
    game.GetSoundManager().StopSound("run");
}
/** 入力処理 */
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

    auto pos = _owner.GetPosition();
    // 移動量ベクトルを取得
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
    // ジャンプ下降処理
    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;
    _owner.SetJumpVelocity(jumpVelocity);

    forward.y = jumpVelocity.y;
    // プレイヤーの色を取得
    int state = static_cast<int> (_owner.GetColourState());
    // 空中の足場の底面と側面判定処理
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
    // 床との当たり判定
    pos = _owner.GetCollision().CheckJumpStand(pos, { 0.f, forward.y, 0.f }, state);
    // 当たっていたら待機状態へ移行
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
        }
    }
    // 死亡判定を取るメッシュと当たり判定
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
}