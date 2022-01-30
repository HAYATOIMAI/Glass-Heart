
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
            void JumpLand();
        private:
            float _gravity{ 9.8f };  //!< 重力加速度
            float _jumpTimer{ 0.0f };
            float _jumpRise{ 0.0f }; //!< 上昇速度
            float _jumpPower{ 100.0f };
            float _jumpAngle{ 87.5f };
            float _jumpHeight{ 15.0f }; //!< ジャンプの高さ
            double _groundY{ 0.0 };
            bool _isJump{ false };
            VECTOR _jumpStartPosition;
            VECTOR _jumpVelocity; //!< 速度
            VECTOR _lastPosition;
        };
    }
}


