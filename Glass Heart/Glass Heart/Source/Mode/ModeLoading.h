#pragma once
#include "ModeMain.h"

namespace GlassHeart {

    namespace Mode {

        class ModeLoading : public ModeMain {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param[in] game
             */
            ModeLoading(GameMain& game);
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
            int _loadHandle{ -1 };
            int _nowLoading{ -1 };
            int _cnt{ 0 };
        };
    }
}