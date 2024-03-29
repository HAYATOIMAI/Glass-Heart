/*****************************************************************//**
 * @file   ModeTeamLogo.h
 * @brief  チームロゴ画面クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeMain.h"
#include <cstdint>
#include <AppFrame.h>
 /**
	* @namespace GlassHeart
	* @brief プロジェクト名
	*/
namespace GlassHeart {
	namespace Application {
		class GameMain;
	}
	/**
   * @namespace Mode
   * @brief モード関係
   */
	namespace Mode {
		/**
		 * @class ModeTeamLogo
		 * @brief チームロゴ画面クラス
		 */
		class ModeTeamLogo : public ModeMain {
		public:
			/**
			 * @brief           コンストラクタ
			 *
			 * @param[in] game　ゲームメインクラスの参照
			 */
			ModeTeamLogo(Application::GameMain& game);
			/**
			 * @brief           デストラクタ
			 *
			 */
			~ModeTeamLogo() = default;
			/**
			 * @brief           初期化処理
			 *
			 */
			void Init() override;
			/**
			 * @brief           入り口処理
			 *
			 */
			virtual void Enter() override;
			/**
			 * @brief           入力処理
			 *
			 * @param[in] input インプットマネージャークラスへの参照
			 */
			void Input(AppFrame::Input::InputManager& input) override;
			/**
			 * @brief           更新処理
			 *
			 */
			void Process() override;
			/**
			 * @brief           描画処理
			 */
			void Render() override;
		private:
			std::int_fast32_t _teamLogo{ -1 };  //!< 背景画像用ハンドル
		};
	} // namespace Mode
} // namespace GlassHeart