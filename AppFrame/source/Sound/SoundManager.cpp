
/*****************************************************************//**
 * @file   SoundManager.cpp
 * @brief  �T�E���h�}�l�[�W���[�N���X�̏���
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "SoundManager.h"
#include "../Resource/ResourceServer.h"
#include "../Application/GameBase.h"
#include <DxLib.h>

namespace AppFrame {

    namespace Sound {
        /** �R���X�g���N�^ */
        SoundManager::~SoundManager() {}
        /** �Đ�(���[�v����) */
        void SoundManager::Play(std::string_view key) {
            Play(key, DX_PLAYTYPE_BACK);
        }
        /** ���[�v�Đ� */
        void SoundManager::PlayLoop(std::string_view key) {
            Play(key, DX_PLAYTYPE_LOOP);
        }
        /** ���ʂ�ݒ� */
        void SoundManager::SetVolume(std::string_view key, int volume) {
            auto res = _game.GetResourceServer();
            auto&& [filename, handle] = res.GetSoundInfo(key);

            if (handle != -1) {
                // �ǂݍ��ݗL��
                ChangeVolumeSoundMem(volume, handle);
            }
            else {
                // �ǂݍ��ݖ���
                SetVolumeMusic(volume);
            }
        }
        /** ��~ */
        void SoundManager::StopSound(std::string_view key) {
            auto res = _game.GetResourceServer();
            auto&& [filename, handle] = res.GetSoundInfo(key);

            if (handle != -1) {
                // �ǂݍ��ݗL��
                StopSoundMem(handle);
            }
            else {
                // �ǂݍ��ݖ���
                StopMusic();
            }
        }
        /** �Đ� */
        void SoundManager::Play(std::string_view key, int playType) {
            if (_isMute) {
                return;
            }

            auto res = _game.GetResourceServer();
            auto&& [filename, handle] = res.GetSoundInfo(key);

            if (handle != -1) {
                // �ǂݍ��ݗL��
                PlaySoundMem(handle, playType, TRUE);
            }
            else {
                // �ǂݍ��ݖ���
                PlayMusic(filename.c_str(), playType);
            }
        }
    } // namspace Sound
}// namespace AppFrame