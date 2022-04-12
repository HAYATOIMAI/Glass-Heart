/*********************************************************************
 * @file   StateJumpUp.h
 * @brief   �W�����v�㏸��Ԃ̐錾
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
         * @class StateJumpUp
         * @brief �W�����v�㏸����
         */
        class StateJumpUp : public StateBase {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param owner �v���C���[�N���X�ւ̎Q��
             */
            StateJumpUp(Player::Player& owner);
            /**
             * @brief ���������
             * 
             */
            void Enter() override;
            /**
             * @brief
             * 
             * @param input
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief �X�V����
             * 
             */
            void Update() override;
        };
    } // namespace State 
} // namespace GlassHeart