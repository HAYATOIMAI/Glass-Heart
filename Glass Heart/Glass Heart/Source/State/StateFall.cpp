
/*********************************************************************
 * @file   StateFall.cpp
 * @brief  プレイヤーの落下クラスの処理
 * 
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#include "StateFall.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"
#include "../Object/ObjectServer.h"
#include <numbers>
#include <AppFrame.h>

namespace {
    constexpr auto StraifVector = 6.5f; // ストレイフ用X軸移動量
    constexpr auto JumpVecY = 0.0f;  //!< ジャンプ用Y軸移動量ベクトル
    constexpr auto Gravity = -1.0f;  //!< 重力加速度
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

using namespace GlassHeart;
/** 入り口処理 */
void State::StateFall::Enter() {

    auto& game = _owner.GetGame();
    game.GetSoundManager().StopSound("run");

    _owner.SetJumpVelocity({ 0.f,5.5f,0.f });
}
/** 入力処理 */
void State::StateFall::Input(AppFrame::InputManager& input) {
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
void State::StateFall::Update() {
    
    auto pos = _owner.GetPosition();
    // 移動量ベクトルを取得
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
    // 下降処理
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
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
    }
    // プレイヤーの色が異なっていたらリスポーン処理
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
        }
    }
    // リスポーン処理
    if (pos.y < -300.0f) {
        if (_owner.GetCheckPointFlag() == true) {
            // オブジェクトサーバーからチェックポイントの座標を取得
            auto checkPos = _owner.GetObjectServer().GetPosition("CheckPoint");
            // プレイヤーの座標をチェックポイントにする
            pos = checkPos;
        }
        else {
            pos = VGet(-150.f, 40.f, -55.f);
        }
    }
    // 座標更新
    _owner.SetPosition(pos);
}
