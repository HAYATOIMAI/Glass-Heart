
/*********************************************************************
* @file   GoalPoint.h
* @brief  ゴールポイントクラスの宣言
*
* @author Yoshihiro Takahashi
* @date   February 2022
*********************************************************************/
#pragma once

#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"

namespace GlassHeart {

    namespace CheckPoint {
        /**
        * @class GoalPoint
        * @brief ゴールポイント
        */
        class GoalPoint : public Object::ObjectBase {
        public:
            /**
            * @brief コンストラクタ
            *
            * @param game ゲームメインクラスへの参照
            */
            GoalPoint(GameMain& game);
            /**
            * @brief デストラクタ
            *
            */
            virtual ~GoalPoint() override = default;
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
            /**
            * @brief ゲームクリアへ遷移処理
            *
            */
            void GoToGameClear();
            /**
            * @brief タイプの取得
            * @return タイプID
            */
            ObjectType GetObjectType() const override { return ObjectType::GoalPoint; };

        private:

            int _goalPoint{ -1 };
            VECTOR _goalDrawPos{ 25800.0f, 12580.0f, 80.0f };
            VECTOR _goalPos{ -1500.0f, 70.0f, -140.0f };
        };
    }
}
