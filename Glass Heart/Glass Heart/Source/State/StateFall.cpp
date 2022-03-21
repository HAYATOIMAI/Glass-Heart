
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
#include <numbers>
#include <AppFrame.h>

namespace {
    constexpr auto StraifVector = 3.0f; // ストレイフ用X軸移動量
    constexpr auto JumpVecY = 0.0f;  //!< ジャンプ用Y軸移動量ベクトル
    constexpr auto Gravity = -1.0f;  //!< 重力加速度
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

using namespace GlassHeart;

void State::StateFall::Enter() {
    //VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    //_jumpVelocity = jumpbase;

    auto& game = _owner.GetGame();
    game.GetSoundManager().StopSound("run");

    _owner.SetJumpVelocity({ 0,3,0 });
}

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

void State::StateFall::Update() {
    //リスポーン処理
    //if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.ResetPos();
    //        _owner.GetStateManage().PushBack("Dead");
    //    }
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        // SetPosition(VGet(_position.x, _position.y, _position.z));

    //    }
    //}
    //if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //    }
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        _owner.ResetPos();
    //        _owner.GetStateManage().PushBack("Dead");
    //    }
    //}
    
    auto pos = _owner.GetPosition();

    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    auto jumpVelocity = _owner.GetJumpVelocity();
    jumpVelocity.y += Gravity;
    _owner.SetJumpVelocity(jumpVelocity);

    forward.y = jumpVelocity.y;

    int state = static_cast<int> (_owner.GetColourState());
    pos = _owner.GetCollision().CheckHitSideAndBottom(pos, { forward.x, 0, 0 }, state);

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

    pos = _owner.GetCollision().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0 });


    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
           // _owner.ResetPos();
           _owner.GetStateManage().PushBack("Dead");
        }
    }

    pos = _owner.GetCollision().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0 });

    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
            //_owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            // SetPosition(VGet(_position.x, _position.y, _position.z));

        }
    }

    _owner.SetPosition(pos);
}

void State::StateFall::Landing() {

    //auto pos = _owner.GetPosition();
    //auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    //_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitWDeathMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitBDeathMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckThroughBMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckThroughWMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    //_owner.GetCollision().CheckHitSideAndBottom(_owner.GetPosition(), { 0.f, 3.f, 0.f });

    //// 空中の足場と接していなかったらゆっくり落下させる
    //// 途中スティックの入力があった場合、入力に応じた角度に補正
    //if (_owner.GetCollision().GetStand().HitFlag == 0) {
    //    if (_subVx > 1) {
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _subVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    //        _subVx = 0;
    //    }
    //    else {
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _addVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    //        _addVx = 0;
    //    }

    //    if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
    //        if (_owner.GetRotation().y == RightRotation) {
    //            _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
    //            _reVx += 80.0f;
    //        }
    //        else if (_owner.GetRotation().y == LeftRotation) {
    //            _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
    //            _reVx -= 80.0f;
    //        }
    //        _owner.SetPosition(VGet(_owner.GetPosition().x + _reVx, _owner.GetPosition().y, _owner.GetPosition().z));
    //    }
    //}
    //else {
    //    // 着地したら状態を削除
    //    _owner.GetStateManage().PushBack("Idle");
    //}
    //// 空中の足場と接しているか
    //if (_owner.GetCollision().GetStand().HitFlag == 1) {
    //    _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
    //    // 着地したら状態を削除
    //    _owner.GetStateManage().PushBack("Idle");
    //}
    //// 白色のみ透ける足場に接しているか
    //if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
    //    // 接している足場と異なる色の場合のみとどまる
    //    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    //        _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
    //        // 着地したら状態を削除
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}
    //// 黒色のみ透ける足場に接しているか
    //if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
    //    // 接している足場と異なる色の場合のみとどまる
    //    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    //        _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
    //        // 着地したら状態を削除
    //        _owner.GetStateManage().PushBack("Idle");
    //    }
    //}
}
