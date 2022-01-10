
/*****************************************************************//**
 * @file   StateBase.h
 * @brief  ��Ԃ̊��N���X
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateManager.h"

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {

        class StateBase : public StateBaseRoot {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param[in] owner
             */
            StateBase(Player::Player& owner) : _owner{ owner } {};
            /**
             * @brief �`�揈��
             */
            void Draw() override;
        protected:
            Player::Player& _owner; //!< �v���C���[�N���X�̎Q��
        };
    }
}



