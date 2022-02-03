
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

using namespace GlassHeart::State;

StateJumpFall::StateJumpFall(Player::Player& owner) : StateBase{owner} {}

void StateJumpFall::Enter() {}

void StateJumpFall::Input(AppFrame::InputManager& input) {}

void StateJumpFall::Update() {
    // 一定の高さ以上だったら　地面と接しているか確認
    if (_owner.GetPosition().y >= 300) {
        _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
        _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });
        // 空中の足場と接しているか
        if (_owner.GetCollision().GetStand().HitFlag == 1) {
            // 接している足場と異なる色の場合のみとどまる
            if (_owner.GetCrName() == "White") {
                _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
            }
            _owner.GetStateManage().PushBack("Idle");
        }
        // 空中の足場と接していなかったら地上の足場に戻す
        if (_owner.GetCollision().GetStand().HitFlag == 0) {
            _owner.GetStateManage().PushBack("Idle");
        }
    }
}