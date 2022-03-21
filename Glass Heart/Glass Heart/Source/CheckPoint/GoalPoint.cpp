
/*****************************************************************//**
 * @file   GoalPoint.cpp
 * @brief  �S�[���|�C���g�̏���
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "GoalPoint.h"
#include "../Application/GameMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"

namespace {
    constexpr auto GoalPositionX = 25830.0f;    //!< �S�[���̈ʒuX
    constexpr auto GoalPositionY = 12420.0f;     //!< �S�[���̈ʒuY
    constexpr auto GoalPositionZ = -30.0f;      //!< �S�[���̈ʒuZ
}


using namespace GlassHeart::CheckPoint;

GoalPoint::GoalPoint(GameMain& game) : ObjectBase{ game } {

    _goalPoint = LoadGraph("resource/Test/2dMaterial/light3.png");
    _position = VGet(GoalPositionX, GoalPositionY, GoalPositionZ);
    //_position = VGet(0.f, 0.f, 0.f);
    _radius = 100.0f;
    _hitFlag = false;
}

GoalPoint::~GoalPoint() {}

void GoalPoint::Process() {

    GetObjectServer().Register("GoalPoint", _position);

    // �`�F�b�N�|�C���g�ƃv���C���[�̓����蔻��
    for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ite++) {

        if ((*ite)->GetObjectType() == ObjectBase::ObjectType::Player) {

            if (_collsionManage->CheckCircleToCircle(*this, **ite) == true) {

                _hitFlag = true;
                GoToGameClear();
            }
            else {

                _hitFlag = false;
            }
        }
    }
}

void GoalPoint::Render() {

    auto cr = GetColor(0, 0, 255);

    DrawBillboard3D(_goalDrawPos, 0.5f, 0.5f, 120.0f, 0.0f, _goalPoint, TRUE);
#ifdef _DEBUG

    auto red = GetColor(255, 0, 0);
    auto green = GetColor(0, 255, 0);

    if (_hitFlag == true) {
        _collsionManage->RenderCircle(_position, _radius, red);
    }
    else {
        _collsionManage->RenderCircle(_position, _radius, green);
    }
#endif // _DEBUG
}

void GoalPoint::GoToGameClear() {

    if (_hitFlag == true) {

        _game.GetModeServer().GoToMode("GameClear");
    }
}