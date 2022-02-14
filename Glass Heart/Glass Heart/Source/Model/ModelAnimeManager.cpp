
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
    // �Đ����Ԃ��Z�b�g����
    MV1SetAttachAnimTime(_handle, _attachIndex, _playTime);

    // ���[���h�s��X�V
    ModelManager::Update();

    // �Đ����Ԃ�i�߂�
    _playTime += (1.f * _timeRate);

    if (_playTime >= _totalTime) {
        if (_repeate) {
            // ���s�[�g�Đ�����
            _playTime = 0.0f;
            ++_repeatedCount;
        }
        else {
            // ���s�[�g�Đ��Ȃ�
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
    // �A�j���[�V�������f�^�b�`����
    MV1DetachAnim(_handle, _attachIndex);
    // �V�����A�j���[�V�������A�^�b�`����
    _attachIndex = MV1AttachAnim(_handle, newAnimIndex, -1, FALSE);
    // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
    _totalTime = MV1GetAttachAnimTotalTime(_handle, _attachIndex);

    _playTime = 0.0f;
    _repeatedCount = 0;
    _repeate = repeate;
}