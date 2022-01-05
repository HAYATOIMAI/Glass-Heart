
/*****************************************************************//**
 * @file   SoundManager.h
 * @brief  サウンドマネージャークラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <string>

namespace AppFrame {

    class GameBase;

    class SoundManager {
    public:
        /**
         * @brief
         * 
         * @param game
         */
        SoundManager(GameBase& game) : _game{ game } {};
        /**
         * @brief
         * 
         */
        virtual ~SoundManager();
        /**
         * @brief
         * 
         * @param key
         */
        void Play(std::string_view key);
        /**
         * @brief
         * 
         * @param key
         */
        void PlayLoop(std::string_view key);
        /**
         * @brief
         * 
         * @param key
         * @param volume
         */
        void SetVolume(std::string_view key, int volume);

        void SetMute(bool isMute) { _isMute = isMute; }
    private:
        void Play(std::string_view key, int playType);

        GameBase& _game;
        bool _isMute{ false };
    };
}