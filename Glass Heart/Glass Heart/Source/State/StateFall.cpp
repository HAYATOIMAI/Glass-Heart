
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
    constexpr auto DownVector = 13.5f; // 下降量
    constexpr auto StraifVector = 10.0f; // ストレイフ用X軸移動量
    constexpr auto JumpVecY = 0.0f;  //!< ジャンプ用Y軸移動量ベクトル
    constexpr auto Gravity = -2.0f;
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

using namespace GlassHeart;

void State::StateFall::Enter() {
    VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    _jumpVelocity = jumpbase;
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
        _owner.SetForwardSpeed(-StraifVector);
    }
}

void State::StateFall::Update() {
    Landing();
    
    //auto pos = _owner.GetPosition();

    //auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    //_jumpVelocity.y += Gravity;

    //forward.y = _jumpVelocity.y;

    //pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetStand().HitFlag == 0) {
    //    pos.x += forward.x;
    //}
    //else if (_owner.GetCollision().GetStand().HitFlag == 1) {
    //   // _owner.GetStateManage().GoToState("Idle");
    //}

    //pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetStand().HitFlag == 0) {
    //    pos.y += forward.y;
    //}
    //else if (_owner.GetCollision().GetStand().HitFlag == 1) {
    //    _owner.GetStateManage().GoToState("Idle");
    //}

    //pos = _owner.GetCollision().CheckHitSecondFloor(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetHitSecondFloor().HitFlag == 0) {
    //    pos.x += forward.x;
    //}
    //else if (_owner.GetCollision().GetHitSecondFloor().HitFlag == 1) {
    //    //_owner.GetStateManage().GoToState("Idle");
    //}

    //pos = _owner.GetCollision().CheckHitSecondFloor(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetHitFloor().HitFlag == 0) {
    //    pos.y += forward.y;
    //}
    //else if (_owner.GetCollision().GetHitFloor().HitFlag == 1) {
    //    _owner.GetStateManage().GoToState("Idle");
    //}

    //_owner.SetPosition(pos);
    auto pos = _owner.GetPosition();

    // リスポーン処理
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {

        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(VGet(pos.x, pos.y, pos.z));

            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.ResetPos();
        }
    }
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(VGet(pos.x, pos.y, pos.z));
        }
    }
}

void State::StateFall::Landing() {

    auto pos = _owner.GetPosition();
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    _owner.GetCollision().CheckJumpStand(pos, forward);
    _owner.GetCollision().CheckHitWDeathMesh(pos, forward);
    _owner.GetCollision().CheckHitBDeathMesh(pos, forward);
    _owner.GetCollision().CheckThroughBMesh(pos, forward);
    _owner.GetCollision().CheckThroughWMesh(pos, forward);
    _owner.GetCollision().CheckHitSideAndBottom(pos, forward);

    _owner.GetCollision().CheckHitSecondJumpStand(pos, forward);
    _owner.GetCollision().CheckHitSecondThroughBMesh(pos, forward);
    _owner.GetCollision().CheckHitSecondThroughWMesh(pos, forward);

    // 空中の足場と接していなかったらゆっくり落下させる
    // 途中スティックの入力があった場合、入力に応じた角度に補正
    if (_owner.GetCollision().GetStand().HitFlag == 0) {
        _owner.SetPosition(VGet(_owner.GetPosition().x + _owner.GetForwardSpeed(), _owner.GetPosition().y - DownVector, _owner.GetPosition().z));

        if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            if (_owner.GetRotation().y == RightRotation) {
                _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
                _reVx += 80.0f;
            }
            else if (_owner.GetRotation().y == LeftRotation) {
                _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
                _reVx -= 80.0f;
            }
            _owner.SetPosition(VGet(_owner.GetPosition().x + _reVx, _owner.GetPosition().y, _owner.GetPosition().z));
        }
    }
    else {
        // 着地したら状態を削除
        _owner.GetStateManage().PopBack();
    }
    // 空中の足場と接しているか
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
        // 着地したら状態を削除
        _owner.GetStateManage().PopBack();
    }
    // 白色のみ透ける足場に接しているか
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        // 接している足場と異なる色の場合のみとどまる
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
            // 着地したら状態を削除
            _owner.GetStateManage().PopBack();
        }
    }
    // 黒色のみ透ける足場に接しているか
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        // 接している足場と異なる色の場合のみとどまる
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
            // 着地したら状態を削除
            _owner.GetStateManage().PopBack();
        }
    }

    if (_owner.GetCollision().GetSecondBThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetSecondBThroughMesh().HitPosition);
            // 着地したら状態を削除
            _owner.GetStateManage().PopBack();
        }
    }

    if (_owner.GetCollision().GetSecondWThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetSecondWThroughMesh().HitPosition);
            // 着地したら状態を削除
            _owner.GetStateManage().PopBack();
        }
    }
}
