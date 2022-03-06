
/*****************************************************************//**
 * @file   GoalPoint.cpp
 * @brief  ゴールポイントの処理
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "GoalPoint.h"
#include "../Application/GameMain.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"

using namespace GlassHeart::CheckPoint;

GoalPoint::GoalPoint(GameMain& game) : ObjectBase{ game } {

    _goalPoint = LoadGraph("resource/Test/2dMaterial/light3.png");
    _position = VGet(-8191.494f, 705.000f, -55.0f);
    _radius = 100.0f;
    _hitFlag = false;
}

GoalPoint::~GoalPoint() {}

void GoalPoint::Process() {

    GetObjectServer().Register("CheckPoint", _position);

    // チェックポイントとプレイヤーの当たり判定
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