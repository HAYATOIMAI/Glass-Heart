
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
            /**
             * @brief コンストラクタ
             * 
             * @param[in] game ゲームメインクラスへの参照
             */
            CheckPoint(GameMain& game);
            /**
             * @brief　デストラクタ
             * 
             */
            virtual ~CheckPoint()override = default;
            /**
             * @brief 更新処理
             * 
             */
            void Process() override;
            /**
             * @brief 描画処理
             * 
             */
            void Render() override;

            ObjectType GetObjectType() const override { return ObjectType::CheckPoint; };

        private:
            int _checkPoint{ -1 };
            VECTOR _checkDrawPos{ 8190.0f, 5880.0f, 30.0f };
            VECTOR _checkPos{ 0.0f, 0.0f, 0.0f };
        };
    }
}