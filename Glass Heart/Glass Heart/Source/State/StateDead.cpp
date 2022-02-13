
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
#include <numbers>

using namespace GlassHeart::State;

StateDead::StateDead(Player::Player& owner) : StateBase{owner} {
    _position = VGet(0.0f, 0.0f, 0.0f);
}

void StateDead::Enter() {
    _position = VGet(-150.0f, 20.0f, -140.0f);
}

void StateDead::Update() {
    ResetPos();
}

void StateDead::ResetPos() {
    auto r = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
    _owner.SetPosition(_position);
    _owner.SetRotation(r);
    _owner.GetStateManage().PopBack();
}
