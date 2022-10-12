/*****************************************************************//**
 * @file   ModeServer.h
 * @brief  ���[�h�T�[�o�[�N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <unordered_map>
#include <string_view>
#include <list>
 /**
	* @namespace AppFrame
	* @brief  �A�v���P�[�V�����t���[��
	*/
namespace AppFrame {
	class GameBase;
	namespace Input {
		class InputManager;
	}
	/**
	 * @namespace Mode
	 * @brief ���[�h�֌W
	 */
	namespace Mode {
		class ModeBase;
		/**
		 * @class ModeServer
		 * @brief ���[�h�T�[�o�[�N���X�̐錾
		 *          ���[�h�N���X���Ǘ�����
		 */
		class ModeServer {
		public:
			/**
			 * @brief      �R���X�g���N�^
			 *
			 * @param[in] key   �ŏ��̃��[�h�Ɋ֘A�t����C�ӂ̕�����
			 * @param[in] mode  �ŏ��̃��[�h��
			 */
			ModeServer(std::string_view key, std::shared_ptr<ModeBase> mode);
			/**
			 * @brief      ���[�h�̓o�^
			 *
			 * @param[in] key  ���[�h�Ɋ֘A�t����C�ӂ̕�����
			 * @param[in] mode ���[�h�̃C���X�^���X
			 */
			void Register(std::string_view key, std::shared_ptr<ModeBase> mode);
			/**
			 * @brief   ���[�h�̃v�b�V���o�b�N
			 *          ���X�g�̈�Ԍ��(�őO��)�Ƀ��[�h���v�b�V���ǉ�����
			 *          ModeBase�̓�������Enter�����s����
			 *
			 * @param[in] key  �o�^�ς݂̃��[�h�Ɋ֘A�t����������
			 */
			void PushBack(std::string_view key);
			/**
			 * @brief ���[�h�̃|�b�v�o�b�N
			 *        ���X�g�̈�Ԍ��(�őO��)�̃��[�h���|�b�v���O����
			 *        ModeBase�̏o������Exit�����s����
			 */
			void PopBack();
			/**
			 * @brief   ���[�h�̑J��
			 *          key�Ŏw�肳�ꂽ���[�h�ֈڍs����
			 *
			 * @param[in] key  �o�^�ς݂̃��[�h�Ɋ֘A�t����������
			 */
			void GoToMode(std::string_view key);
			/**
			 * @brief   ���X�g�̈�Ԍ��(�őO��)�̃��[�h�̐^���ɑ}������
			 *          ModeBase�̓�������Enter�����s����
			 *
			 * @param[in] key  �o�^�ς݂̃��[�h�Ɋ֘A�t����������
			 */
			void InsertBelowBack(std::string_view key);
			/**
			 * @brief       ���͏���
			 *
			 * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
			 */
			void Input(Input::InputManager& input);
			/**
			 * @brief  �X�V����
			 */
			void Process();
			/**
			 * @brief �`�揈��
			 */
			void Render() const;
		private:
			//!< ���[�h�̃��W�X�g��
			std::unordered_map<std::string, std::shared_ptr<ModeBase>> _registry;
			//!< ���[�h�̃��X�g
			std::list<std::shared_ptr<ModeBase>> _mode;
		};
	} // namespace Mode
} // namespace AppFrame