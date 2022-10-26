/*********************************************************************
 * @file   StateJumpUp.cpp
 * @brief  �㏸��Ԃ̐錾
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/

#include "StateJumpUp.h"
#include "../Player/Player.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"

namespace {
  constexpr auto StraifVector = 6.5f;                      //!< �󒆈ړ��p��X���ړ��� 
  constexpr auto Gravity = -0.8f;                          //!< �d�͉����x
  constexpr auto InputThreshold = 5000;                    //!< ����臒l
  constexpr auto InputThresholdMin = 1;                    //!< ���͍Œ�l
  constexpr auto Hit = 1;                                  //!< �q�b�g�������̃t���O
  constexpr auto JumpLoop = "Jump_Loop";                   //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr auto JumpFall = "JumpFall";                    //!< �J�ڂ�����X�e�[�g�̕�����
  constexpr VECTOR JumpVeclosity = { 0.0f, 24.5f, 0.0f };  //!< �㏸��
}

GlassHeart::State::StateJumpUp::StateJumpUp(Player::Player& owner) : State::StateBase{ owner } {}
/** ��������� */
void GlassHeart::State::StateJumpUp::Enter() {
  // �W�����v���x�ݒ�
  VECTOR jumpbase = JumpVeclosity;
  _owner.SetJumpVelocity(jumpbase);
  // �W�����v���̃A�j���[�V�������Đ�
  _owner.GetModelAnime().ChangeAnime(JumpLoop, true);
}
/** ���͏��� */
void GlassHeart::State::StateJumpUp::Input(AppFrame::Input::InputManager& input) {
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
void GlassHeart::State::StateJumpUp::Update() {
  auto pos = _owner.GetPosition();
  // �ړ��ʃx�N�g�����擾
  auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
  // �W�����v�㏸����
  auto jumpVelocity = _owner.GetJumpVelocity();
  jumpVelocity.y += Gravity;
  forward.y = jumpVelocity.y;
  // �v���C���[�̐F���擾
  int state = static_cast<int> (_owner.GetColourState());
  // �󒆂̑���̒�ʂƑ��ʔ��菈��
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { 0.f, forward.y, 0.f }, state);
  //�@�������Ă����痎��
  if (_owner.GetCollision().GetIsHitSideBottom().GetSideAndBottom().HitNum > 0) {
    jumpVelocity.y = 0.0f;
  }
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    // �󒆂̑���ƃv���C���[�̐F���قȂ��Ă����痎��
    if (_owner.GetCollision().GetIsHitSideBottom().GetWWallThroughMesh().HitNum > 0) {
      jumpVelocity.y = 0.0f;
    }
  }
  // �󒆂̑���ƃv���C���[�̐F���قȂ��Ă����痎��
  if (_owner.GetColourState() == Player::Player::ColourState::White) {
    if (_owner.GetCollision().GetIsHitSideBottom().GetBWallThroughMesh().HitNum > 0) {
      jumpVelocity.y = 0.0f;
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
  // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
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

  //�ړ��x�N�g�����}�C�i�X�ɂȂ����牺�~��ԂɈڍs
  if (jumpVelocity.y <= 0.0f) {
    _owner.GetStateManage().GoToState(JumpFall);
  }
  _owner.SetJumpVelocity(jumpVelocity);
}