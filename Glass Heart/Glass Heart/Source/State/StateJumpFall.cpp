/*********************************************************************
 * @file   StateJumpFall.cpp
 * @brief  �W�����v���~��Ԃ̐錾
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "StateJumpFall.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../Application/GameMain.h"
#include <numbers>

namespace {
  constexpr auto StraifVector = 6.5f;    //!< �󒆈ړ��p��X���ړ���
  constexpr auto Gravity = -0.6f;        //!< �d�͉����x
  constexpr auto InputThreshold = 5000;  //!< ����臒l
  constexpr auto InputThresholdMin = 1;  //!< ���͍Œ�l
  constexpr auto Hit = 1;                //!< �q�b�g�������̃t���O
  constexpr auto Idle = "Idle";          //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto JumpEnd = "Jump_End";   //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto Run = "run";            //!< �J�ڂ�����X�e�[�g�̕�����
}
/** ��������� */
void GlassHeart::State::StateJumpFall::Enter() {
  // �������̃A�j���[�V�������Đ�
  _owner.GetModelAnime().ChangeAnime(JumpEnd, true);
  // SE�̍Đ����~
  auto& game = _owner.GetGame();
  game.GetSoundManager().StopSound(Run);
}
/** ���͏��� */
void GlassHeart::State::StateJumpFall::Input(AppFrame::Input::InputManager& input) {
  auto right = _owner.RightRotation();
  auto left = _owner.LeftRotation();
  _owner.SetForwardSpeed(0.f);
  if (input.GetJoyPad().GetAnalogStickLX() >= InputThreshold && input.GetJoyPad().GetAnalogStickLX() > InputThresholdMin) {
    // �E�����Ɍ�����ύX
    _owner.SetRotation(VGet(0.0f, right, 0.0f));
    _owner.SetForwardSpeed(StraifVector);
  }
  if (input.GetJoyPad().GetAnalogStickLX() <= -InputThreshold && input.GetJoyPad().GetAnalogStickLX() < InputThresholdMin) {
    // �������Ɍ�����ύX
    _owner.SetRotation(VGet(0.0f, left, 0.0f));
    _owner.SetForwardSpeed(StraifVector);
  }
}
/** �X�V���� */
void GlassHeart::State::StateJumpFall::Update() {
  auto pos = _owner.GetPosition();
  // �ړ��ʃx�N�g�����擾
  auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
  // �W�����v���~����
  auto jumpVelocity = _owner.GetJumpVelocity();
  jumpVelocity.y += Gravity;
  _owner.SetJumpVelocity(jumpVelocity);

  forward.y = jumpVelocity.y;
  // �v���C���[�̐F���擾
  auto state = static_cast<int> (_owner.GetColourState());
  // �󒆂̑���̒�ʂƑ��ʔ��菈��
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
  // ���Ƃ̓����蔻��
  pos = _owner.GetCollision().GetIsHitJumpStand().CheckJumpStand(pos, { 0.f, forward.y, 0.f }, state);
  // �������Ă�����ҋ@��Ԃֈڍs
  if (_owner.GetCollision().GetIsHitJumpStand().GetStand().HitFlag == Hit) {
    _owner.GetStateManage().GoToState(Idle);
  }
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    if (_owner.GetCollision().GetIsHitJumpStand().GetWThrough().HitFlag == Hit) {
      _owner.GetStateManage().GoToState(Idle);
    }
  }
  if (_owner.GetColourState() == Player::Player::ColourState::White) {
    if (_owner.GetCollision().GetIsHitJumpStand().GetBThrough().HitFlag == Hit) {
      _owner.GetStateManage().GoToState(Idle);
    }
  }
  // ���S�������郁�b�V���Ɠ����蔻��
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    pos = _owner.GetCollision().GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
  }
  // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
  if (_owner.GetCollision().GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
      _owner.ResetPos();
    }
  }
  // ���S�������郁�b�V���Ɠ����蔻��
  if (_owner.GetColourState() == Player::Player::ColourState::White) {
    pos = _owner.GetCollision().GetIsHitBDeathMesh().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
  }
  // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
  if (_owner.GetCollision().GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
      _owner.ResetPos();
    }
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    }
  }
  // ���W�X�V
  _owner.SetPosition(pos);
}