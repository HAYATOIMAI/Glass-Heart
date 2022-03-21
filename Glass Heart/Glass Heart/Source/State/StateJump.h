
/*****************************************************************//**
 * @file   StateJump.h
 * @brief  �v���C���[�̃W�����v��ԃN���X�̐錾
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
         * @class StateJump
         * @brief �W�����v���
         */
        class StateJump : public StateBase{
        public:
            StateJump(Player::Player& owner);
            void Enter() override;
            void Input(AppFrame::InputManager& input) override;
            void Update() override;
        private:
            bool _isJump{ false };
        };
    } //  State 
} // GlassHeart


