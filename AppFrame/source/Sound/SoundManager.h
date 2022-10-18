/*****************************************************************//**
 * @file   SoundManager.h
 * @brief  サウンドマネージャークラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <string>
 /**
  * @namespace AppFrame
  * @brief  アプリケーションフレーム
  */
namespace AppFrame {
  class GameBase;
  /**
   * @namespace Sound 
   * @brief サウンド関係
   */
  namespace Sound {
    /**
     * @class SoundManager
     * @brief サウンドマネージャークラスの宣言
     */
    class SoundManager {
    public:
      /**
       * @brief コンストラクタ
       *
       * @param[in] game ゲームベースクラスへの参照
       */
      SoundManager(GameBase& game) : _game{ game } {};
      /**
       * @brief デストラクタ
       *
       */
      virtual ~SoundManager();
      /**
       * @brief 再生(ループ無し)
       *
       * @param[in] key 登録済みの文字列
       */
      void Play(std::string_view key);
      /**
       * @brief ループ再生
       *
       * @param[in] key 登録済みの文字列
       */
      void PlayLoop(std::string_view key);
      /**
       * @brief 音量を設定
       *
       * @param[in] key 登録済みの文字列
       * @param volume  音量
       */
      void SetVolume(std::string_view key, int volume);
      /**
       * @brief　停止
       *
       * @param[in] key 登録済みの文字列
       */
      void StopSound(std::string_view key);

      inline void SetMute(bool isMute) { _isMute = isMute; }
    private:
      /**
       * @brief　再生
       *
       * @param[in] key       登録済みの文字列
       * @param[in] playType  再生の種類
       */
      void Play(std::string_view key, int playType);

      GameBase& _game;        //!< ゲームベースクラスへの参照
      bool _isMute{ false };  //!< ミュートにするかのフラグ
    };
  } // namespace Sound
} // namespace AppFrame