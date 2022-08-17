/*****************************************************************//**
 * @file   ObjectServer.cpp
 * @brief  オブジェクトサーバーの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ObjectServer.h"
#include "ObjectBase.h"

 /** オブジェクトの追加 */
void GlassHeart::Object::ObjectServer::Add(std::unique_ptr<GlassHeart::Object::ObjectBase> obj) {
	if (_updating) {
		// 更新中は_pendingObjectsに追加する
		_pendingObjects.emplace_back(std::move(obj));
	}
	else {
		_objects.emplace_back(std::move(obj));
	}
}
/** 入力処理 */
void GlassHeart::Object::ObjectServer::Input(AppFrame::Input::InputManager& input) {
	_updating = true;
	for (auto&& obj : _objects) {
		if (obj->IsActive()) {
			// オブジェクトに入力する
			obj->Input(input);
		}
	}
	_updating = false;
}
/** 更新処理 */
void GlassHeart::Object::ObjectServer::Process() {
	for (auto&& obj : _objects) {
		if (obj->IsActive()) {
			// オブジェクトを更新する
			obj->Process();
		}
	}
	_updating = false;

	// 保留中のオブジェクトを_objectsに移動する
	_objects.insert(_objects.end(),
		make_move_iterator(_pendingObjects.begin()),
		make_move_iterator(_pendingObjects.end()));

	// 保留リストを削除
	_pendingObjects.clear();

	// 死亡したオブジェクトを削除
	erase_if(_objects, [](auto&& obj) { return obj->IsDead(); });
}
/** 描画処理 */
void GlassHeart::Object::ObjectServer::Render() {
	for (auto&& obj : _objects) {
		if (obj->IsActive()) {
			//! オブジェクトを描画する
			obj->Render();
		}
	}
}
/** 全オブジェクトを削除 */
void GlassHeart::Object::ObjectServer::AllClear() {
	_objects.clear();
	_pendingObjects.clear();
}
/** オブジェクトを登録 */
void GlassHeart::Object::ObjectServer::Register(std::string_view key, VECTOR vec) {
	if (_registry.contains(key.data())) {
		_registry[key.data()] = vec;
	}
	_registry.emplace(key, vec);
}
/** オブジェクトの位置を取得 */
VECTOR GlassHeart::Object::ObjectServer::GetPosition(std::string_view key) {
	if (_registry.contains(key.data())) {
		return _registry[key.data()];
	}
	// 未登録
	return { 0.f, 0.f, 0.f };
}
/** 前方ベクトルを取得 */
VECTOR GlassHeart::Object::ObjectServer::GetForward(std::string_view key) {
	if (_registry.contains(key.data())) {
		return _registry[key.data()];
	}
	// 未登録
	return { 0.f, 0.f, 0.f };
}