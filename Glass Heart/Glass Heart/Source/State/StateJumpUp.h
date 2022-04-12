/*********************************************************************
 * @file   StateJumpUp.h
 * @brief   ジャンプ上昇状態の宣言
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <DxLib.h>

namespace GlassHeart {
    namespace Player {
        class Player;
    }
    namespace State {
        /**
         * @class StateJumpUp
         * @brief ジャンプ上昇処理
         */
        class StateJumpUp : public StateBase {
        public:
            /**
             * @brief コンストラクタ
             * 
             * @param owner プレイヤークラスへの参照
             */
            StateJumpUp(Player::Player& owner);
            /**
             * @brief 入り口処理
             * 
             */
            void Enter() override;
            /**
             * @brief
             * 
             * @param input
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief 更新処理
             * 
             */
            void Update() override;
        };
    } // namespace State 
} // namespace GlassHeart