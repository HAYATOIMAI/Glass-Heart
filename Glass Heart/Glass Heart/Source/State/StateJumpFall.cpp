
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
#include <numbers>

namespace {
    constexpr auto DownVector = 13.5f; // Y軸の移動量ベクトル下降量
    constexpr auto JumpVecY = 20.0f;  //!< ジャンプ用Y軸移動量ベクトル
    constexpr auto StraifVector = 10.0f; // ストレイフ用X軸移動量
    constexpr auto Gravity = -1.0f;
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

using namespace GlassHeart;

State::StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void State::StateJumpFall::Enter() {

    // ジャンプ速度設定
    //VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    //_jumpVelocity = jumpbase;

    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
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
        _owner.SetForwardSpeed(-StraifVector);
    }
}
/** 更新処理 */
void State::StateJumpFall::Update() {
    // 入力制限の為カウンタを減少
    if (_cnt > 0) {
        --_cnt;
    }

   // auto pos = _owner.GetPosition();

   // auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

   // _jumpVelocity.y += Gravity;

   // forward.y = _jumpVelocity.y;

   //// (pos.x+forward.x, pos.y)でWall_NavMeshと判定
   //// 当たり：pos.xそのままにして移動キャンセル
   //// はずれ：pos.x+=forward.x移動させる

   //// (pos.x, pos.y+forward.y)でWall_NavMeshと判定
   //// 当たり：pos.yそのままにして移動キャンセル
   //// はずれ：pos.y+=forward.y移動させる

   //// 最後に更新する
   //// _owner.SetPosition(pos);

   // pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetStand().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetStand().HitFlag == 1) {
   //     //pos.x;
   //    // _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckJumpStand(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetStand().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetStand().HitFlag == 1) {
   //     //pos.y;
   //     _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckHitSecondJumpStand(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetSecondStand().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetSecondStand().HitFlag == 1) {
   //    // _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckHitSecondJumpStand(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetSecondStand().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetSecondStand().HitFlag == 1) {
   //     _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckThroughBMesh(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetBThrough().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
   //     pos.x;
   // }

   // pos = _owner.GetCollision().CheckThroughBMesh(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetBThrough().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
   //     _owner.GetStateManage().GoToState("Idle");
   // }

   // pos = _owner.GetCollision().CheckThroughWMesh(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetWThrough().HitFlag == 0) {
   //     pos.x += forward.x;
   // }
   // else if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
   // }

   // pos = _owner.GetCollision().CheckThroughWMesh(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

   // if (_owner.GetCollision().GetWThrough().HitFlag == 0) {
   //     pos.y += forward.y;
   // }
   // else if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
   //     _owner.GetStateManage().GoToState("Idle");
   // }

    //_owner.SetPosition(pos);
     //足場と接しているか
    Landing();

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
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1)  {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {           
            _owner.SetPosition(VGet(pos.x, pos.y, pos.z));
        }
    }
}
void State::StateJumpFall::Landing() {

    auto pos = _owner.GetPosition();
    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

     _owner.GetCollision().CheckJumpStand(pos, forward);
     _owner.GetCollision().CheckHitWDeathMesh(pos, forward );
     _owner.GetCollision().CheckHitBDeathMesh(pos, forward );
     _owner.GetCollision().CheckThroughBMesh(pos, forward );
     _owner.GetCollision().CheckThroughWMesh(pos, forward );
     _owner.GetCollision().CheckHitSideAndBottom(pos, forward);

     _owner.GetCollision().CheckHitSecondJumpStand(pos, forward);
     _owner.GetCollision().CheckHitSecondThroughBMesh(pos, forward);
     _owner.GetCollision().CheckHitSecondThroughWMesh(pos, forward);

    // 空中の足場と接していなかったらゆっくり落下させる
    // 途中スティックの入力があった場合、入力に応じた角度に補正
    if (_owner.GetCollision().GetStand().HitFlag == 0) {
            _owner.SetPosition(VGet(pos.x +_owner.GetForwardSpeed(), pos.y - DownVector, pos.z));

        if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            if (_owner.GetRotation().y == RightRotation) {
                _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
                _reVx += 80.0f;
            }
            else if (_owner.GetRotation().y == LeftRotation) {
                _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
                _reVx += 80.0f;
            }
            _owner.SetPosition(VGet(pos.x + _reVx, pos.y, pos.z));
        }
    }
    else {
        // 着地したら状態を削除
        _owner.GetStateManage().PushBack("Idle");
        //_addVx = 0.f;
    }

    // 空中の足場と接しているか
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
            _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
            // 着地したら状態を削除
            _owner.GetStateManage().PushBack("Idle");
    }
    // 白色のみ透ける足場に接しているか
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        // 接している足場と異なる色の場合のみとどまる
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
    // 黒色のみ透ける足場に接しているか
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        // 接している足場と異なる色の場合のみとどまる
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }

    if (_owner.GetCollision().GetSecondJumpStand().HitFlag == 0) {
        _owner.SetPosition(VGet(pos.x + _owner.GetForwardSpeed(), pos.y - DownVector, pos.z));
    }
    else  if (_owner.GetCollision().GetSecondJumpStand().HitFlag == 1) {
        _owner.SetPosition(_owner.GetCollision().GetSecondJumpStand().HitPosition);
        // 着地したら状態を削除
        _owner.GetStateManage().GoToState("Idle");
    }

    if (_owner.GetCollision().GetSecondBThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetSecondBThroughMesh().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }

    if (_owner.GetCollision().GetSecondWThroughMesh().HitFlag == 1) {
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetSecondWThroughMesh().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
}