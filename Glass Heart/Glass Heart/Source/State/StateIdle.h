/*********************************************************************
 * @file   StateIdle.h
 * @brief  アイドル状態クラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace GlassHeart {
    namespace Player {
        class Player;
    }
    namespace State {
        /**
         * @class StateIdle
         * @brief アイドル状態クラスの宣言
         */
        class StateIdle : public StateBase {
        public:
            /**
             * @brief コンストラクタ
             * 
             * @param[in] owner プレイヤークラスへの参照
             */
            StateIdle(Player::Player& owner) : StateBase{ owner } {};
            /**
             * @brief 入り口処理
             * 
             */
            void Enter() override;
            /**
             * @brief　入力処理
             * 
             * @param[in] input インプットマネージャークラスの参照
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief　更新処理
             * 
             */
            void Update() override;
        private:
            int _cnt{ 0 };             //!< リキャスト用カウンター
            bool _resetFlag{ false };  //!< 色をリセットするかのフラグ
        };
    } // namespace State
} // namespace GlassHeart 


