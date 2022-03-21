
/*********************************************************************
 * @file   StateDead.cpp
 * @brief  �v���C���[���S��Ԃ̏���
 * 
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#include "StateDead.h"
#include "../Player/Player.h"
#include "../State/StateManager.h"
#include "../Collision/CollisionManager.h"
#include "../Object/ObjectServer.h"
#include <numbers>

using namespace GlassHeart;

namespace {
    constexpr auto StartPositionX = -150.0f;  //!< �v���C���[�̏����ʒuX
    constexpr auto StartPositionY = 35.0f;    //!< �v���C���[�̏����ʒuY
    constexpr auto StartPositionZ = -55.0f;  //!< �v���C���[�̏����ʒuZ
}

State::StateDead::StateDead(Player::Player& owner) : StateBase{owner} {
    _position = VGet(0.0f, 0.0f, 0.0f);
}

void State::StateDead::Enter() {
    //_position = VGet(-150.0f, 35.0f, -55.0f);
}

void State::StateDead::Update() {
    ResetPos();
}

void State::StateDead::ResetPos() {
    // �f�X���b�V���Ɠ������Ă�����
    if (_owner.GetCollision().GetWDeathMesh().HitNum >= 1) {
        // 
        if (_owner.GetCheckPointFlag() == true) {
            // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
            auto checkPos = _owner.GetObjectServer().GetPosition("CheckPoint");
            // �v���C���[�̍��W���`�F�b�N�|�C���g�ɂ���
            _owner.SetPosition(checkPos);
        }
        else {
            _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
            _owner.SetPosition(_position);
            _position = VGet(0.0f, 0.0f, 0.0f);
        }
    }
    if (_owner.GetCollision().GetBDeathMesh().HitNum >= 1) {
        // 
        if (_owner.GetCheckPointFlag() == true) {
            // �I�u�W�F�N�g�T�[�o�[����`�F�b�N�|�C���g�̍��W���擾
            auto checkPos = _owner.GetObjectServer().GetPosition("CheckPoint");
            // �v���C���[�̍��W���`�F�b�N�|�C���g�ɂ���
           _owner.SetPosition(checkPos);
        }
        else {
            _position = VGet(StartPositionX, StartPositionY, StartPositionZ);
            _owner.SetPosition(_position);
            _position = VGet(0.0f, 0.0f, 0.0f);
        }
    }
    _owner.GetStateManage().PopBack();
}
