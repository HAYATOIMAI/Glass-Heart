#pragma once
#include "ModeMain.h"

namespace GlassHeart {

    namespace Mode {

        class ModeLoading : public ModeMain {
        public:
            ModeLoading(GameMain& game);
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
            int _loadHandle{ -1 };
            int _cnt{ 0 };
        };
    }
}



