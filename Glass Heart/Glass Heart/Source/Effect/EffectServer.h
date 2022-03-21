/*****************************************************************//**
 * @file   EffectServer.h
 * @brief  エフェクト管理クラスの宣言
 *
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <EffekseerForDXLib.h>
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <string>
#include "../Application/GameMain.h"

namespace GlassHeart {
	namespace Effect {
		class EffectServer {
		public:

			using EffectMap = std::unordered_map<std::string, std::pair<std::string, float>>;

			EffectServer(GameMain& game);
			~EffectServer();
			/**
			 * @brief 初期化
			 * 
			 */
			void Initialize();
			/**
			 * @brief リソースの消去処理
			 * 
			 */
			void Clear();
			/**
			 * @brief エフェクトリソースのロード
			 * 
			 * @param[in] key キーとなる文字列
			 * @param[in] filename ファイル名
			 * @param[in] magnification 拡大率
			 */
			void LoadEffect(std::string_view key, std::string_view filename, float magnification);
			/**
			 * @brief エフェクトリソース一括読み込み
			 * 
			 * @param effectmap
			 */
			void LoadEfeects(const EffectMap& effectmap);
			/**
			 * @brief 相対パスの変更
			 * 
			 * @param[in] path 相対パス名
			 */
			void ChangeCurrentFile(std::string_view path);
			/**
			 * @brief エフェクトリソースの取得
			 * 
			 * @param key
			 * @return エフェクトのリソースハンドル 
			 */
			int GetEffectResHandle(std::string_view key);
			/**
			 * @brief エフェクトリソースが存在しているかを返す
			 * 
			 * @param key
			 * @return リソースがあるかの真偽
			 */
			bool GetEffectResContein(std::string_view key);
		private:
			GameMain& _game;
			std::filesystem::path _currentdirectory;
			std::unordered_map<std::string, int> _effects;
		};
	}
}
