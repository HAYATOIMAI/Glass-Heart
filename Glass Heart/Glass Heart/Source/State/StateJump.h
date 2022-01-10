
/*****************************************************************//**
 * @file   StateJump.h
 * @brief  ジャンプ状態クラスの宣言
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
            void  JumpEnd(const VECTOR& jumppos);
        private:
            float _gravity{ 0.0f };  //!< 重力加速度
            double _jumpTimer{ 0.0 };
            double _groundY{ 0.0 };
            double _jumpPower{0.0};
            double _jumpAngle{ 0.0 };
            bool _isJump{ false };
            VECTOR _jumpStartPosition;
            VECTOR _jumpVelocity;
        };
    }
}


