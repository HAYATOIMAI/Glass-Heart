
/*****************************************************************//**
 * @file   CheckPoint.cpp
 * @brief  チェックポイントの処理
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "CheckPoint.h"
#include "../Object/ObjectServer.h"
#include "../Player/Player.h"

using namespace GlassHeart::CheckPoint;

CheckPoint::CheckPoint(GameMain& game) : ObjectBase{ game } {

    _checkPoint = LoadGraph("resource/Test/2dMaterial/light3.png");
    _position = VGet(-150.0f, 35.0f, -140.0f);
    _radius = 100.0f;
    _hitFlag = false;
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

void GlassHeart::CheckPoint::CheckPoint::RenderCircle(const VECTOR checkDrawPos, float range) {
    for (float i = 0.0; i < 360.0; i++) {

        float radian = DX_PI_F / 180 * i;
        float x = range * std::cos(radian);
        float z = range * std::sin(radian);

        VECTOR move = { x, 0.0f, z };

        VECTOR newPos = VAdd(checkDrawPos, move);
        DrawPixel3D(newPos, GetColor(0, 255, 0));

    }
}

void CheckPoint::Render() {

    auto cr = GetColor(0, 0, 255);

    //DrawCircle(1920 / 2, 1080 / 2, 100, cr, FALSE);

    //DrawSphere3D(_checkPos, 100.0f, 32, cr, cr, FALSE);

    DrawBillboard3D(_checkDrawPos, 0.5f, 0.5f, 120.0f, 0.0f, _checkPoint, TRUE);
#ifdef _DEBUG

    if (_hitFlag == true) {

        _collsionManage->RenderCircle(_position, _radius, 255, 0, 0);

    }
    else {

        _collsionManage->RenderCircle(_position, _radius, 0, 255, 0);

    }

#endif // _DEBUG

}