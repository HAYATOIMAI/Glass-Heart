
/*****************************************************************//**
 * @file   StateManager.cpp
 * @brief  ステートマネージャークラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateManager.h"
#include <AppFrame.h>

using namespace GlassHeart;

State::StateManager::StateManager(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
    Register(key, state);
    PushBack(key);
}

void State::StateManager::Register(std::string_view key, std::shared_ptr<StateBaseRoot> state) {
    if (_registry.contains(key.data())) {
        _registry.erase(key.data());
    }
    _registry.emplace(key, state);
}

void State::StateManager::PushBack(std::string_view key) {
    if (!_registry.contains(key.data())) {
        return;   // キーが未登録
    }
    auto pushScene = _registry[key.data()];
    pushScene->Enter();
    _states.push_back(pushScene);
}

void State::StateManager::PopBack() {
    if (_states.empty()) {
        return;
    }
    _states.pop_back();
    if (_states.empty()) {
        return;
    }
    _states.back()->Enter();
}

void State::StateManager::GoToState(std::string_view key) {
    PopBack();
    PushBack(key.data());
}

void State::StateManager::Input(AppFrame::InputManager& input) {
    if (_states.empty()) {
        return;
    }
    _states.back()->Input(input);
}

void State::StateManager::Update() {
    if (_states.empty()) {
        return;
    }
    _states.back()->Update();
}

void State::StateManager::Draw() const {
    if (_states.empty()) {
        return;
    }
    _states.back()->Draw();
}