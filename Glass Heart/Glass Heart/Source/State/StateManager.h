
/*****************************************************************//**
 * @file   StateManager.h
 * @brief  �X�e�[�g�}�l�[�W���[�N���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <AppFrame.h>

namespace AppFrame {
    class InputManager;
}

namespace GlassHeart {

    namespace Object {
        class ObjectBase;
    }

    namespace State {
        /**
         * @class StateBaseRoot
         * @brief ��Ԃ̊��N���X
         */
        class StateBaseRoot {
        public:
            StateBaseRoot() {};
            virtual void Enter() {};
            virtual void Input(AppFrame::InputManager& input) {};
            virtual void Update() {};
            virtual void Draw() {};
        };
        /**
         * @class StateManager
         * @brief �I�u�W�F�N�g�̏�Ԃ��Ǘ�����
         */
        class StateManager {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param[in] key   �ŏ��̃V�[���Ɋ֘A�t����C�ӂ̕�����
             * @param[in] state �ŏ��̃X�e�[�g��
             */
            StateManager(std::string_view key, std::shared_ptr<StateBaseRoot> state);
            /**
             * @brief ��Ԃ̓o�^
             * 
             * @param[in] key   �ŏ��̃V�[���Ɋ֘A�t����C�ӂ̕�����
             * @param[in] state �ŏ��� �X�e�[�g��
             */
            void Register(std::string_view key, std::shared_ptr<StateBaseRoot> state);
            /**
             * @brief ��Ԃ̃v�b�V���o�b�N
             *        ���X�g�̈�Ԍ��(�őO��)�ɃV�[�����v�b�V���ǉ�����
             *        state�̓�������Enter�����s����
             * 
             * @param[in] key �o�^�ς݂̃V�[���Ɋ֘A�t����������
             */
            void PushBack(std::string_view key);
            /**
             * @brief ��Ԃ̃|�b�v�o�b�N
             *        ���X�g�̈�Ԍ��(�őO��)�̃V�[�����|�b�v���O����
             *         state�̏o������Exit�����s����
             */
            void PopBack();
            /**
             * @brief ��Ԃ̑J��
             *         PopBack����PushBack����
             * 
             * @param[in] key �o�^�ς݂̃V�[���Ɋ֘A�t����������
             */
            void GoToState(std::string_view key);
            /**
             * @brief ���͏���
             *        ���X�g�̈�Ԍ��(�őO��)�̃V�[��������������
             * 
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            void Input(AppFrame::InputManager& input);
            /**
             * @brief �X�V����
             *        ���X�g�̈�Ԍ��(�őO��)�̃V�[��������������
             * 
             */
            void Update();
            /**
             * @brief �`�揈��
             *        ���X�g�̑S�V�[������������
             * 
             */
            void Draw() const;
        private:
            std::unordered_map<std::string, std::shared_ptr<StateBaseRoot>>	_registry;  //!< ��Ԃ̃��W�X�g��
            std::list<std::shared_ptr<StateBaseRoot>> _states;  //!< ��Ԃ̃��X�g
        };
    } // State
} // GlassHeart