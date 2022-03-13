
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
    constexpr auto StartPositionX = 8790.0f;  //!< �e�X�g�p�v���C���[�̏����ʒuX
    constexpr auto StartPositionY = 5705.000f;    //!< �e�X�g�p�v���C���[�̏����ʒuY
    constexpr auto StartPositionZ = -55.0f;  //!< �e�X�g�p�v���C���[�̏����ʒuZ
    //constexpr auto StartPositionX = -150.0f;  //!< �v���C���[�̏����ʒuX
    //constexpr auto StartPositionY = 35.0f;    //!< �v���C���[�̏����ʒuY
    //constexpr auto StartPositionZ = -55.0f;  //!< �v���C���[�̏����ʒuZ
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
    _cameraManage->Input(input);
    _angularSpeed = 0;
    _stateManage->Input(input);
    //LB�{�^���������ƐF�ύX
    if (input.GetJoyPad().GetXinputLeftShoulder() && _colourCount == 0) {
        //�A�Ŗh�~�̂���0.5�b(30�t���[��)�ԓ��͂𐧌�
        ColorCollisionDetectionSystem();
        _colourCount = Recast;
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
        _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
    }
#endif // _DEBUG
}
/** �X�V���� */
void Player::Player::Process() {
    // ���͐����̈׃J�E���^������
    if (_colourCount > 0) {
        --_colourCount;
    }
    // ��Ԃ̍X�V
    _stateManage->Update();
    // ���[���h�s��̍X�V
    ComputeWorldTransform();
    // ���f���̍X�V
    _modelAnimeManage->Update();
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
    if (_position.y < -600.0f) {
        _rotation = VGet(0.0f, RightRotation, 0.0f);
        _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
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
    //DrawLine3D(VGet(_lastPosition.x, _lastPosition.y, _lastPosition.z), VGet(_position.x, _position.y / 200.0f, _position.z), GetColor(255, 0, 0));
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

    pos = _collsionManage->CheckHitFloor(pos, { forward.x, forward.y, 0.f });

    pos = _collsionManage->CheckHitSecondFloor(pos, { forward.x, forward.y, 0.f });

    pos = _collsionManage->CheckHitSideAndBottom(pos, { forward.x, forward.y, 0.f });

    if (_collsionManage->GetFall().HitFlag == 0 ) {

        if (_collsionManage->GetSecondFall().HitFlag == 1) {
        }
        else if (_collsionManage->GetSecondFall().HitFlag == 0) {

            if (_collsionManage->GetBThrough().HitFlag == 0 || _collsionManage->GetWThrough().HitFlag == 0) {
                _stateManage->PushBack("Fall");
            }
        }
    }

    // �F��Ԃ����̂Ƃ��̂ݍ��̃��b�V���Ɣ�����s��
    if (_crState == ColourState::White ) {

        pos = _collsionManage->CheckThroughBMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckThroughBWallMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckFall(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckHitSecondFall(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckHitBDeathMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckHitSecondThroughBMesh(pos, { forward.x, forward.y, 0.f });
    }
    // �F��Ԃ����̂Ƃ��̂ݔ��̃��b�V���Ɣ�����s��
    if (_crState == ColourState::Black) {
        // X����
        pos = _collsionManage->CheckThroughWMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckThroughWWallMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckFall(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckHitSecondFall(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckHitWDeathMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckHitSecondThroughWMesh(pos, { forward.x, forward.y, 0.f });
    }
    // ���W�X�V
    _position = pos;
}
/** �F���菈�� */
void Player::Player::ColorCollisionDetectionSystem() {

    auto animHandle = _modelAnimeManage->GetHandle();

    if (_crState == ColourState::Black) {
        _stateName = "White";
        MV1SetFrameVisible(animHandle, 0, FALSE);
        MV1SetFrameVisible(animHandle, 1, TRUE);
        MV1SetFrameVisible(animHandle, 2, FALSE);
        MV1SetFrameVisible(animHandle, 3, TRUE);
        _crState = ColourState::White;
    }
    else if (_crState == ColourState::White) {
        _stateName = "Black";
        MV1SetFrameVisible(animHandle, 1, FALSE);
        MV1SetFrameVisible(animHandle, 0, TRUE);
        MV1SetFrameVisible(animHandle, 3, FALSE);
        MV1SetFrameVisible(animHandle, 2, TRUE);
        _crState = ColourState::Black;
    }
}

void Player::Player::ResetPos() {
    // �f�X���b�V���Ɠ������Ă�����
    if (_collsionManage->GetWDeathMesh().HitNum >= 1) {
        // 
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
    if (_collsionManage->GetBDeathMesh().HitNum >= 1) {
        // 
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
}

void Player::Player::ReturnCheckPoint() {}
