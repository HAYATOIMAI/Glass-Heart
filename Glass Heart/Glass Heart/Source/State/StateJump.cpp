
/*********************************************************************
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

/** コンストラクタ */
StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {
    _jumpStartPosition = VGet(0.0f, 0.0f, 0.0f);
    _jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
    _moveVector = VGet(0.0f, 0.0f, 0.0f);
    _lastPosition = _owner.GetPosition();
}
/** 入り口処理 */
void StateJump::Enter() {

    if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, _jumpPower, 0.0f);
        _jumpVelocity = jumpbase;
    }
    else if(_owner.GetRotation().y ==  90.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, _jumpPower, 0.0f);
        _jumpVelocity = jumpbase;
    }

    _owner.GetModelAnime().ChangeAnime("MO_SDChar_jumpStart", true);
}
/** 入力処理 */
void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        _owner.GetStateManage().PushBack("Run");
    }
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _gravity = -8.0f; // Y軸のジャンプ量
        _isJump = true;
    }
}
/** 更新処理 */
void StateJump::Update() {
    // 対応するボタンが押されたらジャンプ処理実行
    if (_isJump == true){
         JumpFunction(_isJump);
    }   
}
/** ジャンプ処理制御 */
void StateJump::JumpFunction(const bool isJumpStart) {


    _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });

    if (_owner.GetCollision().Mcrp().HitFlag )
    {
        auto jump = JumpProcess();
        // 一定の高さ以上かフラグがtrueならジャンプ開始
        if (isJumpStart || jump.y > 0.0f) {
            _owner.SetPosition(jump);
            //　移動ベクトルがマイナスになったら下降状態に移行
            if (_jumpVelocity.y < 0) {
                _owner.GetStateManage().PushBack("JumpFall");
            }
        }
        else {
            _isJump = false;
        }
    }
}
/** ジャンプ中処理 */
VECTOR StateJump::JumpProcess() {
    
    // ベクトルで計算
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _gravity;

    return jumpPosition;
}