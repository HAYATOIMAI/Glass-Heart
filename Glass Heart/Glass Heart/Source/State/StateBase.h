
/*****************************************************************//**
 * @file   StateBase.h
 * @brief  状態の基底クラス
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateManager.h"

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {

        class StateBase : public StateBaseRoot {
        public:
            /**
             * @brief コンストラクタ
             * 
             * @param[in] owner
             */
            StateBase(Player::Player& owner) : _owner{ owner } {};
            /**
             * @brief 描画処理
             */
            void Draw() override;
        protected:
            Player::Player& _owner; //!< プレイヤークラスの参照
        };
    }
}



