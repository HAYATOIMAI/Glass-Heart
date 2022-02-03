
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
    constexpr auto PlayerPositionX = 0.0f;     //!< �v���C���[�̏����ʒuX
    constexpr auto PlayerPositionY = 70.0f;    //!< �v���C���[�̏����ʒuY
    constexpr auto PlayerPositionZ = -140.0f;  //!< �v���C���[�̏����ʒuZ
}

using namespace GlassHeart::Player;

/** �R���X�g���N�^ */
Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {

    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
    _position = VGet(PlayerPositionX, PlayerPositionY, PlayerPositionZ);
    
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
    DrawFormatString(i, o, GetColor(255, 0, 0), _stateName.c_str(), _crState); y += size;
    //�J�����̈ʒu��\��
    _cameraManage->Render();
    DrawLine3D(VGet(_lastPosition.x, _lastPosition.y, _lastPosition.z), VGet(_position.x, _position.y / 200.0f, _position.z), GetColor(255, 0, 0));
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
    pos = _collsionManage->CheckTerrain(pos, { forward.x, forward.y, 0 });
    //Y����
    pos = _collsionManage->CheckTerrain(pos, { forward.x, forward.y, forward.z });
    // Z�����݈̂ړ���ʒu����^���ɐ�������
    pos = _collsionManage->CheckTerrain(pos, { 0, forward.y, forward.z });

    pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, 0 });

    pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, forward.z });

    pos = _collsionManage->CheckJumpStand(pos, { 0, forward.y, forward.z });

    // �F��Ԃ����̂Ƃ��̂ݍ��̃��b�V���Ɣ�����s��
    if (_crState == ColourState::Black) {
        // X����
        pos = _collsionManage->CheckHitWall(pos, { forward.x, forward.y, 0 });
        // Y����
        pos = _collsionManage->CheckHitWall(pos, { forward.x, forward.y, forward.z });
        // Z����
        pos = _collsionManage->CheckHitWall(pos, { 0, forward.y, forward.z });

        pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, 0 });

        pos = _collsionManage->CheckJumpStand(pos, { forward.x, forward.y, forward.z });

        pos = _collsionManage->CheckJumpStand(pos, { 0, forward.y, forward.z });
    }
    // ���W�X�V
    _position = pos;
}
/** �F���菈�� */
void Player::ColorCollisionDetectionSystem() {

    auto animHandle = _modelAnimeManage->GetHandle();

    if (_crState == ColourState::Black) {
        _stateName = "Black";
        MV1SetMaterialSpcColor(animHandle, 0, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
        _crState = ColourState::White;
    }
    else if (_crState == ColourState::White) {
        _stateName = "White";
        MV1SetMaterialSpcColor(animHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
        _crState = ColourState::Black;
    }
}
