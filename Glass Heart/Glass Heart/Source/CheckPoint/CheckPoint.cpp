/*****************************************************************//**
 * @file   CheckPoint.cpp
 * @brief  チェックポイントの処理
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "CheckPoint.h"
#include "../Application/GameMain.h"
#include "../Model/ModelManager.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"

namespace {
    constexpr auto CheckPositionX = 8220.0f;    //!< チェックポイントの位置X
    constexpr auto CheckPositionY = 5705.0f;    //!< チェックポイントの位置Y
    constexpr auto CheckPositionZ = 30.0f;       //!< チェックポイントの位置Z
}

using namespace GlassHeart::CheckPoint;

CheckPoint::CheckPoint(Application::GameMain& game) : ObjectBase{ game } {
    _checkPoint = LoadGraph("resource/2dMaterial/light3.png");
    _position = VGet(CheckPositionX, CheckPositionY, CheckPositionZ);
    _radius = 100.0f;
    _hitFlag = false;
    _checkPoints.clear();
    Register("1", _checkPos);
    Register("2", _position);
}

void CheckPoint::Process() {

    GetObjectServer().Register("CheckPoint", _position);

    // チェックポイントとプレイヤーの当たり判定
    for (auto ite = GetObjectServer().GetObjectLists().begin(); ite != GetObjectServer().GetObjectLists().end(); ite++) {

        if ((*ite)->GetObjectType() == ObjectBase::ObjectType::Player) {

            if (_collsionManage->CheckCircleToCircle(*this, **ite) == true) {
                _hitFlag = true;
            }
            else {
                _hitFlag = false;
            }
        }
    }
}

void CheckPoint::Render() {
    auto cr = GetColor(0, 0, 255);

    DrawBillboard3D(_checkDrawPos, 0.5f, 0.5f, 120.0f, 0.0f, _checkPoint, TRUE);
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

void GlassHeart::CheckPoint::CheckPoint::Register(std::string_view key, VECTOR vec) {
    if (_checkPoints.contains(key.data())) {
        _checkPoints.erase(key.data());
    }
    _checkPoints.emplace(key, vec);
}