
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
         * @brief ƒWƒƒƒ“ƒv‰º~ó‘Ô
         */
        class StateJumpFall : public StateBase {
        public:
            StateJumpFall(Player::Player& owner);
            void Enter() override;
            void Update() override;
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief ’…’nˆ—
             * 
             * @return 
             */
            bool JumpLand();
        private:

        };
    }

}



