
/*****************************************************************//**
 * @file   StateJump.h
 * @brief  �v���C���[�̃W�����v��ԃN���X�̐錾
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <DxLib.h>

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
            bool  JumpEnd(const VECTOR& jumppos);
        private:
            double _gravity{ 9.8 };  //!< �d�͉����x
            double _jumpTimer{ 0.0 };
            double _groundY{ 0.0 };
            double _jumpPower{ 100.0 };
            double _jumpAngle{ 87.5 };
            bool _isJump{ false };
            VECTOR _jumpStartPosition;
            VECTOR _jumpVelocity;
            VECTOR _lastPosition;
        };
    }
}


