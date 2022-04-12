/*****************************************************************//**
 * @file   StateManager.cpp
 * @brief  ステートマネージャークラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateManager.h"

using namespace GlassHeart;
/** コンストラクタ */
State::StateManager::StateManager(std::string_view key, std::shared_ptr<AppFrame::StateBaseRoot> state) {
    Register(key, state);
    PushBack(key);
}
/** ステートの登録 */
void State::StateManager::Register(std::string_view key, std::shared_ptr<AppFrame::StateBaseRoot> state) {
    if (_registry.contains(key.data())) {
        _registry.erase(key.data());
    }
    _registry.emplace(key, state);
}
/** ステートのプッシュバック */
void State::StateManager::PushBack(std::string_view key) {
    if (!_registry.contains(key.data())) {
        return;   // キーが未登録
    }
    // 文字列と一致するステートをレジストリから取得
    auto pushState = _registry[key.data()];
    // 一致するステートの入り口処理を実行
    pushState->Enter();
    _states.push_back(pushState);
}
/** ステートのポップバック */
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
/** ステートの遷移 */
void State::StateManager::GoToState(std::string_view key) {
    // ステートの真下に挿入する
    InsertBelowBack(key.data());
    // 最前面のステートを除外
    PopBack();
}
/** リストの一番後ろ(最前面)のステートの真下に挿入する */
void State::StateManager::InsertBelowBack(std::string_view key) {
    if (!_registry.contains(key.data())) {
        return;   // キーが未登録
    }
    auto insertState = _registry[key.data()];
    insertState->Enter();
    _states.insert(std::prev(_states.end()),insertState);
}
/** 入力処理 */
void State::StateManager::Input(AppFrame::InputManager& input) {
    if (_states.empty()) {
        return;
    }
    _states.back()->Input(input);
}
/** 更新処理 */
void State::StateManager::Update() {
    if (_states.empty()) {
        return;
    }
    _states.back()->Update();
}
/** 描画処理 */
void State::StateManager::Draw() const {
    if (_states.empty()) {
        return;
    }
    _states.back()->Draw();
}