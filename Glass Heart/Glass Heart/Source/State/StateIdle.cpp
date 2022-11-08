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
  constexpr int_fast16_t RecastTime = 5;                  //!< �W�����v�A�Ŗh�~�p���L���X�g�^�C��
  constexpr VECTOR LineSegment = { 0.0f, -10.0f, 0.0f };  //!< �����蔻��Ɏg�p��������̒���
  constexpr auto Hit = 1;                                 //!< �q�b�g�������̃t���O
  constexpr auto Idle = "idle";                           //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto RunSound = "run";                        //!< �Đ�����T�E���h�̕�����
  constexpr auto RunState = "Run";                        //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto JumpSound = "jump";                      //!< �Đ�����T�E���h�̕�����
  constexpr auto JumpState = "Jump";                      //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto StateFall = "Fall";                      //!< �J�ڂ�����X�e�[�g�̕�����
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
    game.GetSoundManager().PlayLoop(RunSound);
    _owner.GetStateManage().PushBack(RunState);
  }
  else if (!input.GetJoyPad().GetXinputThumbLX()) {
    game.GetSoundManager().StopSound(RunSound);
  }
  // A�{�^���������ꂽ��W�����v��Ԃֈڍs
  if (input.GetJoyPad().GetXTriggerButtonA() && _recastCnt == 0) {
    // �W�����v��Ԃ̌��ʉ����Đ�
    game.GetSoundManager().Play(JumpSound);
    // ���͂𐧌�
    _recastCnt = RecastTime;
    _owner.GetStateManage().PushBack(JumpState);
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
  auto state = static_cast<int_fast16_t>(_owner.GetColourState());
  pos = _owner.GetCollision().GetIsHitFloor().CheckHitFloor(pos, LineSegment, state);
  // �F�Ɋ֌W�Ȃ�������u���b�N�Ɠ������Ă��Ȃ�������
  if (_owner.GetCollision().GetIsHitFloor().GetHitFloor().HitFlag == 0) {
    //
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
      if (_owner.GetCollision().GetIsHitFloor().GetBThrough().HitFlag == Hit) {
        _owner.GetStateManage().GoToState(StateFall);
      }
    }
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
      if (_owner.GetCollision().GetIsHitFloor().GetWThrough().HitFlag == Hit) {
        _owner.GetStateManage().GoToState(StateFall);
      }
    }
  }
  _owner.SetPosition(pos);
}