
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
#include <numbers>
<<<<<<< HEAD
=======


namespace {
	constexpr auto DownVector = 20; // 1秒ごとの下降量
	constexpr auto StraifVector = 18.0f; // ストレイフ用X軸移動量
}
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{ owner } {}

void StateJumpFall::Enter() {}

void StateJumpFall::Input(AppFrame::InputManager& input) {
<<<<<<< HEAD
    if (input.GetJoyPad().GetAnalogStickLX() >= 5000) {
        // 右方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() >= 10000) {
            _owner.SetForwardSpeed(10.0f * 2.0f);
        }
    }
    if (input.GetJoyPad().GetAnalogStickLX() <= 5000) {
        // 左方向に向きを変更
        _owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
        if (input.GetJoyPad().GetAnalogStickLX() <= 10000) {
            _owner.SetForwardSpeed(1.0f * 2.0f);
        }
    }
}

void StateJumpFall::Update() {
    // 一定の高さ以上だったら　地面と接しているか確認
    if (_owner.GetPosition().y >= 300) {
<<<<<<< HEAD
        //_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
=======
        _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 300, 0 });
>>>>>>> 989e81406f870dcb22c2ed52ae5680147a58cf2f
        _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });
        // 空中の足場と接しているか
        if (_owner.GetCollision().Mcrp().HitFlag == 1) {
            // 接している足場と異なる色の場合のみとどまる
            if (_owner.GetCrName() == "White") {
                _owner.SetPosition(_owner.GetCollision().Mcrp().HitPosition);
            }
            _owner.GetStateManage().PushBack("Idle");
        }
        // 空中の足場と接していなかったら地上の足場に戻す
        if (_owner.GetCollision().Mcrp().HitFlag == 0) {
            _owner.GetStateManage().PushBack("Idle");
        }
    }
=======

	if (input.GetJoyPad().GetAnalogStickLX() >= 6000) {
		// 右方向に向きを変更
		_owner.SetRotation(VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
		_addVx = -StraifVector;
	}
	if (input.GetJoyPad().GetAnalogStickLX() <= 6000) {
		// 左方向に向きを変更
		_owner.SetRotation(VGet(0.0f, 90.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f));
		_addVx = StraifVector;
	}
}

void StateJumpFall::Update() {
	// 足場と接しているか
	_owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });

	// 空中の足場と接していなかったらゆっくり落下させる
	// 途中スティックの入力があった場合、入力に応じた角度に補正
	if (_owner.GetCollision().GetStand().HitFlag == 0) {
		_owner.SetPosition(VGet(_owner.GetPosition().x /*+ _addVx*/, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
	}
	else {
		// 着地したら状態を削除
		_owner.GetStateManage().PopBack();
	}

	// 空中の足場と接しているか
	if (_owner.GetCollision().GetStand().HitFlag == 1) {
		// 接している足場と異なる色の場合のみとどまる
		if (_owner.GetCrName() == "White") {
			_owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
			// 着地したら状態を削除
			_owner.GetStateManage().PopBack();
		}
	}
>>>>>>> 20d15396b0340e91c89ed3ce4e63dcdfdc047354
}