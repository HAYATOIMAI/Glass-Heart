/*****************************************************************//**
 * @file   StateIdle.cpp
 * @brief  �A�C�h����ԃN���X�̏���
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "StateIdle.h"
#include <AppFrame.h>
#include "../Application/GameMain.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"
#include "../Collision/CollisionManager.h"

namespace {
  constexpr std::int_fast16_t RecastTime = 5;
  constexpr auto Hit = 1;                //!< �q�b�g�������̃t���O
  constexpr auto Idle = "Idle";          //!< �J�ڂ�����X�e�[�g
  constexpr auto Fall = "Fall";          //!< �J�ڂ�����X�e�[�g
  constexpr auto Run = "run";            //!< �J�ڂ�����X�e�[�g
}

 /** ��������� */
void GlassHeart::State::StateIdle::Enter() {
  // �Q�[���J�n���v���C���[�̐F�𔒂ɂ���
  if (_resetFlag == false) {
    _owner.SetWhite();
    _resetFlag = true;
  }

  _owner.SetForwardSpeed(0.0f);
  // �ҋ@���[�V�������Đ�
  _owner.GetModelAnime().ChangeAnime(Idle, true);
}
/** ���͏��� */
void GlassHeart::State::StateIdle::Input(AppFrame::Input::InputManager& input) {
  auto& game = _owner.GetGame();
  // �X�e�B�b�N���͂�����Έړ�
  if (input.GetJoyPad().GetXinputThumbLX()) {
    // �����Ԃ̌��ʉ����Đ�
    game.GetSoundManager().PlayLoop(Run);
    _owner.GetStateManage().PushBack("Run");
  }
  else if (!input.GetJoyPad().GetXinputThumbLX()) {
    game.GetSoundManager().StopSound(Run);
  }
  // A�{�^���������ꂽ��W�����v��Ԃֈڍs
  if (input.GetJoyPad().GetXTriggerButtonA() && _recastCnt == 0) {
    // �W�����v��Ԃ̌��ʉ����Đ�
    game.GetSoundManager().Play("jump");
    // ���͂𐧌�
    _recastCnt = RecastTime;
    _owner.GetStateManage().PushBack("Jump");
  }
}
/** �X�V���� */
void GlassHeart::State::StateIdle::Update() {
  // ���͐����̈׃J�E���^������
  if (_recastCnt > 0) {
    --_recastCnt;
  }
  // �v���C���[�̐F�Ə��u���b�N�̐F�������ꍇ����������
  auto pos = _owner.GetPosition();
  // �����b�V���Ɛ����ł̓����蔻��
  auto state = static_cast<std::int_fast8_t>(_owner.GetColourState());
  pos = _owner.GetCollision().GetIsHitFloor().CheckHitFloor(pos, { 0.f, -10.f, 0.f }, state);
  // �F�Ɋ֌W�Ȃ�������u���b�N�Ɠ������Ă��Ȃ�������
  if (_owner.GetCollision().GetIsHitFloor().GetHitFloor().HitFlag == 0) {
    //
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
      if (_owner.GetCollision().GetIsHitFloor().GetBThrough().HitFlag == Hit) {
        _owner.GetStateManage().GoToState("Fall");
      }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
      if (_owner.GetCollision().GetIsHitFloor().GetWThrough().HitFlag == Hit) {
        _owner.GetStateManage().GoToState("Fall");
      }
    }
  }
  _owner.SetPosition(pos);
}