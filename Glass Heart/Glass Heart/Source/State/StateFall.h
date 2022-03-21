
/*********************************************************************
 * @file   StateFall.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {

        class StateFall : public StateBase {
        public:
            StateFall(Player::Player& owner) : StateBase{ owner } {};
            void Enter() override;
            void Input(AppFrame::InputManager& input) override;
            void Update() override;

            void Landing();
        private:
            float _addVx{ 0.0f }; //!< ストレイフ用X軸移動量
            float _subVx{ 0.0f };
            float _reVx{ 0.0f };
            VECTOR  _jumpVelocity{ 0.0f, 0.0f, 0.0f }; //!< 
        };
    }// State 
}// GlassHeart