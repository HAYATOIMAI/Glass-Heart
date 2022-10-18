/*****************************************************************//**
 * @file   StateRun.cpp
 * @brief  �����ԃN���X�̏���
 *
 * @author Hayato Imai,
 * @date   January 2022
 *********************************************************************/
#include "StateRun.h"
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include <AppFrame.h>

namespace {
  constexpr auto DefaultSpeed = 5.6f;    //!< ���s�X�s�[�h
  constexpr auto InputThreshold = 3000;  //!< ����臒l
  constexpr auto Dash = "dash";          //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto Jump = "jump";          //!< �J�ڂ�����X�e�[�g�̕�����
}

void GlassHeart::State::StateRun::Enter() {
  _owner.SetForwardSpeed(DefaultSpeed);
  // ����A�j���[�V�������Đ�
  _owner.GetModelAnime().ChangeAnime(Dash, true);
}

void GlassHeart::State::StateRun::Input(AppFrame::Input::InputManager& input) {
  auto right = _owner.RightRotation();
  auto left = _owner.LeftRotation();
  auto& game = _owner.GetGame();
  // A�{�^���������ꂽ��W�����v��Ԃֈڍs
  if (input.GetJoyPad().GetXTriggerButtonA()) {
    game.GetSoundManager().Play(Jump);
    _owner.GetStateManage().PushBack(Jump);
  }
  // �X�e�B�b�N���͂�����Έړ�
  if (input.GetJoyPad().GetAnalogStickLX() >= InputThreshold) {
    // �E�����Ɍ�����ύX
    _owner.SetRotation(VGet(0.0f, right, 0.0f));
  }
  else if (input.GetJoyPad().GetAnalogStickLX() <= -InputThreshold) {
    // �������Ɍ�����ύX
    _owner.SetRotation(VGet(0.0f, left, 0.0f));
  }
  else {
    // �������͂�������΃A�C�h����Ԃֈڍs
    _owner.GetStateManage().PopBack();
  }
}
/** �X�V���� */
void GlassHeart::State::StateRun::Update() {
  // �ړ�����
  _owner.Move(VScale(_owner.GetForward(), _owner.GetForwardSpeed()));
}