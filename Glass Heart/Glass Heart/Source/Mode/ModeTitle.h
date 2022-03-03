
/*****************************************************************//**
 * @file   ModeTitle.h
 * @brief  �^�C�g����ʃN���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeMain.h"
#include <AppFrame.h>

namespace GlassHeart {
   
    class GameMain;

    namespace Mode {
        /**
         * @class 
         * @brief 
         */
        class ModeTitle :  public ModeMain {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param game�@�Q�[���x�[�X�N���X
             */
            ModeTitle(GameMain& game);
            /**
             * @brief �f�X�g���N�^
             *
             */
            ~ModeTitle() = default;
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
        private:
            int _title{ -1 };               //!< �^�C�g���摜
            int _titleBgHandle{ -1 };       //!< �Q�[���^�C�g���摜
            int _titleButtonHandle{ -1 };   //!< Press Any Button�摜
            int _titleLogo{ -1 };           //!< �w�i�摜
        };
    }
}
