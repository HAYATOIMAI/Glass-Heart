
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
    _lastPosition = _owner.GetPosition();
}
/** 入り口処理 */
void StateJump::Enter() {
    _jumpStartPosition = _owner.GetPosition();

    if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(-12.0f, _jumpPower, 0.0f);
        _jumpVelocity = jumpbase;
    }
    else if(_owner.GetRotation().y ==  90.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(12.0f, _jumpPower, 0.0f);
        _jumpVelocity = jumpbase;
    }
<<<<<<< HEAD
   
    _owner.GetModelAnime().ChangeAnime("MO_SDChar_jumpStart", true);
=======

    _owner.GetModelAnime().ChangeAnime("Jump_start", true);
>>>>>>> 989e81406f870dcb22c2ed52ae5680147a58cf2f
}
/** 入力処理 */
void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        //_owner.GetStateManage().PushBack("Run");

    }
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _gravity = -8.0f; // Y軸のジャンプ量
        _isJump = true;
    }
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= 5000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
    }
}
/** 更新処理 */
void StateJump::Update() {
    // 対応するボタンが押されたらジャンプ処理実行
    if (_isJump == true){
         JumpFunction(_isJump);
    }   

    

    // 空中ブロックの天井との当たり判定(現状機能せず)
    //_owner.GetCollision().CheckHitCeiling(_owner.GetPosition(), { 0, -100, 0 });

}
/** ジャンプ処理制御 */
void StateJump::JumpFunction(const bool isJumpStart) {

    auto jump = JumpProcess();
    // 一定の高さ以上かフラグがtrueならジャンプ開始
    if (isJumpStart ||  jump.y > 35.0f) {
        _owner.SetPosition(jump);
        // 一定の高さ以上になったら上昇状態に移行
        if (_owner.GetPosition().y > 100.f) {

            _owner.GetStateManage().PushBack("JumpUp");
        }
    }
    else {
        _isJump = false;
    }

    // 落下中で無ければ上昇
    //if (_isfall != true) {
    //    auto j = JumpProcess();
    //    _owner.SetPosition(j);
    //}
    //else {
    //    _owner.GetStateManage().PushBack("JumpFall");
    //}
    //// 一定の高さに達したら落下開始
    //if (_owner.GetPosition().y > 700.0f && _owner.GetPosition().y < 1500.0f) {
    //    _isfall = true;
    //}

}
/** ジャンプ中処理 */
VECTOR StateJump::JumpProcess() {
    
    // ベクトルで計算
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _gravity;

    return jumpPosition;
}