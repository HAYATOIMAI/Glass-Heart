/*********************************************************************
 * @file   ModelAnimeManager.cpp
 * @brief モデルアニメーションマネージャークラスの処理
 *
 * @author Hayato Imai,Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#include "ModelAnimeManager.h"
#include <DxLib.h>
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

/** コンストラクタ */
GlassHeart::Model::ModelAnimeManager::ModelAnimeManager(Object::ObjectBase& owner) : ModelManager{ owner }{}
/** デストラクタ */
GlassHeart::Model::ModelAnimeManager::~ModelAnimeManager() {
    MV1DetachAnim(_handle, _attachIndex);
}
/** 初期化処理 */
void GlassHeart::Model::ModelAnimeManager::Init() {}

void GlassHeart::Model::ModelAnimeManager::Register(std::string_view key, int animIndex) {
    if (_registry.contains(key.data())) {
        _registry.erase(key.data());
    }
    _registry.emplace(key, animIndex);
}

void GlassHeart::Model::ModelAnimeManager::Update(){
    //AnimeBlend();
    MV1SetAttachAnimTime(_handle, _attachIndex, _playTime);

    // ワールド行列更新
    ModelManager::Update();

    // 再生時間を進める
    _playTime += (1.f * _timeRate);
    _animrate += 0.3f;

    if (_playTime >= _totalTime) {
        if (_repeate) {
            // リピート再生あり
            _playTime = 0.0f;
            ++_repeatedCount;
        }
        else {
            // リピート再生なし
            _repeatedCount = 1;
            _playTime = _totalTime;
        }
    }
}

void GlassHeart::Model::ModelAnimeManager::Draw() {
    MV1DrawModel(_handle);
}

void GlassHeart::Model::ModelAnimeManager::ChangeAnime(std::string_view key, bool repeate) {
    auto newAnimIndex = _owner.GetGame().GetResourceServer().GetModelAnimIndex(_key, key);
    if (_animIndex == newAnimIndex) {
        return;
    }
    _animIndex = newAnimIndex;
    /*if (_oldattachIndex == _attachIndex) {

    }
    // 前のアタッチ番号を保持
    _oldattachIndex = _attachIndex;*/
    MV1DetachAnim(_handle, _attachIndex);
    // 新しいアニメーションをアタッチする
    _attachIndex = MV1AttachAnim(_handle, newAnimIndex, -1, FALSE);
    // アタッチしたアニメーションの総再生時間を取得する
    _totalTime = MV1GetAttachAnimTotalTime(_handle, _attachIndex);

    _playTime = 0.0f;
    _animrate = 1.0f;
    _repeatedCount = 0;
    _repeate = repeate;
}

void GlassHeart::Model::ModelAnimeManager::AnimeBlend() {
    if (_animrate >= 1.0f)  {
        MV1SetAttachAnimTime(_handle, _attachIndex, _playTime);
        _animrate = 1.0f;
        MV1DetachAnim(_handle, _oldattachIndex);
        _oldattachIndex = -1;
    }
    else {
        MV1SetAttachAnimBlendRate(_handle, _oldattachIndex, 1.0f - _animrate);
        MV1SetAttachAnimBlendRate(_handle, _attachIndex, _animrate);
    }
}
