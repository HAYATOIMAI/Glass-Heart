/*****************************************************************//**
 * @file   ModeClear.h
 * @brief  �Q�[���N���A�N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once

#include <AppFrame.h>
#include "ModeMain.h"
#include "../Object/ObjectBase.h"

namespace GlassHeart {

    class GameMain;

    namespace Mode {
        /**
         * @class ModeClear
         * @brief �Q�[���N���A�N���X�̐錾
         */
        class ModeClear : public ModeMain {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param game�@�Q�[���x�[�X�N���X
             */
            ModeClear(GameMain& game);
            /**
             * @brief �f�X�g���N�^
             *
             */
            ~ModeClear() = default;
            /**
             * @brief ����������
             *
             */
            void Init() override;
            /**
             * @brief ���������
             *
             */
            virtual void Enter() override;
            /**
             * @brief ���͏���
             *
             * @param input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief �X�V����
             *
             */
            void Process() override;
            /**
             * @brief �`�揈��
             *
             */
            void Render() override;
            /**
            * @brief �I������
            *
            */
            void Exit() override;

        private:
            int _gameClear{ -1 };   //!< �Q�[���N���A�摜
            int _gameOver{ -1 };    //!< �Q�[���I�[�o�[�摜
        };
    }
}


