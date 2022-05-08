/*****************************************************************//**
 * @file   ModeMain.h
 * @brief  ���[�h�̊��N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>

namespace GlassHeart {
    namespace Application {
        class GameMain;
    }
    namespace Object {
        class ObjectServer;
        class ObjectFactory;
    }
    namespace UI {
        class UI;
    } // namespace
    namespace Mode {
        /**
         * @class ModeMain
         * @brief ���[�h�̊��N���X�̐錾
         */
        class ModeMain : public AppFrame::Mode::ModeBase {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param game�@�Q�[�����C���N���X
             */
            ModeMain(Application::GameMain& game);
            /**
             * @brief �f�X�g���N�^
             *
             */
            ~ModeMain() = default;
            /**
             * @brief ����������
             *
             */
            void Init() override {};
            /**
             * @brief ���������
             *
             */
            void Enter() override {};
            /**
             * @brief ���͏���
             *
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
             */
            void Input(AppFrame::Input::InputManager& input) override {};
            /**
             * @brief �X�V����
             *
             */
            void Process()override {};
            /**
             * @brief�@�`�揈��
             *
             */
            void Render() override {};
            /**
             * @brief �I������
             */
            void Exit() override {};

            inline Application::GameMain& GetGameMain() const { return _gameMain; }

            Object::ObjectFactory& GetObjectFactory();

            Object::ObjectServer& GetObjectServer();

            UI::UI& GetUI();
        protected:
            Application::GameMain& _gameMain; //!< �Q�[�����C���N���X�ւ̎Q��
            static int _count;                      //!< �^�C�}�[�p�t���[���J�E���g
            static int _countSeconds;            //!< �^�C�}�[�p�t���[���J�E���g
            int _fadeCount;                          //!< �����t�F�[�h�C���A�E�g�p�J�E���^
        };
    } // namespace Mode
} // namespace GlassHeart