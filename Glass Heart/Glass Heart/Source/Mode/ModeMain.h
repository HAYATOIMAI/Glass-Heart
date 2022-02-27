
/*****************************************************************//**
 * @file   ModeMain.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>

namespace GlassHeart {

    class GameMain;

    namespace Object {
        class ObjectServer;
        class ObjectFactory;
    }

    namespace Mode {
        /**
         * @class ModeMain
         * @brief 
         */
        class ModeMain : public AppFrame::ModeBase{
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param game�@�Q�[�����C���N���X
             */
            ModeMain(GameMain& game);
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
            void Input(AppFrame::InputManager& input) override {};
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

            GameMain& GetGameMain() const { return _gameMain; }

            Object::ObjectFactory& GetObjectFactory();

            Object::ObjectServer& GetObjectServer();
        protected:
            GameMain& _gameMain;
            static int _count;         //!< �t���[���J�E���g
            static int _countSeconds;  //!< �b
            static int _countMinutes;  //!< ��
        };
    }
}