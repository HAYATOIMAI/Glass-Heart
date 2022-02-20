
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
    constexpr auto StartPositionX = -150.0f;     //!< �v���C���[�̏����ʒuX
    constexpr auto StartPositionY = 35.0f;    //!< �v���C���[�̏����ʒuY
    constexpr auto StartPositionZ = -140.0f;  //!< �v���C���[�̏����ʒuZ
}

using namespace GlassHeart::Player;

/** �R���X�g���N�^ */
Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
    _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
    _radius = 25.0f;
}
/** ���͏��� */
void Player::Input(AppFrame::InputManager& input) {
    _cameraManage->Input(input);
    _angularSpeed = 0;
    _stateManage->Input(input);
    //LB�{�^���������ƐF�ύX
    if (input.GetJoyPad().GetXinputLeftShoulder() && _colourCount == 0) {
        //�A�Ŗh�~�̂���1�b(60�t���[��)�ԓ��͂𐧌�
        ColorCollisionDetectionSystem();
        _colourCount = 60;
    }
    // B�{�^���������ƃ`�F�b�N�|�C���g�ɕۑ�
    if (_hitFlag == true) {

        if (input.GetJoyPad().GetXTriggerButtonB()) {

            _checkPointFlag = true;
        }
    }
}
/** �X�V���� */
void Player::Process() {
    // ���͐����̈׃J�E���^������
    if (_colourCount > 0) {
        --_colourCount;
    }
    // �p�x�̍X�V
    auto angle = GetRotation();
    angle.y += _angularSpeed;
    SetRotation(angle);
    // ��Ԃ̍X�V
    _stateManage->Update();
    // ���[���h�s��̍X�V
    ComputeWorldTransform();
    // ���f���̍X�V
    _modelAnimeManage->Update();
    // �J�����̍X�V
    _cameraManage->SetTarget(_position, GetForward());
    _cameraManage->Update();
    // �I�u�W�F�N�g�T�[�o�[�Ɉʒu�𑗐M
    GetObjectServer().Register("Player", _position);

    _lastPosition = _position;

    // �����̍ő�l��ۑ�
    if (_lastPosition.y < _position.y ) {
        _highestPosition = _lastPosition;
    }

    for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ite++) {

        if ((*ite)->GetObjectType() == ObjectBase::ObjectType::CheckPoint) {

            if (_collsionManage->CheckCircleToCircle(*this, **ite) == true) {
                _hitFlag = true;
            }
            else {
                _hitFlag = false;
            }
        }
    }

}
/** �`�揈�� */
void Player::Render() {
#ifdef _DEBUG
    //�v���C���[�̍��W��\��
    auto x = 0; auto y = 0; auto size = 32;
    auto i = 0; auto o = 32 * 6;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[X���W =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[Y���W =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 255, 255), "�v���C���[Z���W =  %.3f ", _position.z); y += size;
    // �F��Ԃ�\��
    DrawFormatString(i, o, GetColor(255, 255, 255), _stateName.c_str(), _crState); y += size;
    //�J�����̈ʒu��\��
    _cameraManage->Render();
    //DrawLine3D(VGet(_lastPosition.x, _lastPosition.y, _lastPosition.z), VGet(_position.x, _position.y / 200.0f, _position.z), GetColor(255, 0, 0));
    // �R���W��������\��
    _collsionManage->Render();
#endif // _DEBUG
    _stateManage->Draw();
}
/** ���[���h���W�ϊ� */
void Player::ComputeWorldTransform() {
    auto world = MGetScale(_scale);
    world = MMult(world, MGetRotZ(_rotation.z));
    world = MMult(world, MGetRotX(_rotation.x));
    world = MMult(world, MGetRotY(_rotation.y + std::numbers::pi_v<float>));
    _worldTransform = MMult(world, MGetTranslate(_position));
}
/** �ړ����� */
void Player::Move(const VECTOR& forward) {
    auto pos = _position;
    // X�����݈̂ړ���ʒu����^���ɐ�������
    pos = _collsionManage->CheckHitFloor(pos, { forward.x, forward.y, 0 });
    //Y����
    pos = _collsionManage->CheckHitFloor(pos, { forward.x, forward.y, forward.z });

    pos = _collsionManage->CheckHitWall(pos, { forward.x, forward.y, 0.f });
    // Y����
    pos = _collsionManage->CheckHitWall(pos, { forward.x, forward.y, forward.z });

    pos = _collsionManage->CheckHitDeathFloor(pos, { forward.x, forward.y, 0.f });

    pos = _collsionManage->CheckHitDeathFloor(pos, { forward.x, forward.y, forward.z });

    // �F��Ԃ����̂Ƃ��̂ݍ��̃��b�V���Ɣ�����s��
    if (_crState == ColourState::White ) {

        pos = _collsionManage->CheckThroughBMesh(pos, { forward.x, forward.y, 0.f });

       pos = _collsionManage->CheckThroughBMesh(pos, { forward.x, forward.y, forward.z }); 

        pos = _collsionManage->CheckThroughBWallMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckThroughBWallMesh(pos, { forward.x, forward.y,  forward.z });
    }
    // �F��Ԃ����̂Ƃ��̂ݔ��̃��b�V���Ɣ�����s��
    if (_crState == ColourState::Black) {
        // X����
        pos = _collsionManage->CheckThroughWMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckThroughWMesh(pos, { forward.x, forward.y, forward.z});

        pos = _collsionManage->CheckThroughWWallMesh(pos, { forward.x, forward.y, 0.f });

        pos = _collsionManage->CheckThroughWWallMesh(pos, { forward.x, forward.y, forward.z});
    }

    // ���W�X�V
    _position = pos;
}
/** �F���菈�� */
void Player::ColorCollisionDetectionSystem() {

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

void Player::ResetPos() {

    if (_collsionManage->GetDeathMesh().HitFlag == 1) {

        if (_checkPointFlag == true) {

            auto checkPos = GetObjectServer().GetPosition("CheckPoint");
            _position = checkPos;

        }
        else {

            _position = VGet(StartPositionX, StartPositionY, StartPositionZ);

        }
    }
}

void GlassHeart::Player::Player::ReturnCheckPoint()
{
}
