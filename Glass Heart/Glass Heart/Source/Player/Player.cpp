/*****************************************************************//**
 * @file   Player.cpp
 * @brief  �v���C���[�̏���
 *
 * @author Hayato Imai, Haruki Ikeda, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "Player.h"
#include "../Object/ObjectServer.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"

namespace {
  constexpr int_fast16_t Recast = 20;                       //!< �F�ύX���L���X�g�^�C��
  constexpr int_fast16_t DeathCoolTime = 120;               //!< ���S�������̕����܂ł̃N�[���^�C��
  constexpr VECTOR PlayerPosition  = { -150.0f, 40.0f, -55.0f };  //!< �v���C���[�̈ʒu���W
  constexpr VECTOR LineLength = { 0.0f, -10.0f, 0.0f };     //!< �����蔻��Ɏg�p��������̒���
  constexpr auto Hit = 1;                                   //!< �q�b�g�������̃t���O
  constexpr auto Radius = 20.f;                             //!< �`�F�b�N�|�C���g�Ƃ̓����蔻��p���a
  constexpr auto RespawnArea = -300.0f;                     //!< ���X�|�[���G���A
  constexpr auto ObjectToRegister = "Player";               //!< �I�u�W�F�N�g���Ǘ�����}�l�[�W���[�ɓo�^���镶����
  constexpr auto DeathSoundeffect = "death";                //!< �Đ�����SE
  constexpr auto CheckPoint = "CheckPoint";                 //!< 
  constexpr auto Fall = "Fall";                             //!<
  constexpr auto White = "White";                           //!<
  constexpr auto Black = "Black";                           //!<
}

/** �R���X�g���N�^ */
GlassHeart::Player::Player::Player(Application::GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
  auto right = RightRotation();
  _rotation = VGet(0.0f, right, 0.0f);
  _position = PlayerPosition;
  _radius = Radius;  // �`�F�b�N�|�C���g�Ƃ̓����蔻��p���a���Z�b�g
}
/** ���͏��� */
void GlassHeart::Player::Player::Input(AppFrame::Input::InputManager& input) {
  if (_deadFlag == false) {
    // �J�����̍X�V
    _cameraManage->Input(input);
    // �X�e�[�g�̍X�V
    _stateManage->Input(input);
  }
  //LB�{�^���������ƐF�ύX
  if (input.GetJoyPad().GetXinputLeftShoulder() && _recastCount == 0) {
    //�A�Ŗh�~�̂���20�t���[���ԓ��͂𐧌�
    ColorChange();
    _recastCount = Recast;
  }
#ifdef _DEBUG
  // �f�o�b�O�pLB�{�^���������ƃv���C���[�̈ʒu��������
  if (input.GetJoyPad().GetXinputRightShoulder()) {
    auto right = RightRotation();
    _rotation = VGet(0.0f, right, 0.0f);
    _position = Position;
  }
#endif // _DEBUG
}
/** �X�V���� */
void GlassHeart::Player::Player::Process() {
  // ���͐����̈׃J�E���^������
  if (_recastCount > 0) {
    --_recastCount;
  }
  if (_deathCoolCount > 0) {
    --_deathCoolCount;
  }
  // �F���Ƃ̏Փ˔���
  CollisionDetectionByColor();

  if (_deadFlag == false) {
    // ��Ԃ̍X�V
    _stateManage->Update();
    // ���[���h�s��̍X�V
    ComputeWorldTransform();
    // ���f���A�j���[�V�����̍X�V
    _modelAnimeManage->Update();
  }
  // �I�u�W�F�N�g�T�[�o�[�Ɉʒu�𑗐M
  GetObjectServer().Register(ObjectToRegister, _position);
  // �`�F�b�N�|�C���g�Ƃ̏Փ˔���
  IsHitCheckPoint();
#ifdef _DEBUG
  if (_position.y < RespawnArea) {
    if (_checkPointFlag == true) {
      // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
      auto checkPos = GetObjectServer().GetPosition(CheckPoint);
      // �v���C���[�̍��W���`�F�b�N�|�C���g�̍��W�ɂ���
      _position = checkPos;
    }
    else {
      _position = PlayerPosition;
    }
  }
#endif // DEBUG
}
/** �`�揈�� */
void GlassHeart::Player::Player::Render() {
  // �X�e�[�g�̍X�V
  _stateManage->Draw();
#ifdef _DEBUG
  // �f�o�b�O�p �v���C���[�̍��W��\��
  auto x = 0; auto y = 0; auto size = 32;
  auto i = 0; auto o = 32 * 6; auto timeY = 32 * 10;
  auto white = GetColor(255, 255, 255);

  SetFontSize(size);
  DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[X���W =  %.3f ", _position.x); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[Y���W =  %.3f ", _position.y); y += size;
  DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[Z���W =  %.3f ", _position.z); y += size;
  // �F��Ԃ�\��
  DrawFormatString(i, o, GetColor(255, 255, 255), _stateName.c_str(), _colorState); y += size;
#endif // _DEBUG
}
/** ���[���h���W�ϊ� */
void GlassHeart::Player::Player::ComputeWorldTransform() {
  auto world = MGetScale(_scale);
  world = MMult(world, MGetRotZ(_rotation.z));
  world = MMult(world, MGetRotX(_rotation.x));
  world = MMult(world, MGetRotY(_rotation.y + DX_PI_F)); // ���f���̌����͂����Œ���
  _worldTransform = MMult(world, MGetTranslate(_position));
}
/** �ړ����� */
void GlassHeart::Player::Player::Move(const VECTOR& forward) {
  auto pos = _position;
  // �v���C���[�̐F���擾
  auto state = static_cast<int_fast16_t> (_colorState);
  // �󒆂̑���̒�ʂƑ��ʔ��菈��
  pos = _collsionManage->GetIsHitSideBottom().CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
  // ���Ƃ̓����蔻��
  pos = _collsionManage->GetIsHitFloor().CheckHitFloor(pos, LineLength, state);
  // ���S�������郁�b�V���Ɠ����蔻��
  pos = _collsionManage->GetIsHitBDeathMesh().CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });
  // ���S�������郁�b�V���Ɠ����蔻��
  pos = _collsionManage->GetIsHitWDeathMesh().CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });
  // ����ƒ�ʂƑ��ʂɓ������Ă��Ȃ������痎����Ԃֈڍs
  if (_collsionManage->GetIsHitFloor().GetHitFloor().HitFlag == 0 && 
    _collsionManage->GetIsHitSideBottom().GetSideAndBottom().HitNum == 0) {
    GetStateManage().GoToState(Fall);
  }
  // ���W�X�V
  _position = pos;
}
/** �F�ύX���� */
void GlassHeart::Player::Player::ColorChange() {
  if (_colorState == ColourState::Black) {
    SetWhite();
  }
  else if (_colorState == ColourState::White) {
    SetBlack();
  }
}
/** ���ɐݒ� */
void GlassHeart::Player::Player::SetWhite() {
  auto animHandle = _modelAnimeManage->GetHandle();
  _stateName = White;
  MV1SetFrameVisible(animHandle, 0, FALSE);
  MV1SetFrameVisible(animHandle, 1, TRUE);
  MV1SetFrameVisible(animHandle, 2, FALSE);
  MV1SetFrameVisible(animHandle, 3, TRUE);
  _colorState = ColourState::White;
}
/** ���ɐݒ� */
void GlassHeart::Player::Player::SetBlack() {
  auto animHandle = _modelAnimeManage->GetHandle();
  _stateName = Black;
  MV1SetFrameVisible(animHandle, 1, FALSE);
  MV1SetFrameVisible(animHandle, 0, TRUE);
  MV1SetFrameVisible(animHandle, 3, FALSE);
  MV1SetFrameVisible(animHandle, 2, TRUE);
  _colorState = ColourState::Black;
}
/** ���X�|�[���V�X�e�� */
void GlassHeart::Player::Player::ResetPos() {
  // �����f�X���b�V���Ɠ������Ă�����
  if (_collsionManage->GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    if (_deadFlag == false) {
      // ���S���̌��ʉ����Đ�
      GetGame().GetSoundManager().Play(DeathSoundeffect);
      _deadFlag = true;
      _deathCoolCount = DeathCoolTime;
    }
    // �`�F�b�N�|�C���g�Ɠ������Ă�����v���C���[�̍��W���`�F�b�N�|�C���g�̈ʒu�ɂ���
    if (_checkPointFlag == true) {
      if (_deadFlag == true && _deathCoolCount == 0) {
        // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
        auto checkPos = GetObjectServer().GetPosition(CheckPoint);
        // �v���C���[�̍��W���`�F�b�N�|�C���g�̍��W�ɂ���
        _position = checkPos;
        _deadFlag = false;
      }
    }
    else {
      // �`�F�b�N�|�C���g�Ɠ������Ă��Ȃ������珉���ʒu�ɖ߂�
      if (_deadFlag == true && _deathCoolCount == 0) {
        _position = PlayerPosition;
        _deadFlag = false;
      }
    }
  }
  // �����f�X���b�V���Ɠ������Ă�����
  if (_collsionManage->GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    if (_deadFlag == false) {
      // ���S���̌��ʉ����Đ�
      GetGame().GetSoundManager().Play(DeathSoundeffect);
      _deadFlag = true;
      _deathCoolCount = DeathCoolTime;
    }
    // �`�F�b�N�|�C���g�Ɠ������Ă�����v���C���[�̍��W���`�F�b�N�|�C���g�̈ʒu�ɂ���
    if (_checkPointFlag == true) {
      if (_deadFlag == true && _deathCoolCount == 0) {
        // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
        auto checkPos = GetObjectServer().GetPosition(CheckPoint);
        // �v���C���[�̍��W���`�F�b�N�|�C���g�̍��W�ɂ���
        _position = checkPos;
        _deadFlag = false;
      }
    }
    else {
      // �`�F�b�N�|�C���g�Ɠ������Ă��Ȃ������珉���ʒu�ɖ߂�
      if (_deadFlag == true && _deathCoolCount == 0) {
        _position = PlayerPosition;
        _deadFlag = false;
      }
    }
  }
}

