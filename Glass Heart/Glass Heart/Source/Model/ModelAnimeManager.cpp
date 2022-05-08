/*********************************************************************
 * @file   ModelAnimeManager.cpp
 * @brief ���f���A�j���[�V�����}�l�[�W���[�N���X�̏���
 *
 * @author Hayato Imai,Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#include "ModelAnimeManager.h"
#include <DxLib.h>
#include "../Object/ObjectBase.h"
#include "../Application/GameMain.h"

/** �R���X�g���N�^ */
GlassHeart::Model::ModelAnimeManager::ModelAnimeManager(Object::ObjectBase& owner) : ModelManager{ owner }{}
/** �f�X�g���N�^ */
GlassHeart::Model::ModelAnimeManager::~ModelAnimeManager() {
    MV1DetachAnim(_handle, _attachIndex);
}
/** ���������� */
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

    // ���[���h�s��X�V
    ModelManager::Update();

    // �Đ����Ԃ�i�߂�
    _playTime += (1.f * _timeRate);
    _animrate += 0.3f;

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
    // �O�̃A�^�b�`�ԍ���ێ�
    _oldattachIndex = _attachIndex;*/
    MV1DetachAnim(_handle, _attachIndex);
    // �V�����A�j���[�V�������A�^�b�`����
    _attachIndex = MV1AttachAnim(_handle, newAnimIndex, -1, FALSE);
    // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
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
