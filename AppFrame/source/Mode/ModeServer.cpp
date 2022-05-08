/*****************************************************************//**
 * @file   ModeServer.cpp
 * @brief  ���[�h�T�[�o�[�N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeServer.h"
#include "ModeBase.h"
#include "ModeFade.h"
#include "ModeFadeIn.h"
#include "ModeFadeOut.h"
#include "../Input/InputManager.h"
#include "../Application/GameBase.h"

namespace AppFrame {

	namespace Mode {
		/** �R���X�g���N�^ */
		ModeServer::ModeServer(std::string_view key, std::shared_ptr<ModeBase> mode) {
			Register("FadeIn", std::make_shared<Mode::ModeFadeIn>(mode->GetGame()));
			Register("FadeOut", std::make_shared<Mode::ModeFadeOut>(mode->GetGame()));
			Register(key, mode);
			PushBack(key);
			PushBack("FadeIn");
		}
		/** ���[�h�̓o�^ */
		void ModeServer::Register(std::string_view key, std::shared_ptr<ModeBase> mode) {
			if (_registry.contains(key.data())) {
				_registry.erase(key.data());
			}
			_registry.emplace(key, mode);
			mode->Init();
		}
		/** ���[�h�̃v�b�V���o�b�N */
		void ModeServer::PushBack(std::string_view key) {
			if (!_registry.contains(key.data())) {
				return;   // �L�[�����o�^
			}
			auto pushScene = _registry[key.data()];
			pushScene->Enter();
			_mode.push_back(pushScene);
		}
		/** ���[�h�̃|�b�v�o�b�N */
		void ModeServer::PopBack() {
			if (_mode.empty()) {
				return;
			}
			_mode.back()->Exit();
			_mode.pop_back();
		}
		/** ���[�h�̑J��
		 �����̃��[�h
		 ���t�F�[�h�C��
		 �����݂̃��[�h
		 ���t�F�[�h�A�E�g�F�őO�� */
		void ModeServer::GoToMode(std::string_view key) {
			InsertBelowBack(key.data());  // ���̃��[�h��}��
			InsertBelowBack("FadeIn");    // �t�F�[�h�C����}��
			PushBack("FadeOut");            // �t�F�[�h�A�E�g���v�b�V���o�b�N
		}
		/** ���X�g�̈�Ԍ��(�őO��)�̃��[�h�̐^���ɑ}�� */
		void ModeServer::InsertBelowBack(std::string_view key) {
			if (!_registry.contains(key.data())) {
				return;   // �L�[�����o�^
			}
			auto insertScene = _registry[key.data()];
			insertScene->Enter();
			_mode.insert(std::prev(_mode.end()), insertScene);
		}
		/** ���͏��� */
		void ModeServer::Input(Input::InputManager& input) {
			if (_mode.empty()) {
				return;
			}
			_mode.back()->Input(input);
		}
		/** �X�V���� */
		void ModeServer::Process() {
			if (_mode.empty()) {
				return;
			}
			_mode.back()->Process();
		}
		/** �`�揈�� */
		void ModeServer::Render() const {
			for (auto&& mode : _mode) {
				mode->Render();
			}
		}
	} // namespace Mode
} // namespace AppFrame