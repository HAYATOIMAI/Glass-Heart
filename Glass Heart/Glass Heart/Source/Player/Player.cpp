
/*****************************************************************//**
 * @file   Player.cpp
 * @brief  �v���C���[�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "Player.h"
#include "../Object/ObjectServer.h"
#include "../Camera/CameraManager.h"
#include "../Collision/CollisionManager.h"
#include "../Model/ModelAnimeManager.h"
#include "../State/StateManager.h"
#include "../Application/GameMain.h"
#include <numbers>

namespace {
    //constexpr auto StartPositionX = 25600.0f;  //!< �e�X�g�p�v���C���[�̏����ʒuX
    //constexpr auto StartPositionY = 12420.0f;  //!< �e�X�g�p�v���C���[�̏����ʒuY
    //constexpr auto StartPositionZ = -55.0f;  //!< �e�X�g�p�v���C���[�̏����ʒuZ
    constexpr auto StartPositionX = -150.0f;  //!< �v���C���[�̏����ʒuX
    constexpr auto StartPositionY = 35.0f;    //!< �v���C���[�̏����ʒuY
    constexpr auto StartPositionZ = -55.0f;  //!< �v���C���[�̏����ʒuZ
    constexpr auto Recast = 20;  //!<�@�F�ύX���L���X�g�^�C�� 
    constexpr auto RightRotation = 90.0f * (std::numbers::pi_v<float> / 180.0f); //!< �E�����̊p�x
    constexpr auto LeftRotation = 270.0f * (std::numbers::pi_v<float> / 180.0f);  //!< �������̊p�x
}

using namespace GlassHeart;

/** �R���X�g���N�^ */
Player::Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _rotation = VGet(0.0f, RightRotation, 0.0f);
    _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
    _radius = 25.0f;
}
/** ���͏��� */
void Player::Player::Input(AppFrame::InputManager& input) {
    if (_deadFlag == false) {
        _cameraManage->Input(input);
        _stateManage->Input(input);
    }
    //LB�{�^���������ƐF�ύX
    if (input.GetJoyPad().GetXinputLeftShoulder() && _recastCount == 0) {
        //�A�Ŗh�~�̂���20�t���[���ԓ��͂𐧌�
        ColorCollisionDetectionSystem();
        _recastCount = Recast;
    }
    // B�{�^���������ƃ`�F�b�N�|�C���g�ɕۑ�
    if (_hitFlag == true) {

        if (input.GetJoyPad().GetXTriggerButtonB()) {
            _checkPointFlag = true;
        }
    }
#ifdef _DEBUG
    if (input.GetJoyPad().GetXinputRightShoulder()) {
        _rotation = VGet(0.0f, RightRotation, 0.0f);
        _position = VGet(StartPositionX, StartPositionY + 20, StartPositionZ);
    }
#endif // _DEBUG
}
/** �X�V���� */
void Player::Player::Process() {
    // ���͐����̈׃J�E���^������
    if (_recastCount > 0) {
        --_recastCount;
    }
    if (_deathCoolCount > 0) {
        --_deathCoolCount;
    }

    if (_deadFlag == false) {
        // ��Ԃ̍X�V
        _stateManage->Update();
        // ���[���h�s��̍X�V
        ComputeWorldTransform();
        // ���f���̍X�V
        _modelAnimeManage->Update();
    }
    if (GetCollision().GetWDeathMesh().HitNum >= 1) {
        if (GetColourState() == Player::Player::ColourState::White) {
            SetPosition(_position);
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (GetColourState() == Player::Player::ColourState::Black) {
            ResetPos();
        }
    }
    if (GetCollision().GetBDeathMesh().HitNum >= 1) {
        if (GetColourState() == Player::Player::ColourState::White) {
            ResetPos();
            // _owner.GetStateManage().PushBack("Dead");
        }
        if (GetColourState() == Player::Player::ColourState::Black) {
            SetPosition(_position);
        }
    }
    // �I�u�W�F�N�g�T�[�o�[�Ɉʒu�𑗐M
    GetObjectServer().Register("Player", _position);
    // �`�F�b�N�|�C���g�Ƃ̓����蔻��
    for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ite++) {
        // �I�u�W�F�N�g�^�C�v���`�F�b�N�|�C���g��������
        if ((*ite)->GetObjectType() == ObjectBase::ObjectType::CheckPoint) {
            // �~�`�Ɖ~�`�̓����蔻��(����������true��Ԃ�)
            if (_collsionManage->CheckCircleToCircle(*this, **ite) == true) {
                // ��������
                _hitFlag = true;
            }
            else {
                // ������Ȃ�����
                _hitFlag = false;
            }
        }
    }
#ifdef _DEBUG
    if (_position.y < -100.0f) {
        if (_checkPointFlag == true) {
            // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
            auto checkPos = GetObjectServer().GetPosition("CheckPoint");
            // �v���C���[�̍��W���`�F�b�N�|�C���g�ɂ���
            _position = checkPos;
        }
        else {
            _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
        }
    }
#endif // DEBUG
}
/** �`�揈�� */
void Player::Player::Render() {
#ifdef _DEBUG
    //�v���C���[�̍��W��\��
    auto x = 0; auto y = 0; auto size = 32;
    auto i = 0; auto o = 32 * 6; auto timeY = 32 * 10;
    auto white = GetColor(255, 255, 255);

    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[X���W =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[Y���W =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[Z���W =  %.3f ", _position.z); y += size;
    // �F��Ԃ�\��
    DrawFormatString(i, o, GetColor(255, 255, 255), _stateName.c_str(), _crState); y += size;
    //�J�����̈ʒu��\��
    //_cameraManage->Render();
#endif // _DEBUG
    _stateManage->Draw();
}
/** ���[���h���W�ϊ� */
void Player::Player::ComputeWorldTransform() {
    auto world = MGetScale(_scale);
    world = MMult(world, MGetRotZ(_rotation.z));
    world = MMult(world, MGetRotX(_rotation.x));
    world = MMult(world, MGetRotY(_rotation.y + std::numbers::pi_v<float>)); // ���f���̌����͂����Œ���
    _worldTransform = MMult(world, MGetTranslate(_position));
}
/** �ړ����� */
void Player::Player::Move(const VECTOR& forward) {
    auto pos = _position;

    int state = static_cast<int> (_crState);
    pos = _collsionManage->CheckHitSideAndBottom(pos, { forward.x, 0.f, 0.f }, state);
    pos = _collsionManage->CheckHitFloor(pos, { 0.f, -10.f, 0.f }, state);

    pos = _collsionManage->CheckHitBDeathMesh(pos, { 0.f, forward.y, 0.f });

    pos = _collsionManage->CheckHitWDeathMesh(pos, { 0.f, forward.y, 0.f });

    if (_collsionManage->GetHitFloor().HitFlag == 0) {
        GetStateManage().PushBack("Fall");
    }
    if (_crState == Player::ColourState::Black) {
        if (_collsionManage->GetWThrough().HitFlag == 0) {
            //GetStateManage().PushBack("Fall");
        }
    }
    if (_crState == Player::Player::ColourState::White) {
        if (_collsionManage->GetBThrough().HitFlag == 0) {
            //GetStateManage().GoToState("Fall");
        }
    }
    //if (_collsionManage->GetBDeathMesh().HitNum >= 1) {
    //    if (GetColourState() == Player::Player::ColourState::White) {
    //        //SetPosition(VGet(_position.x, _position.y, _position.z));
    //       GetStateManage().PushBack("Dead");
    //    }
    //    if (GetColourState() == Player::Player::ColourState::Black) {
    //        ResetPos();
    //    }
    //}
    //if (_collsionManage->GetWDeathMesh().HitNum >= 1) {
    //    if (GetColourState() == Player::Player::ColourState::White) {
    //        //SetPosition(VGet(_position.x, _position.y, _position.z));
    //         GetStateManage().PushBack("Dead");
    //    }
    //    if (GetColourState() == Player::Player::ColourState::Black) {
    //        ResetPos();
    //    }
    //}
    // ���W�X�V
    _position = pos;
}
/** �F���菈�� */
void Player::Player::ColorCollisionDetectionSystem() {
    if (_crState == ColourState::Black) {
        SetWhite();
    }
    else if (_crState == ColourState::White) {
        SetBlack();
    }
}

void GlassHeart::Player::Player::SetWhite() {
    auto animHandle = _modelAnimeManage->GetHandle();
    _stateName = "White";
    MV1SetFrameVisible(animHandle, 0, FALSE);
    MV1SetFrameVisible(animHandle, 1, TRUE);
    MV1SetFrameVisible(animHandle, 2, FALSE);
    MV1SetFrameVisible(animHandle, 3, TRUE);
    _crState = ColourState::White;
}

void GlassHeart::Player::Player::SetBlack() {
    auto animHandle = _modelAnimeManage->GetHandle();
    _stateName = "Black";
    MV1SetFrameVisible(animHandle, 1, FALSE);
    MV1SetFrameVisible(animHandle, 0, TRUE);
    MV1SetFrameVisible(animHandle, 3, FALSE);
    MV1SetFrameVisible(animHandle, 2, TRUE);
    _crState = ColourState::Black;
}

void Player::Player::ResetPos() {
    // �f�X���b�V���Ɠ������Ă�����
    if (_collsionManage->GetWDeathMesh().HitNum >= 1) {
        if (_deadFlag == false) {
            _deadFlag = true;
            _deathCoolCount = 120;
        }
        if (_checkPointFlag == true) {
            if (_deadFlag == true && _deathCoolCount == 0) {
                // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
                auto checkPos = GetObjectServer().GetPosition("CheckPoint");
                // �v���C���[�̍��W���`�F�b�N�|�C���g�ɂ���
                _position = checkPos;
                _deadFlag = false;
            }
        }
        else {
            if (_deadFlag == true && _deathCoolCount == 0) {
                _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
                _deadFlag = false;
            }
        }
    }
    if (_collsionManage->GetBDeathMesh().HitNum >= 1) {
        if (_deadFlag == false) {
            _deadFlag = true;
            _deathCoolCount = 120;
        }
        if (_checkPointFlag == true) {
            if (_deadFlag == true && _deathCoolCount == 0) {
                // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
                auto checkPos = GetObjectServer().GetPosition("CheckPoint");
                // �v���C���[�̍��W���`�F�b�N�|�C���g�ɂ���
                _position = checkPos;
                _deadFlag = false;
            }
        }
        else {
            if (_deadFlag == true && _deathCoolCount == 0) {
                _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
                _deadFlag = false;
            }
        }
    }
}