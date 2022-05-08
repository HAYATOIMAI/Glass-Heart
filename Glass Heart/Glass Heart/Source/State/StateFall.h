/*********************************************************************
 * @file   StateFall.h
 * @brief  プレイヤー落下状態の宣言
 *
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace GlassHeart {
    namespace Player {
        class Player;
    }
    namespace State {
        /**
         * @class StateFall
         * @brief プレイヤー落下状態の宣言
         */
        class StateFall : public StateBase {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param owner プレイヤークラスへの参照
             */
            StateFall(Player::Player& owner) : StateBase{ owner } {};
            /**
             * @brief 入り口処理
             *
             */
            void Enter() override;
            /**
             * @brief 入力処理
             *
             * @param[in] input インプットマネージャークラスの参照
             */
            void Input(AppFrame::Input::InputManager& input) override;
            /**
             * @brief更新処理
             *
             */
            void Update() override;
        };
    } // namespace State 
} // namespace GlassHeart