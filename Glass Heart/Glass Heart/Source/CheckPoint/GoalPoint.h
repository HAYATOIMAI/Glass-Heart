
/*********************************************************************
 * @file   GoalPoint.h
 * @brief  ゴールポイントクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"

namespace GlassHeart {

    namespace CheckPoint {

        class GoalPoint : public Object::ObjectBase {
        public:

            GoalPoint(GameMain& game);

            ~GoalPoint();

            void Process() override;

            void Render() override;

            void GoToGameClear();

            ObjectType GetObjectType() const override { return ObjectType::GoalPoint; };

        private:

            int _goalPoint;
            VECTOR _goalDrawPos{ -1500.0f, 70.0f, -300.0f };
            VECTOR _goalPos{ -1500.0f, 70.0f, -140.0f };
        };
    }
}