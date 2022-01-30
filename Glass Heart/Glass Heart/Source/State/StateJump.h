
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
            void JumpFunction(const bool isJumpStart);
            void JumpStart();
            VECTOR JumpProcess();
            void JumpLand();
        private:
            float _gravity{ 9.8f };  //!< �d�͉����x
            float _jumpTimer{ 0.0f };
            float _jumpRise{ 0.0f }; //!< �㏸���x
            float _jumpPower{ 100.0f };
            float _jumpAngle{ 87.5f };
            float _jumpHeight{ 15.0f }; //!< �W�����v�̍���
            double _groundY{ 0.0 };
            bool _isJump{ false };
            VECTOR _jumpStartPosition;
            VECTOR _jumpVelocity; //!< ���x
            VECTOR _lastPosition;
        };
    }
}


