
/*****************************************************************//**
 * @file   StateIdle.h
 * @brief  アイドル状態クラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace AppFrame {
    class InputManager;
}

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
            StateIdle(Player::Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::InputManager& input) override;
            void Update() override;
        private:
            int _cnt{ 0 };
        };
    }
}


