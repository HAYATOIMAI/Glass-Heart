
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
    constexpr auto CheckPositionX = 8220.0f;    //!< ゴールの位置X
    constexpr auto CheckPositionY = 5705.0f;     //!< ゴールの位置Y
    constexpr auto CheckPositionZ = -30.0f;      //!< ゴールの位置Z
}

using namespace GlassHeart::CheckPoint;

CheckPoint::CheckPoint(GameMain& game) : ObjectBase{ game } {
    //_light = std::make_unique<Model::ModelManager>(*this);
   //_light->handle("Light");
   //_light->SetPosition(VGet(100.0f, 100.0f, 0.0f));
   //_light->SetScale({ 1.f, 1.f, 1.f });

    _checkPoint = LoadGraph("resource/Test/2dMaterial/light3.png");
    _position = VGet(CheckPositionX, CheckPositionY, CheckPositionZ);
    _radius = 100.0f;
    _hitFlag = false;
    //MV1SetPosition(_checkPoint, VGet(0.0f, 0.0f, -0.0f));
}

CheckPoint::~CheckPoint() {}

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

    //_light->Draw();
  //MV1DrawModel(_checkPoint);
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