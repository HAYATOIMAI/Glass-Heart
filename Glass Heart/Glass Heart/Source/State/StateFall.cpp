/*********************************************************************
 * @file   StateFall.cpp
 * @brief  �v���C���[�̗����N���X�̏���
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
#include "../Object/ObjectServer.h"
#include <AppFrame.h>

namespace {
  constexpr auto AirMovementSpeed = 6.5f;              //!< �󒆈ړ��p��X���ړ���
  constexpr auto Gravity = -1.0f;                      //!< �d�͉����x
  constexpr auto RespawnArea = -300.0f;                //!< �G���A���E
  constexpr auto InputThresholdMax = 5000;             //!< ����臒l
  constexpr auto InputThresholdMin = 1;                //!< ���͍Œ�l
  constexpr auto Hit  = 1;                             //!< �q�b�g�������̃t���O
  constexpr auto Idle = "Idle";                        //!< �J�ڂ�����X�e�[�g
  constexpr auto Fall = "fall";                        //!< �J�ڂ�����X�e�[�g
  constexpr auto Run = "run";                          //!< �J�ڂ�����X�e�[�g
  constexpr auto CheckPoint = "CheckPoint";            //!< �I�u�W�F�N�g�T�[�o�[������W���擾����ׂ̕�����
  constexpr VECTOR Position = { -150.f, 60.f, -55.f }; //!< �ʒu���W
  constexpr VECTOR Velocity = { 0.0f, 5.5f, 0.0f };    //!< 
}

/** ��������� */
void GlassHeart::State::StateFall::Enter() {
  // �������[�V�������Đ�
  _owner.GetModelAnime().ChangeAnime(Fall, true);
  // ���ʉ����~
  auto& game = _owner.GetGame();
  game.GetSoundManager().StopSound(Run);
  // �������̂͂�����鋗�����Z�b�g
  _owner.SetJumpVelocity(Velocity);
}
/** ���͏��� */
void GlassHeart::State::StateFall::Input(AppFrame::Input::InputManager& input) {
  auto right = _owner.RightRotation();
  auto left = _owner.LeftRotation();
  _owner.SetForwardSpeed(0.f);
  if (input.GetJoyPad().GetAnalogStickLX() >= InputThresholdMax && input.GetJoyPad().GetAnalogStickLX() > InputThresholdMin) {
    // �E�����Ɍ�����ύX
    _owner.SetRotation(VGet(0.0f, right, 0.0f));
    _owner.SetForwardSpeed(AirMovementSpeed);
  }
  if (input.GetJoyPad().GetAnalogStickLX() <= -InputThresholdMax && input.GetJoyPad().GetAnalogStickLX() < InputThresholdMin) {
    // �������Ɍ�����ύX
    _owner.SetRotation(VGet(0.0f, left, 0.0f));
    _owner.SetForwardSpeed(AirMovementSpeed);
  }
}
/** �X�V���� */
void GlassHeart::State::StateFall::Update() {
  auto pos = _owner.GetPosition();
  // �ړ��ʃx�N�g�����擾
  auto forward = VScale(_owner.GetForward(), _owner.GetForwardSpeed());
  // ���~����
  auto jumpVelocity = _owner.GetJumpVelocity();
  jumpVelocity.y += Gravity;
  _owner.SetJumpVelocity(jumpVelocity);
  forward.y = jumpVelocity.y;
  // �v���C���[�̐F���擾
  auto state = static_cast<std::int_fast8_t> (_owner.GetColourState());
  // �󒆂̑���̒�ʂƑ��ʔ��菈��
  pos = _owner.GetCollision().GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.0f, 0.0f }, state);
  // ���Ƃ̓����蔻��
  pos = _owner.GetCollision().GetIsHitJumpStand().CheckJumpStand(pos, { 0.0f, forward.y, 0.0f }, state);
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
    pos = _owner.GetCollision().GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.0f, forward.y, 0.0f });
  }
  // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
  if (_owner.GetCollision().GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::Black) {
      _owner.ResetPos();
    }
  }
  // ���S�������郁�b�V���Ɠ����蔻��
  if (_owner.GetColourState() == Player::Player::ColourState::Black) {
    pos = _owner.GetCollision().GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.0f, forward.y, 0.0f });
  }
  // �v���C���[�̐F���قȂ��Ă����烊�X�|�[������
  if (_owner.GetCollision().GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    if (_owner.GetColourState() == Player::Player::ColourState::White) {
      _owner.ResetPos();
    }
  }
  // ���X�|�[������
  if (pos.y < RespawnArea) {
    if (_owner.GetCheckPointFlag() == true) {
      // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
      auto checkPos = _owner.GetObjectServer().GetPosition(CheckPoint);
      // �v���C���[�̍��W���`�F�b�N�|�C���g�ɂ���
      pos = checkPos;
    }
    else {
      pos = Position;
    }
  }
  // ���W�X�V
  _owner.SetPosition(pos);
}