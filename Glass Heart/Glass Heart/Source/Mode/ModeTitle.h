
/*****************************************************************//**
 * @file   ModeTitle.h
 * @brief  �^�C�g����ʃN���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include <AppFrame.h>

namespace GlassHeart {

    class GameMain;

    namespace Mode {
        /**
         * @class 
         * @brief 
         */
        class ModeTitle :  public AppFrame::ModeBase {
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
            int _gameTitleHandle{ -1 };  //!< �Q�[���^�C�g���摜
            int _leftClickToStart{ -1 };  //!< Left click to Start�摜
            int _titleBgHandle{ -1 };  //!< �w�i�摜
            int _alpha{ 0 };  //!< �A���t�@�l
        };
    }

}
