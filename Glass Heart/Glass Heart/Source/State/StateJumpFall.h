
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
            /**
             * @brief 落下死処理
             * 
             */
            void IsDeath();
        private:
            float _addVx{ 0.0f }; //!< ストレイフ用X軸移動量
            float _subVx{ 0.0f };
            float _reVx{ 0.0f };
        };
    }
}