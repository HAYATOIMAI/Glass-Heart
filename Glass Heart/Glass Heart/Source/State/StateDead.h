
/*********************************************************************
 * @file   StateDead.h
 * @brief  ƒvƒŒƒCƒ„[€–Só‘Ô‚ÌéŒ¾
 * 
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <AppFrame.h>

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {

        class StateDead : public StateBase { 
        public:
            StateDead(Player::Player& owner);
            void Enter() override;
            void Update()override;
            void ResetPos();
        private:
            VECTOR _position;
        };
    }// State 
} // GlassHeart



