/*********************************************************************
 * @file   StateIdle.h
 * @brief  �A�C�h����ԃN���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateBase.h"

namespace GlassHeart {
    namespace Player {
        class Player;
    }
    namespace State {
        /**
         * @class StateIdle
         * @brief �A�C�h����ԃN���X�̐錾
         */
        class StateIdle : public StateBase {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param[in] owner �v���C���[�N���X�ւ̎Q��
             */
            StateIdle(Player::Player& owner) : StateBase{ owner } {};
            /**
             * @brief ���������
             * 
             */
            void Enter() override;
            /**
             * @brief�@���͏���
             * 
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief�@�X�V����
             * 
             */
            void Update() override;
        private:
            int _cnt{ 0 };             //!< ���L���X�g�p�J�E���^�[
            bool _resetFlag{ false };  //!< �F�����Z�b�g���邩�̃t���O
        };
    } // namespace State
} // namespace GlassHeart 


