/*****************************************************************//**
 * @file   StateManager.h
 * @brief ステートマネージャークラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <AppFrame.h>

namespace AppFrame {
	namespace Input {
		class InputManager;
	}
}
/**
 * @namespace GlassHeart
 * @brief プロジェクト名
 */
namespace GlassHeart {
	namespace Object {
		class ObjectBase;
	}
	/**
	 * @namespace State
	 * @brief  プレイヤーのステート関係
	 */
	namespace State {
		/**
		 * @class StateManager
		 * @brief オブジェクトのステートを管理する
		 */
		class StateManager {
		public:
			/**
			 * @brief コンストラクタ
			 *
			 * @param[in] key    最初のステートに関連付ける任意の文字列
			 * @param[in] state 最初のステート
			 */
			StateManager(std::string_view key, std::shared_ptr<AppFrame::State::StateBaseRoot> state);
			/**
			 * @brief ステートの登録
			 *
			 * @param[in] key    最初のステートに関連付ける任意の文字列
			 * @param[in] state 最初のステート
			 */
			void Register(std::string_view key, std::shared_ptr<AppFrame::State::StateBaseRoot> state);
			/**
			 * @brief ステートのプッシュバック
			 *           リストの一番後ろ(最前面)にステートをプッシュ追加する
			 *           stateの入口処理Enterを実行する
			 *
			 * @param[in] key 登録済みのシーンに関連付けた文字列
			 */
			void PushBack(std::string_view key);
			/**
			 * @brief ステートのポップバック
			 *           リストの一番後ろ(最前面)のステートをポップ除外する
			 *           stateの出口処理Exitを実行する
			 */
			void PopBack();
			/**
			 * @brief ステートの遷移
			 *
			 * @param[in] key 登録済みのステートに関連付けた文字列
			 */
			void GoToState(std::string_view key);
			/**
			 * @brief リストの一番後ろ(最前面)のステートの真下に挿入する
			 *           stateの入口処理Enterを実行する
			 *
			 * @param[in] key 登録済みのステートに関連付けた文字列
			 */
			void InsertBelowBack(std::string_view key);
			/**
			 * @brief 入力処理
			 *           リストの一番後ろ(最前面)のステートだけ処理する
			 *
			 * @param[in] input インプットマネージャークラスへの参照
			 */
			void Input(AppFrame::Input::InputManager& input);
			/**
			 * @brief 更新処理
			 *           リストの一番後ろ(最前面)のステートだけ処理する
			 */
			void Update();
			/**
			 * @brief 描画処理
			 *           リストの全ステートを処理する
			 */
			void Draw() const;
		private:
			//!< 状態のレジストリ
			std::unordered_map<std::string, std::shared_ptr<AppFrame::State::StateBaseRoot>>	_registry;
			//!< 状態のリスト
			std::list<std::shared_ptr<AppFrame::State::StateBaseRoot>> _states;
		};
	} // namespace State
} // namespace GlassHeart