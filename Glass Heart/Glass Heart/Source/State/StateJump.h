
/*****************************************************************//**
 * @file   StateJump.h
 * @brief  プレイヤーのジャンプ状態クラスの宣言
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
         * @brief ジャンプ状態
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
            float _gravity{ 9.8f };  //!< 重力加速度
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


