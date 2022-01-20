
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
#include <sstream>

using namespace GlassHeart::Player;

namespace {
    constexpr auto DegreeToRadian = std::numbers::pi_v<float> / 180.0f;
}

/** �R���X�g���N�^ */
Player::Player(GameMain& game) : GlassHeart::Object::ObjectBase{ game } {
    _rotation = VGet(0.0f, 270.0f * (std::numbers::pi_v<float> / 180.0f), 0.0f);
   // _state = State::White;
}
/** ���͏��� */
void Player::Input(AppFrame::InputManager& input) {
    _cameraManage->Input(input);
    _angularSpeed = 0;
    _stateManage->Input(input);

    if (input.GetJoyPad().GetXinputLeftShoulder() && _colourCount == 0) {
        ColorCollisionDetectionSystem();   
        _colourCount = 60;
    }
}
/** �X�V���� */
void Player::Process() {

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

   // ColorCollisionDetectionSystem();
}
/** �`�揈�� */
void Player::Render() {
#ifdef _DEBUG
    //�v���C���[�̍��W��\��
    auto x = 0; auto y = 0; auto size = 32;
    auto i = 0; auto o = 32 * 6;
    SetFontSize(size);
    DrawFormatString(x, y, GetColor(255, 0, 0), "�v���C���[X���W =  %.3f ", _position.x); y += size;
    DrawFormatString(x, y, GetColor(255, 0, 0), "�v���C���[Y���W =  %.3f ", _position.y); y += size;
    DrawFormatString(x, y, GetColor(255, 0, 0), "�v���C���[Z���W =  %.3f ", _position.z); y += size;
    DrawFormatString(i, o, GetColor(255, 0, 0), _stateName.c_str(), _state); y += size;
    _cameraManage->Render();
    DrawLine3D(VGet(_lastPosition.x, _lastPosition.y, _lastPosition.z), VGet(_position.x, _position.y / 200.0f, _position.z), GetColor(255, 0, 0));

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
    // Z�����݈̂ړ���ʒu����^���ɐ�������
    pos = _collsionManage->CheckTerrain(pos, { 0, forward.y, forward.z });
    // ���W�X�V
    _position = pos;
}
/** �F���菈�� */
void Player::ColorCollisionDetectionSystem(){

    auto animHandel = _modelAnimeManage->GetHandle();


    if (_state == State::White) {
        _stateName = "Black";
        MV1SetMaterialSpcColor(animHandel, 0, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
        _state = State::Black;
    }
    else if (_state == State::Black) {
        _stateName = "White";
        MV1SetMaterialSpcColor(animHandel, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
        _state = State::White;
    }
}
