
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
            int _checkPoint{ -1 };
            //VECTOR _checkDrawPos{ -4510.0f, 5660.0f, -80.0f };
            VECTOR _checkDrawPos{ 8190.0f, 5880.0f, -80.0f };
            VECTOR _checkPos{ 0.0f, 0.0f, 0.0f };
            //std::unique_ptr<Model::ModelManager> _light;    //!< ライト用ユニークポインタ
        };
    }
}