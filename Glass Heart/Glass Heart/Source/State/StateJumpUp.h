
/*********************************************************************
 * @file   StateJumpUp.h
 * @brief  �㏸��Ԃ̐錾
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
            /**
             * @brief �W�����v������
             * 
             * @return �W�����v���̈ʒu
             */
            VECTOR JumpUpdate();
        private:
            float _jY{ -8.0f }; //!< �d�͉����x
                                //  
            VECTOR _jumpVelocity{ 0.0f, 0.0f, 0.0f }; //!< �W�����v���x
            bool _isfall{ false }; //!< ���������𔻒f����t���O

            float _vX{ 0.0f };  //!< ����̈ړ���

            float _addVx{ 0.0f }; //!< �E�����ւ̃X�g���C�t��
            float _subVx{ 0.0f }; //!< �������ւ̃X�g���C�t��
            VECTOR _position{ 0.0f, 0.0f, -140.0f }; //!< �ʒu
        };
    }
}



