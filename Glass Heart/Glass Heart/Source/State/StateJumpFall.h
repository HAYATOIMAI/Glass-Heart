
/*********************************************************************
 * @file   StateBaseFall.h
 * @brief  �W�����v���~��Ԃ̐錾
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace GlassHeart {

    namespace Player {
        class Player;
    }

    namespace State {
        /**
         * @class StateJumpFall 
         * @brief �W�����v���~��Ԃ̐錾
         */
        class StateJumpFall : public StateBase {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param[in] owner �v���C���[�N���X�ւ̎Q��
             */
            StateJumpFall(Player::Player& owner) : StateBase{ owner } {};
            /**
             * @brief ���������
             *
             */
            void Enter() override;
            /**
            * @brief ���͏���
            *
            * @param input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
            */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief �X�V����
             *
             */
            void Update() override;
        };
    }  //  State 
} // GlassHeart