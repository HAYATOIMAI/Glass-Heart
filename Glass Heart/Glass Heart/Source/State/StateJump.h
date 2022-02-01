
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
            VECTOR JumpProcess();
            bool JumpLand(const VECTOR& pos);
        private:
            float _gravity{ 0.f };  //!< 重力加速度
            float _jumpTimer{ 0.0f };
            float _jumpPower{ 100.0f };
            bool _isJump{ false };
            VECTOR _jumpStartPosition;
            VECTOR _jumpVelocity; //!< 速度
            VECTOR _lastPosition;
        };
    }
}


