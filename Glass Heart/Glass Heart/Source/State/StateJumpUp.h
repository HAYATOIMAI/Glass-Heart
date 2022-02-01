
/*********************************************************************
 * @file   StateJumpUp.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <AppFrame.h>

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {
        /**
         * @class StateJumpUp
         * @brief ÉWÉÉÉìÉvè„è∏èàóù
         */
        class StateJumpUp : public StateBase {
        public:
            StateJumpUp(Player::Player& owner);
            void Enter() override;
            void Input(AppFrame::InputManager& input) override;
            void Update() override;
            VECTOR JumpUpdate();
        private:
            float _vX{ 0.0f };
            float _vY{ 0.0f };
            float _gravity{ 0.0f };
            VECTOR _jumpVelocity{ 0.0f, 0.0f, 0.0f };
            bool _isfall{ false };
        };
    }
}



