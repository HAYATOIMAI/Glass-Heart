
/*********************************************************************
 * @file   StateDead.cpp
 * @brief  プレイヤー死亡状態の処理
 * 
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#include "StateDead.h"
#include "../Player/Player.h"
#include "../State/StateManager.h"
#include "../Collision/CollisionManager.h"
#include "../Object/ObjectServer.h"
#include <numbers>

using namespace GlassHeart;

namespace {
    constexpr auto StartPositionX = -150.0f;  //!< プレイヤーの初期位置X
    constexpr auto StartPositionY = 35.0f;    //!< プレイヤーの初期位置Y
    constexpr auto StartPositionZ = -55.0f;  //!< プレイヤーの初期位置Z
}

State::StateDead::StateDead(Player::Player& owner) : StateBase{owner} {
    _position = VGet(0.0f, 0.0f, 0.0f);
}

void State::StateDead::Enter() {
    //_position = VGet(-150.0f, 35.0f, -55.0f);
}

void State::StateDead::Update() {
    ResetPos();
}

void State::StateDead::ResetPos() {
    // デスメッシュと当たっていたら
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        // 
        if (_owner.GetCheckPointFlag() == true) {
            // オブジェクトサーバーからチェックポイントの座標を取得
            auto checkPos = _owner.GetObjectServer().GetPosition("CheckPoint");
            // プレイヤーの座標をチェックポイントにする
            _owner.SetPosition(checkPos);
        }
        else {
            _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
            _owner.SetPosition(_position);
            _position = VGet(0.0f, 0.0f, 0.0f);
        }
    }
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        // 
        if (_owner.GetCheckPointFlag() == true) {
            // オブジェクトサーバーからチェックポイントの座標を取得
            auto checkPos = _owner.GetObjectServer().GetPosition("CheckPoint");
            // プレイヤーの座標をチェックポイントにする
           _owner.SetPosition(checkPos);
        }
        else {
            _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
            _owner.SetPosition(_position);
            _position = VGet(0.0f, 0.0f, 0.0f);
        }
    }
    _owner.GetStateManage().PopBack();
}
