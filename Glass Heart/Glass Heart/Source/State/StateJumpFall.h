
/*********************************************************************
 * @file   StateBaseFall.h
 * @brief  
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
         * @brief �W�����v���~���
         */
        class StateJumpFall : public StateBase {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param owner �v���C���[�N���X�ւ̎Q��
             */
            StateJumpFall(Player::Player& owner);
            /**
             * @brief ���������
             *
             */
            void Enter() override;
            /**
            * @brief ���͏���
            *
            * @param input
            */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief �X�V����
             *
             */
            void Update() override;
            /**
             * @brief ���n����
             * 
             */
            void Landing();
        private:
            int _cnt{ 0 };
        };
    }  //  State 
} // GlassHeart