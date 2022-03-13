
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

namespace {
    constexpr auto StraifVector = 10.0f; // ストレイフ用X軸移動量
    constexpr auto JumpVecY = 40.0f;  //!< ジャンプ用Y軸移動量ベクトル
    constexpr auto RerocateY = 35.0f; //!< 足場の底面や側面衝突時の位置修正量
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< 右方向の角度
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< 左方向の角度
}

using namespace GlassHeart;

State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** 入り口処理 */
void State::StateJumpUp::Enter() {
    // ジャンプ速度設定
    VECTOR jumpbase = VGet(0.0f, JumpVecY, 0.0f);
    _jumpVelocity = jumpbase;

    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}
void State::StateJumpUp::Input(AppFrame::InputManager& input) {
   
    //if (input.GetJoyPad().GetAnalogStickLX() >= 5000 && input.GetJoyPad().GetAnalogStickLX() > 1) {
    //    // 右方向に向きを変更
    //    _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
    //    _subVx += StraifVector;
    //}
    //if (input.GetJoyPad().GetAnalogStickLX() <= -5000 && input.GetJoyPad().GetAnalogStickLX() < 1) {
    //    // 左方向に向きを変更
    //    _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
    //    _addVx -= StraifVector;
    //}
    
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
    //input.GetJoyPad().InputReject();
}
/** 更新処理 */
void State::StateJumpUp::Update() {

    //auto pos = _owner.GetPosition();

    //auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    //_jumpVelocity.y += -2.0f;

    //forward.y = _jumpVelocity.y;
    //// forwardが今回の移動量xとy

    //// (pos.x+forward.x, pos.y)でWall_NavMeshと判定
    //// 当たり：pos.xそのままにして移動キャンセル
    //// はずれ：pos.x+=forward.x移動させる

    //// (pos.x, pos.y+forward.y)でWall_NavMeshと判定
    //// 当たり：pos.yそのままにして移動キャンセル
    //// はずれ：pos.y+=forward.y移動させる

    //// 最後に更新する
    //// _owner.SetPosition(pos);

    //pos =  _owner.GetCollision().CheckHitSideAndBottom(VGet(pos.x + forward.x, pos.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
    //    pos.x += forward.x;
    //}
    //else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
    //    pos.x;
    //    //_owner.GetStateManage().GoToState("Fall");
    //}

    //pos = _owner.GetCollision().CheckHitSideAndBottom(VGet(pos.x, pos.y + forward.y, pos.z), _owner.GetForward());

    //if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
    //    pos.y += forward.y;
    //}
    //else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
    //    pos.y;
    //    _owner.GetStateManage().GoToState("Fall");
    //}

    // _owner.SetPosition(pos);

    // if (_jumpVelocity.y < 0) {
    //     _owner.GetStateManage().PushBack("JumpFall");
    //     _isfall = true;
    // }

    auto jump = JumpUpdate();

    auto pos = _owner.GetPosition();

    auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());

    _owner.GetCollision().CheckHitSideAndBottom(pos, forward);
    _owner.GetCollision().CheckThroughBWallMesh(pos, forward);
    _owner.GetCollision().CheckThroughWWallMesh(pos, forward);

    // 落下中もしくは移動ベクトルが0以下で無ければ上昇
    if (_isfall != true  || jump.y > 0.f) {

        _position = _owner.GetPosition();

        // 底面に衝突したか
        if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
            // 衝突していないのでそのままジャンプ
            _owner.SetPosition(VGet(pos.x + _owner.GetForwardSpeed(), jump.y, jump.z));
        }
        else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            // 衝突したので押し戻す
            //_owner.SetPosition(VGet(_position.x, _position.y - RerocateY, _position.z));
            _owner.GetStateManage().PushBack("Fall");
            _vX = 0.f;
            
        }
        // 壁面に衝突したか
        if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            if (_owner.GetRotation().y == RightRotation) {
                _owner.SetRotation(VGet(0.0f, LeftRotation, 0.0f));
                //_vX -= 80.0f;
                _owner.SetForwardSpeed(-80.0f);
            } else  {
                _owner.SetRotation(VGet(0.0f, RightRotation, 0.0f));
                //_vX += 80.0f;
                _owner.SetForwardSpeed(80.0f);
            }
            _owner.SetPosition(VGet(_position.x + _owner.GetForwardSpeed(), _position.y, _position.z));
            _vX = 0.f;
        }
        //if (_owner.GetCollision().GetBWallThroughMesh().HitNum == 0) {
        //    // 衝突していないのでそのままジャンプ
        //    _owner.SetPosition(VGet(_position.x, jump.y, jump.z));
        //}
        //else if (_owner.GetCollision().GetBWallThroughMesh().HitNum >= 1) {
        //    // 衝突したので押し戻す
        //    _owner.SetPosition(VGet(_position.x, _position.y - 35.f, _position.z));
        //}

        //if (_owner.GetCollision().GetWWallThroughMesh().HitNum == 0) {
        //    // 衝突していないのでそのままジャンプ
        //    _owner.SetPosition(VGet(_position.x, jump.y, jump.z));
        //}
        //else if (_owner.GetCollision().GetWWallThroughMesh().HitNum >= 1) {
        //    // 衝突したので押し戻す
        //    _owner.SetPosition(VGet(_position.x, _position.y - 35.f, _position.z));

        //}
    }
     //移動ベクトルがマイナスになったら下降状態に移行
    if (_jumpVelocity.y < 0) {
        _owner.GetStateManage().PushBack("JumpFall");
        _isfall = true;
    }
}
/** ジャンプ中処理 */
VECTOR State::StateJumpUp::JumpUpdate() {
    // ベクトルで計算
    // 移動ベクトルに重力加速度を足し続けて
    // 0より小さくなったら落下
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _jY;

    return jumpPosition;
}
