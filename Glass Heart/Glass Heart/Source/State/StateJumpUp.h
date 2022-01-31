
/*********************************************************************
 * @file   StateJumpUp.h
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
         * @class StateJumpUp
         * @brief ƒWƒƒƒ“ƒvã¸ˆ—
         */
        class StateJumpUp : public StateBase {
        public:
            StateJumpUp(Player::Player& owner);
            void Enter() override;
            void Input(AppFrame::InputManager& input) override;
            void Update() override;
        private:
            
        };
    }
}



