
/*********************************************************************
 * @file   CheckPoint.h
 * @brief  チェックポイントクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"

namespace GlassHeart {

    namespace Model {
        class ModelManager;
    }

    class GameMain;

    namespace CheckPoint {

        class CheckPoint : public Object::ObjectBase {
        public:

            CheckPoint(GameMain& game);

            ~CheckPoint();

            void Process() override;

            void Render() override;

            ObjectType GetObjectType() const override { return ObjectType::CheckPoint; };

        private:

            int _checkPoint;
            VECTOR _checkDrawPos{ -1500.0f, 70.0f, -300.0f };
            VECTOR _checkPos{ -1500.0f, 70.0f, -140.0f };
        };
    }
}