void GlassHeart::Player::Player::CollisionDetectionByColor() {
  // �����f�X���b�V���Ɠ������Ă�����
  if (GetCollision().GetIsHitWDeathMesh().GetWDeathMesh().HitNum >= Hit) {
    // �����F�Ȃ�Έʒu�͂��̂܂܂ɂ���
    if (GetColourState() == Player::Player::ColourState::White) {
      SetPosition(_position);
    }
    // �Ⴄ�F�Ȃ�Έʒu�����Z�b�g����
    if (GetColourState() == Player::Player::ColourState::Black) {
      ResetPos();
    }
  }
  // �����f�X���b�V���Ɠ������Ă�����
  if (GetCollision().GetIsHitBDeathMesh().GetBDeathMesh().HitNum >= Hit) {
    // �Ⴄ�F�Ȃ�Έʒu�����Z�b�g����
    if (GetColourState() == Player::Player::ColourState::White) {
      ResetPos();
    }
    // �����F�Ȃ�Έʒu�͂��̂܂܂ɂ���
    if (GetColourState() == Player::Player::ColourState::Black) {
      SetPosition(_position);
    }
  }
}

void GlassHeart::Player::Player::IsHitCheckPoint() {
  // �`�F�b�N�|�C���g�Ƃ̓����蔻��
  for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ++ite) {
    // �I�u�W�F�N�g�^�C�v���`�F�b�N�|�C���g��������
    if ((*ite)->GetObjectType() == ObjectBase::ObjectType::CheckPoint) {
      // �~�`�Ɖ~�`�̓����蔻��(����������true��Ԃ�)
      if (_collsionManage->GetIsHitCircle().CheckCircleToCircle(*this, **ite) == true) {
        // ��������
        _hitFlag = true;
        _checkPointFlag = true;
      }
      else {
        // ������Ȃ�����
        _hitFlag = false;
      }
    }
  }
}
