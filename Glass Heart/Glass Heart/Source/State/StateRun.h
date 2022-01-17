
/*****************************************************************//**
 * @file   StateRun.h
 * @brief  走り状態クラスの宣言
 * 
 * @author Hayato Imai
 * @date   January 2022
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
        * @class StateRun
        * @brief プレイヤーの走り状態クラス
        */
        class StateRun : public StateBase{
        public:
            StateRun(Player::Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::InputManager& input) override;
            void Update() override;
        };
    }
}



