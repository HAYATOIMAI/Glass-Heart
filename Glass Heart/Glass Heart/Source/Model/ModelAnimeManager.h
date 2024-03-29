/*****************************************************************//**
 * @file   ModelAnimeManager.h
 * @brief  3Dモデル管理
 *
 * @author Hayato Imai, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModelManager.h"
#include <string_view>
#include <unordered_map>
 /**
  * @namespace GlassHeart
  * @brief     プロジェクト名
  */
namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }
  /**
   * @namespace Model
   * @brief     モデル関係
   */
  namespace Model {
    /**
     * @class ModelAnimeManager
     * @brief モデルアニメーション管理クラス
     */
    class ModelAnimeManager : public ModelManager {
    public:
      /**
       * @brief　                コンストラクタ
       *                         
       * @param[in] owner        オブジェクトベースクラスへの参照
       */
      ModelAnimeManager(GlassHeart::Object::ObjectBase& owner);
      /**
       * @brief　                デストラクタ
       */
      virtual ~ModelAnimeManager() override;
      /**
       * @brief                  初期化
       */
      void Init() override;
      /**
       * @brief                  アニメーションの登録
       *                         
       * @param[in] key          任意の文字列キー
       * @param[in] animIndex    関連付けるアニメインデックス
       */
      void Register(std::string_view key, int animIndex);
      /**
       * @brief                  更新処理
       */
      void Update() override;
      /**
       * @brief                  描画処理
       */
      void Draw() override;
      /**
       * @brief                  アニメーションの変更
       *
       * @param[in] key          任意の文字列キー
       * @param[in] repeate      アニメーションのループ可否
       * @param[in] newAnimIndex アニメインデックス
       */
      void ChangeAnime(std::string_view key, bool repeate = false);
      /**
       * @brief                  アニメーションブレンド
       */
      void AnimeBlend();
      /**
       * @brief                  アニメーションを繰り返した回数の取得
       *                         
       * @return                 繰り返した回数
       */
      int GetRepeatedCount() const { return _repeatedCount; }
      /**
       * @brief                  アニメーションの総時間を取得
       *                         
       * @return                 総時間
       */
      float GetPlayTime() const { return _playTime; }
      /**
       * @brief                  アニメーションの総時間を取得
       *                         
       * @return                 総時間
       */
      float GetPlayProgress() const { return _playTime / _totalTime; }
      /**
       * @brief                  再生時間の掛率設定
       *                         
       * @param[in] timeRate     再生時間の掛率
       */
      void SetTimeRate(const float timeRate) { _timeRate = timeRate; }
      /**
       * @brief                  再生時間掛率の取得
       *                         
       * @return                 再生時間掛率
       */
      float GetTimeRate() const { return _timeRate; }
    private:
      bool _isRepeate{ false };                 //!< アニメーションのループ可否
      float _animrate{ 1.f };                   //!< アニメーションブレンド率
      float _playTime{ 0.0f };                  //!< 総時間
      float _timeRate{ 1.f };                   //!< 再生時間掛率
      float _totalTime{ 0.0f };                 //!< アニメーションの総時間
      std::int_fast16_t _animIndex{ -1 };       //!< アニメーション番号
      std::int_fast16_t _attachIndex{ -1 };     //!< アタッチする番号
      std::int_fast16_t _oldAttachIndex{ -1 };  //!< 前のアタッチ番号
      std::int_fast16_t _repeatedCount{ 0 };    //!< アニメーションを繰り返した回数
      /** レジストリ */
      std::unordered_map<std::string, std::int_fast32_t> _registry;
    };
  } //  namespace Model
} //  namespace GlassHeart