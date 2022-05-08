/*********************************************************************
 * @file   StateFall.h
 * @brief  �v���C���[������Ԃ̐錾
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
        /**
         * @class StateFall
         * @brief �v���C���[������Ԃ̐錾
         */
        class StateFall : public StateBase {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param owner �v���C���[�N���X�ւ̎Q��
             */
            StateFall(Player::Player& owner) : StateBase{ owner } {};
            /**
             * @brief ���������
             *
             */
            void Enter() override;
            /**
             * @brief ���͏���
             *
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            void Input(AppFrame::Input::InputManager& input) override;
            /**
             * @brief�X�V����
             *
             */
            void Update() override;
        };
    } // namespace State 
} // namespace GlassHeart