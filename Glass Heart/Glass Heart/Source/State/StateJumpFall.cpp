
/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  �v���C���[�̗������
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
    // ���̍����ȏゾ������@�n�ʂƐڂ��Ă��邩�m�F
    if (_owner.GetPosition().y >= 300) {
        _owner.GetCollision().CheckJumpStand(_owner.GetPosition(), { 0, 3, 0 });
        _owner.GetCollision().CheckTerrain(_owner.GetPosition(), { 0, 300, 0 });
        // �󒆂̑���Ɛڂ��Ă��邩
        if (_owner.GetCollision().GetStand().HitFlag == 1) {
            // �ڂ��Ă��鑫��ƈقȂ�F�̏ꍇ�݂̂Ƃǂ܂�
            if (_owner.GetCrName() == "White") {
                _owner.SetPosition(_owner.GetCollision().GetStand().HitPosition);
            }
            _owner.GetStateManage().PushBack("Idle");
        }
        // �󒆂̑���Ɛڂ��Ă��Ȃ�������n��̑���ɖ߂�
        if (_owner.GetCollision().GetStand().HitFlag == 0) {
            _owner.GetStateManage().PushBack("Idle");
        }
    }
}