
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
    constexpr auto DownVector = 13.5f; // ���~��
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


    // �󒆂̑���Ɛڂ��Ă��邩
    if (_owner.GetCollision().GetStand().HitFlag == 1) {
        _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
        // ���n�������Ԃ��폜
        _owner.GetStateManage().PushBack("Idle");
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetBThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetColourState() == Player::Player::ColourState::White) {
            _owner.SetPosition(_owner.GetCollision().GetBThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
    // ���F�̂ݓ����鑫��ɐڂ��Ă��邩
    if (_owner.GetCollision().GetWThrough().HitFlag == 1) {
        // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
        if (_owner.GetColourState() == Player::Player::ColourState::Black) {
            _owner.SetPosition(_owner.GetCollision().GetWThrough().HitPosition);
            _owner.GetStateManage().PushBack("Idle");
        }
    }
}
