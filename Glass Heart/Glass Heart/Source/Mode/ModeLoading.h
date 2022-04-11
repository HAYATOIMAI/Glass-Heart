/*****************************************************************//**
 * @file   ModeLoading.h
 * @brief  ���[�f�B���O��ʃN���X�̐錾
 *
 * @author Hayato Imai
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ModeMain.h"

namespace GlassHeart {
    namespace Application {
        class GameMain;
    }
    namespace Mode {
        /**
         * @class ModeLoading
         * @brief ���[�f�B���O��ʃN���X�̐錾
         */
        class ModeLoading : public ModeMain {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param[in] game
             */
            ModeLoading(Application::GameMain& game);
            /**
             * @brief �f�X�g���N�^
             *
             */
            ~ModeLoading() = default;
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
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
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
            int _loadHandle{ -1 };  //!< ���[�f�B���OGIF�摜�p�n���h��
            int _nowLoading{ -1 };  //!< NowLoadig�摜�p�n���h��
            int _cnt{ 0 };          //!< ���[�f�B���O����
        };
    } // Mode
} // GlassHeart