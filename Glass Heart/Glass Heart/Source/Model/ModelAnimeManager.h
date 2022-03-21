
/*****************************************************************//**
 * @file   ModelAnimeManager.h
 * @brief  3Dモデル管理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/

#pragma once
#include "ModelManager.h"
#include <string_view>
#include <unordered_map>

namespace GlassHeart {

    namespace Object {
        class ObjectBase;
    }

    namespace Model {

        /**
         * @class ModelAnimeManager
         * @brief モデルアニメーション管理クラス
         */
        class ModelAnimeManager : public ModelManager {
        public:
            ModelAnimeManager(GlassHeart::Object::ObjectBase& owner);

            virtual ~ModelAnimeManager() override;
            /**
             * @brief 初期化
             * 
             */
            void Init() override;
            /**
             * @brief アニメーションの登録
             * 
             * @param[in] key 任意の文字列キー
             * @param[in] animIndex 関連付けるアニメインデックス
             */
            void Register(std::string_view key, int animIndex);
            /**
             * @brief 更新
             * 
             */
            void Update() override;
            /**
             * @brief 描画
             * 
             */
            void Draw() override;
            /**
             * @brief アニメーションの変更
             * 
             * @param key 任意の文字列キー
             * @param repeate アニメーションのループ可否
             * @param[in] newAnimIndex アニメインデックス
             */
            void ChangeAnime(std::string_view key, bool repeate = false);
            /**
             * @brief アニメーションブレンド
             * 
             */
            void AnimeBlend();
            /**
             * @brief アニメーションを繰り返した回数の取得
             * 
             * @return 繰り返した回数
             */
            int GetRepeatedCount() const { return _repeatedCount; }
            /**
             * @brief アニメーションの総時間を取得
             *
             * @return 総時間
             */
            float GetPlayTime() const { return _playTime; }
            /**
             * @brief アニメーションの総時間を取得
             *
             * @return 総時間
             */
            float GetPlayProgress() const { return _playTime / _totalTime; }
            /**
             * @brief 再生時間の掛率設定
             *
             * @param[in] timeRate 再生時間の掛率
             */
            void SetTimeRate(float timeRate) { _timeRate = timeRate; }
            /**
             * @brief 再生時間掛率の取得
             * 
             * @return 再生時間掛率 
             */
            float GetTimeRate() { return _timeRate; }
        private:
            std::unordered_map<std::string, int> _registry;
            int _animIndex{ -1 };
            int _oldattachIndex{ -1 };
            int _attachIndex{ -1 };
            int _repeatedCount{ 0 };
            float _playTime{ 0 };
            float _totalTime{ 0 };
            float _timeRate{ 1.f };
            float _animrate{ 1.f };//!アニメーションブレンド率
            bool _repeate{ false };
        };
    } // Model
} // GlassHeart