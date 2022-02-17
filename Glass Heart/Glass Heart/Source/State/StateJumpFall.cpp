
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
    constexpr auto DownVector = 20; // 下降量
    constexpr auto StraifVector = 18.0f; // ストレイフ用X軸移動量
}

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void StateJumpFall::Enter() {
    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
}

void StateJumpFall::Input(AppFrame::InputManager& input) {
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _addVx = -StraifVector;
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= -5000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        _addVx = StraifVector;
    }
}
/** 更新処理 */
void StateJumpFall::Update() {
   
    // 足場と接しているか
    Landing();

    // リスポーン処理
    if (_owner.GetCollision().GetDeathMesh().HitFlag == 1) {

        if (_owner.GetCrName() == "White") {
            _owner.ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (_owner.GetCrName() == "Black") {
            _owner.SetPosition(_owner.GetCollision().GetDeathMesh().HitPosition);
        }
    }
    IsDeath();
}
void StateJumpFall::Landing() {

    _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckHitDeathFloor(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckThroughBMesh(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckThroughWMesh(_owner.GetPosition(), { 0, 3, 0 });
   

    // 空中の足場と接していなかったらゆっくり落下させる
    // 途中スティックの入力があった場合、入力に応じた角度に補正
    if (_owner.GetCollision().GetStand().HitFlag == 0) {
        _owner.SetPosition(VGet(_owner.GetPosition().x + _addVx, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
    }
    else {
        // 着地したら状態を削除
        _owner.GetStateManage().PushBack("Idle");
        _addVx = 0.f;
    }

    // 空中の足場と接しているか
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        // 接している足場と異なる色の場合のみとどまる
        if (_owner.GetCrName() == "White" || _owner.GetCrName() == "Black") {
            _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
            // 着地したら状態を削除
            _owner.GetStateManage().PushBack("Idle");
        }
    }
    // 白色のみ透ける足場に接しているか
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        // 接している足場と異なる色の場合のみとどまる
        if (_owner.GetCrName() == "White") {
            _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
    // 黒色のみ透ける足場に接しているか
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        // 接している足場と異なる色の場合のみとどまる
        if (_owner.GetCrName() == "Black") {
            _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }

   
}

void StateJumpFall::IsDeath() {
    // 落下死処理
    // レンガブロックに着地したか
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        // 着地処理
        _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
        auto landing = _owner.GetCollision().GetStand().HitPosition.y;
        // 最高地点と着地地点との差分を取得
        auto difference = _owner.GetHighestPosition().y - landing;
        // 差分が大きかったら死亡
        if (difference > 50.0f) {
            _owner.ResetPos();
        }
    }
}