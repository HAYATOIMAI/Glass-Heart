
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

    if (_owner.GetCollision().Mcrp().HitFlag == 1) {
        _jumpRise = _jumpHeight;
        _owner.SetJumpState(Player::Player::Jump::JumpStart);
    }
    else {
        _jumpRise = 0.0f;
        _owner.SetJumpState(Player::Player::Jump::JumpLoop);
    }

    _owner.GetModelAnime().ChangeAnime("MO_SDChar_jumpStart", true);
}
/** 入力処理 */
void StateJump::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetXinputThumbLX()) {
        _owner.GetStateManage().PushBack("Run");
    }
    if (input.GetJoyPad().GetXTriggerButtonA()) {
        _isJump = true;

    }
   // _owner.GetStateManage().PopBack();
}
/** 更新処理 */
void StateJump::Update() {

    if (_isJump ) {
        _lastPosition = _owner.GetPosition();
        JumpFunction(_isJump);
    }
   
   ///_owner.SetPosition(_owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 70 }));
}

void StateJump::JumpFunction(const bool isJumpStart) {
    if (isJumpStart) {
        JumpStart();
    }

  // _owner.SetPosition(JumpProcess());
   auto jump = JumpProcess();

    if (isJumpStart || /*_owner.GetJumpState() == Player::Player::Jump::JumpLoop &&*/ jump.y > 0.0f) {
        _owner.SetPosition(jump);
    }
    else {
        JumpLand();
        _isJump = false;
    }

}
/** ジャンプ開始処理 */
void StateJump::JumpStart() {
    _jumpTimer = 0.0;
    _jumpStartPosition = _owner.GetPosition();

    VECTOR jumpbase = VGet(0.0f, _jumpPower, 0.0f);
    MATRIX jump_rotate = MMult(MGetRotX(_jumpAngle * DegreeToRadian),MGetRotY(_owner.GetRotation().y * DegreeToRadian));

    //_jumpVelocity = VTransform(jumpbase, jump_rotate);
    _jumpVelocity = jumpbase;
}
/** ジャンプ中処理 */
VECTOR StateJump::JumpProcess() {
    //放物線の式で計算
    VECTOR jumpPosition = VAdd(_jumpStartPosition, VScale(_jumpVelocity, _jumpTimer));
    auto jumpY = (0.5 * _gravity * _jumpTimer * _jumpTimer);

    jumpPosition.y -= jumpY;
    _jumpTimer += 1.0f;

    return jumpPosition;
}
/** 着地処理 */
void StateJump::JumpLand() {

    _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 70 });

    if (_owner.GetCollision().Mcrp().HitFlag && _jumpVelocity.y < 0) {
        _owner.SetPosition(VGet(0.0f, _owner.GetCollision().Mcrp().HitPosition.y, 0.0f));
        _jumpVelocity = VGet(0.0f, 0.0f, 0.0f);
    }

}