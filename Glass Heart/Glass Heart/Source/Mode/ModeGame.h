
/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  �Q�[�����N���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "ModeMain.h"
#include <AppFrame.h>
#include <memory>

namespace GlassHeart {

    class GameMain;
    namespace Camera {
        class CameraManager;
    }
    namespace Object {
        class ObjectFactory;
    }
    namespace UI {
        class UI;
    }
    namespace Mode {
        /**
         * @class ModeGame 
         * @brief �Q�[�����N���X�̐錾
         */
        class ModeGame : public ModeMain {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param[in] game �Q�[�����C���N���X�ւ̎Q��
             */
            ModeGame(GameMain& game);
            /**
             * @brief �f�X�g���N�^
             * 
             */
            ~ModeGame() = default;
            /**
             * @brief ����������
             * 
             */
            void Init() override;
            /**
             * @brief ���������
             * 
             */
            void Enter() override;
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
            /**
             * @brief �I������
             * 
             */
            void Exit() override;          
        };
    }
}

