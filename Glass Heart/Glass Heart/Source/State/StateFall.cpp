
/*********************************************************************
 * @file   StateFall.cpp
 * @brief  
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
#include <AppFrame.h>

namespace {
    constexpr auto DownVector = 13.5f; // 下降量
}

using namespace GlassHeart;

void State::StateFall::Enter() {
    _owner.GetModelAnime().ChangeAnime("Jump_End", true);
}

void State::StateFall::Input(AppFrame::InputManager& input) {

}

void State::StateFall::Update() {
    Landing();
}

void State::StateFall::Landing() {
    _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckHitDeathMesh(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckThroughBMesh(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckThroughWMesh(_owner.GetPosition(), { 0, 3, 0 });
    _owner.GetCollision().CheckHitWall(_owner.GetPosition(), { 0, 3, 0 });

    if (_owner.GetCollision().GetStand().HitFlag == 0) {
        _owner.SetPosition(VGet(_owner.GetPosition().x, _owner.GetPosition().y - DownVector, _owner.GetPosition().z));
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
}
