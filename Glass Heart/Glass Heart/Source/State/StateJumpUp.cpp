
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
}

using namespace GlassHeart;

State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** 入り口処理 */
void State::StateJumpUp::Enter() {
    if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, 80.0f, 0.0f);
        _jumpVelocity = jumpbase;
    }
    else if (_owner.GetRotation().y == 90.0f * (std::numbers::pi_v<float> / 180.0f)) {
        VECTOR jumpbase = VGet(0.0f, 80.f, 0.0f);
        _jumpVelocity = jumpbase;
    }
    _owner.GetModelAnime().ChangeAnime("Jump_Loop", true);
}
void State::StateJumpUp::Input(AppFrame::InputManager& input) {
    input.GetJoyPad().InputReject();

    if (input.GetJoyPad().GetAnalogStickLX() > 5000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _addVx = -StraifVector;
    }
    if (input.GetJoyPad().GetAnalogStickLX() < -5000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _addVx = StraifVector;
    }
}
/** 更新処理 */
void State::StateJumpUp::Update() {

    auto jump = JumpUpdate();

    _owner.GetCollision().CheckHitSideAndBottom(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    _owner.GetCollision().CheckHitWall(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    _owner.GetCollision().CheckThroughBWallMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });
    _owner.GetCollision().CheckThroughWWallMesh(_owner.GetPosition(), { 0.f, 3.f, 0.f });

    // 落下中もしくはYが0以下で無ければ上昇
    if (_isfall != true || jump.y > 0.f) {

        _position = _owner.GetPosition();

        // 底面に衝突したか
        if (_owner.GetCollision().GetSideAndBottom().HitNum == 0) {
            // 衝突していないのでそのままジャンプ
            _owner.SetPosition(VGet(jump.x + _addVx, jump.y, jump.z));
        }
        else if (_owner.GetCollision().GetSideAndBottom().HitNum >= 1) {
            // 衝突したので押し戻す
            _owner.SetPosition(VGet(_position.x, _position.y - 35.f, _position.z));
            _vX = 0.f;
            
        }
        // 壁面に衝突したか
        if (_owner.GetCollision().CollPol().HitNum >= 1) {
            if (_owner.GetRotation().y == 270.0f * (std::numbers::pi_v<float> / 180.0f)) {
                _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
                _vX -= 80.0f;
            } else  {
                _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
                _vX += 80.0f;
            }
            _owner.SetPosition(VGet(_position.x + _vX, _position.y, _position.z));
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

   

    // 移動ベクトルがマイナスになったら下降状態に移行
    if (_jumpVelocity.y < 0) {
        _owner.GetStateManage().PushBack("JumpFall");
        _isfall = true;

    }
}
/** ジャンプ中処理 */
VECTOR State::StateJumpUp::JumpUpdate() {
    // ベクトルで計算
    VECTOR jumpPosition = VAdd(_owner.GetPosition(), _jumpVelocity);

    _jumpVelocity.y += _jY;

    return jumpPosition;
}
