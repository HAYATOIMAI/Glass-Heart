
/*****************************************************************//**
 * @file   ModelAnimeManager.cpp
 * @brief
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModelAnimeManager.h"
#include <DxLib.h>
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Model;

ModelAnimeManager::ModelAnimeManager(Object::ObjectBase& owner) : ModelManager{ owner }
{
}

ModelAnimeManager::~ModelAnimeManager()
{
    MV1DetachAnim(_handle, _attachIndex);
}

void ModelAnimeManager::Init()
{
}

void ModelAnimeManager::Register(std::string_view key, int animIndex)
{
    if (_registry.contains(key.data())) {
        _registry.erase(key.data());
    }
    _registry.emplace(key, animIndex);
}

void ModelAnimeManager::Update()
{
    // 再生時間をセットする
    MV1SetAttachAnimTime(_handle, _attachIndex, _playTime);

    // ワールド行列更新
    ModelManager::Update();

    // 再生時間を進める
    _playTime += (1.f * _timeRate);

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

void ModelAnimeManager::Draw()
{
    MV1DrawModel(_handle);
}

void ModelAnimeManager::ChangeAnime(std::string_view key, bool repeate)
{
    auto newAnimIndex = _owner.GetGame().GetResourceServer().GetModelAnimIndex(_key, key);
    if (_animIndex == newAnimIndex) {
        return;
    }
    _animIndex = newAnimIndex;
    // アニメーションをデタッチする
    MV1DetachAnim(_handle, _attachIndex);
    // 新しいアニメーションをアタッチする
    _attachIndex = MV1AttachAnim(_handle, newAnimIndex, -1, FALSE);
    // アタッチしたアニメーションの総再生時間を取得する
    _totalTime = MV1GetAttachAnimTotalTime(_handle, _attachIndex);

    _playTime = 0.0f;
    _repeatedCount = 0;
    _repeate = repeate;
}