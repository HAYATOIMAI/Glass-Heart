/*****************************************************************//**
 * @file   StateManager.h
 * @brief �X�e�[�g�}�l�[�W���[�N���X�̐錾
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
	namespace Input {
		class InputManager;
	}
}
/**
 * @namespace GlassHeart
 * @brief �v���W�F�N�g��
 */
namespace GlassHeart {
	namespace Object {
		class ObjectBase;
	}
	/**
	 * @namespace State
	 * @brief  �v���C���[�̃X�e�[�g�֌W
	 */
	namespace State {
		/**
		 * @class StateManager
		 * @brief �I�u�W�F�N�g�̃X�e�[�g���Ǘ�����
		 */
		class StateManager {
		public:
			/**
			 * @brief �R���X�g���N�^
			 *
			 * @param[in] key    �ŏ��̃X�e�[�g�Ɋ֘A�t����C�ӂ̕�����
			 * @param[in] state �ŏ��̃X�e�[�g
			 */
			StateManager(std::string_view key, std::shared_ptr<AppFrame::State::StateBaseRoot> state);
			/**
			 * @brief �X�e�[�g�̓o�^
			 *
			 * @param[in] key    �ŏ��̃X�e�[�g�Ɋ֘A�t����C�ӂ̕�����
			 * @param[in] state �ŏ��̃X�e�[�g
			 */
			void Register(std::string_view key, std::shared_ptr<AppFrame::State::StateBaseRoot> state);
			/**
			 * @brief �X�e�[�g�̃v�b�V���o�b�N
			 *           ���X�g�̈�Ԍ��(�őO��)�ɃX�e�[�g���v�b�V���ǉ�����
			 *           state�̓�������Enter�����s����
			 *
			 * @param[in] key �o�^�ς݂̃V�[���Ɋ֘A�t����������
			 */
			void PushBack(std::string_view key);
			/**
			 * @brief �X�e�[�g�̃|�b�v�o�b�N
			 *           ���X�g�̈�Ԍ��(�őO��)�̃X�e�[�g���|�b�v���O����
			 *           state�̏o������Exit�����s����
			 */
			void PopBack();
			/**
			 * @brief �X�e�[�g�̑J��
			 *
			 * @param[in] key �o�^�ς݂̃X�e�[�g�Ɋ֘A�t����������
			 */
			void GoToState(std::string_view key);
			/**
			 * @brief ���X�g�̈�Ԍ��(�őO��)�̃X�e�[�g�̐^���ɑ}������
			 *           state�̓�������Enter�����s����
			 *
			 * @param[in] key �o�^�ς݂̃X�e�[�g�Ɋ֘A�t����������
			 */
			void InsertBelowBack(std::string_view key);
			/**
			 * @brief ���͏���
			 *           ���X�g�̈�Ԍ��(�őO��)�̃X�e�[�g������������
			 *
			 * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
			 */
			void Input(AppFrame::Input::InputManager& input);
			/**
			 * @brief �X�V����
			 *           ���X�g�̈�Ԍ��(�őO��)�̃X�e�[�g������������
			 */
			void Update();
			/**
			 * @brief �`�揈��
			 *           ���X�g�̑S�X�e�[�g����������
			 */
			void Draw() const;
		private:
			//!< ��Ԃ̃��W�X�g��
			std::unordered_map<std::string, std::shared_ptr<AppFrame::State::StateBaseRoot>>	_registry;
			//!< ��Ԃ̃��X�g
			std::list<std::shared_ptr<AppFrame::State::StateBaseRoot>> _states;
		};
	} // namespace State
} // namespace GlassHeart