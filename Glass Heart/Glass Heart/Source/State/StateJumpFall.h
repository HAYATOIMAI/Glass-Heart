
/*********************************************************************
 * @file   StateBaseFall.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {
        /**
         * @class StateJumpFall 
         * @brief ジャンプ下降状態
         */
        class StateJumpFall : public StateBase {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param owner プレイヤークラスへの参照
             */
            StateJumpFall(Player::Player& owner);
            /**
             * @brief 入り口処理
             *
             */
            void Enter() override;
            /**
            * @brief 入力処理
            *
            * @param input
            */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief 更新処理
             *
             */
            void Update() override;
            /**
             * @brief 着地処理
             * 
             */
            void Landing();
        private:
            int _cnt{ 0 };
        };
    }  //  State 
} // GlassHeart