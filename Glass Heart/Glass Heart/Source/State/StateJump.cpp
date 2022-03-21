
/*********************************************************************
 * @file   StateJump.cpp
 * @brief  �W�����v��ԃN���X�̏���
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJump.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"
#include <numbers>
#include <AppFrame.h>

using namespace GlassHeart;

/** �R���X�g���N�^ */
State::StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {}
/** ��������� */
void State::StateJump::Enter() {
    _isJump = true;

    _owner.GetModelAnime().ChangeAnime("Jump_start", true);
}
/** ���͏��� */
void State::StateJump::Input(AppFrame::InputManager& input) {}
/** �X�V���� */
void State::StateJump::Update() {
    // �Ή�����{�^���������ꂽ��W�����v�������s
    if (_isJump == true){
        _owner.GetStateManage().PushBack("JumpUp");
        _isJump = false;
    }   
}