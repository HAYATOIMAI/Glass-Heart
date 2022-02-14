
/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJumpUp.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <numbers>

using namespace GlassHeart::State;

StateJumpUp::StateJumpUp(Player::Player& owner) : StateBase{owner} {}

void StateJumpUp::Enter() {
    _vY = -8.0f;

    if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, 100.0f, 0.0f);
        _jumpVelocity = jumpbase;
    }
    else if (_owner.GetRotation().y == 90.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, 100.f, 0.0f);
        _jumpVelocity = jumpbase;
    }
    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}

void StateJumpUp::Input(AppFrame::InputManager& input) {}

void StateJumpUp::Update() {

    auto jump = JumpUpdate();

    // 落下中で無ければ上昇
    if (_isfall != true || jump.y > 0.f) {
        _owner.SetPosition(jump);
        _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
    }

    // 移動ベクトルがマイナスになったら下降状態に移行
    if (_jumpVelocity.y < 0) {
        _owner.GetStateManage().PushBack("JumpFall");
        _isfall = true;
       
    }
}

VECTOR StateJumpUp::JumpUpdate() {
    // ベクトルで計算
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _vY;

    return jumpPosition;
}
