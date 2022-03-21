
/*********************************************************************
 * @file   StateBaseFall.h
 * @brief  ジャンプ下降状態の宣言
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
         * @brief ジャンプ下降状態の宣言
         */
        class StateJumpFall : public StateBase {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param[in] owner プレイヤークラスへの参照
             */
            StateJumpFall(Player::Player& owner) : StateBase{ owner } {};
            /**
             * @brief 入り口処理
             *
             */
            void Enter() override;
            /**
            * @brief 入力処理
            *
            * @param input インプットマネージャークラスの参照
            */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief 更新処理
             *
             */
            void Update() override;
        };
    }  //  State 
} // GlassHeart