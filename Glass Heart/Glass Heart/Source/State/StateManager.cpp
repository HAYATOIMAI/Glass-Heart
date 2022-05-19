/*****************************************************************//**
 * @file   StateManager.cpp
 * @brief  �X�e�[�g�}�l�[�W���[�N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateManager.h"

 /** �R���X�g���N�^ */
GlassHeart::State::StateManager::StateManager(std::string_view key, std::shared_ptr<AppFrame::State::StateBaseRoot> state) {
	Register(key, state);
	PushBack(key);
}
/** �X�e�[�g�̓o�^ */
void GlassHeart::State::StateManager::Register(std::string_view key, std::shared_ptr<AppFrame::State::StateBaseRoot> state) {
	if (_registry.contains(key.data())) {
		_registry.erase(key.data());
	}
	_registry.emplace(key, state);
}
/** �X�e�[�g�̃v�b�V���o�b�N */
void GlassHeart::State::StateManager::PushBack(std::string_view key) {
	if (!_registry.contains(key.data())) {
		return;   // �L�[�����o�^
	}
	// ������ƈ�v����X�e�[�g�����W�X�g������擾
	auto pushState = _registry[key.data()];
	// ��v����X�e�[�g�̓�������������s
	pushState->Enter();
	_states.push_back(pushState);
}
/** �X�e�[�g�̃|�b�v�o�b�N */
void GlassHeart::State::StateManager::PopBack() {
	if (_states.empty()) {
		return;
	}
	_states.pop_back();
	if (_states.empty()) {
		return;
	}
	_states.back()->Enter();
}
/** �X�e�[�g�̑J�� */
void GlassHeart::State::StateManager::GoToState(std::string_view key) {
	// �X�e�[�g�̐^���ɑ}������
	InsertBelowBack(key.data());
	// �őO�ʂ̃X�e�[�g�����O
	PopBack();
}
/** ���X�g�̈�Ԍ��(�őO��)�̃X�e�[�g�̐^���ɑ}������ */
void GlassHeart::State::StateManager::InsertBelowBack(std::string_view key) {
	if (!_registry.contains(key.data())) {
		return;   // �L�[�����o�^
	}
	auto insertState = _registry[key.data()];
	insertState->Enter();
	_states.insert(std::prev(_states.end()), insertState);
}
/** ���͏��� */
void GlassHeart::State::StateManager::Input(AppFrame::Input::InputManager& input) {
	if (_states.empty()) {
		return;
	}
	_states.back()->Input(input);
}
/** �X�V���� */
void GlassHeart::State::StateManager::Update() {
	if (_states.empty()) {
		return;
	}
	_states.back()->Update();
}
/** �`�揈�� */
void GlassHeart::State::StateManager::Draw() const {
	if (_states.empty()) {
		return;
	}
	_states.back()->Draw();
}