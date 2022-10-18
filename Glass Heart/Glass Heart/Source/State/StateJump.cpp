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

namespace {
  constexpr auto JumpStart = "Jump_start";  //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto JumpUp = "JumpUp";         //!< �J�ڂ�����X�e�[�g�̕�����
}

 /** �R���X�g���N�^ */
GlassHeart::State::StateJump::StateJump(Player::Player& owner) : StateBase{ owner } {}
/** ��������� */
void GlassHeart::State::StateJump::Enter() {
  // �W�����v�J�n���[�V�����Đ�
  _owner.GetModelAnime().ChangeAnime(JumpStart, true);
}
/** ���͏��� */
void GlassHeart::State::StateJump::Input(AppFrame::Input::InputManager& input) {}
/** �X�V���� */
void GlassHeart::State::StateJump::Update() {
  _owner.GetStateManage().GoToState(JumpUp);
}