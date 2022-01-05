
/*****************************************************************//**
 * @file   SoundManager.cpp
 * @brief  サウンドマネージャークラスの処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "SoundManager.h"
#include "../Resource/ResourceServer.h"
#include "../Application/GameBase.h"
#include <DxLib.h>

using namespace AppFrame;

SoundManager::~SoundManager()
{
}

void SoundManager::Play(std::string_view key) {
	Play(key, DX_PLAYTYPE_BACK);
}

void SoundManager::PlayLoop(std::string_view key) {
	Play(key, DX_PLAYTYPE_LOOP);
}

void SoundManager::SetVolume(std::string_view key, int volume) {
	auto res = _game.GetResourceServer();
	auto&& [filename, handle] = res.GetSoundInfo(key);

	if (handle != -1) {
		// 読み込み有り
		ChangeVolumeSoundMem(volume, handle);
	}
	else {
		// 読み込み無し
		SetVolumeMusic(volume);
	}
}

void SoundManager::Play(std::string_view key, int playType) {
	if (_isMute) {
		return;
	}

	auto res = _game.GetResourceServer();
	auto&& [filename, handle] = res.GetSoundInfo(key);

	if (handle != -1) {
		// 読み込み有り
		PlaySoundMem(handle, playType, TRUE);
	}
	else {
		// 読み込み無し
		PlayMusic(filename.c_str(), playType);
	}
}