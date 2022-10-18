/*****************************************************************//**
 * @file   ModeMain.h
 * @brief  モードの基底クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include <cstdint>
 /**
	* @namespace GlassHeart
	* @brief プロジェクト名
	*/
namespace GlassHeart {
	namespace Application {
		class GameMain;
	}
	namespace Object {
		class ObjectServer;
		class ObjectFactory;
	}
	namespace UI {
		class UI;
	} // namespace
	/**
	 * @namespace Mode
	 * @brief モード関係
	 */
	namespace Mode {
		/**
		 * @class ModeMain
		 * @brief モードの基底クラスの宣言
		 */
		class ModeMain : public AppFrame::Mode::ModeBase {
		public:
			/**
			 * @brief コンストラクタ
			 *
			 * @param game　ゲームメインクラス
			 */
			ModeMain(Application::GameMain& game);
			/**
			 * @brief デストラクタ
			 *
			 */
			~ModeMain() = default;
			/**
			 * @brief 初期化処理
			 *
			 */
			void Init() override {};
			/**
			 * @brief 入り口処理
			 *
			 */
			void Enter() override {};
			/**
			 * @brief 入力処理
			 *
			 * @param[in] input インプットマネージャークラスへの参照
			 */
			void Input(AppFrame::Input::InputManager& input) override {};
			/**
			 * @brief 更新処理
			 *
			 */
			void Process()override {};
			/**
			 * @brief　描画処理
			 *
			 */
			void Render() override {};
			/**
			 * @brief 終了処理
			 */
			void Exit() override {};

			inline Application::GameMain& GetGameMain() const { return _gameMain; }

			Object::ObjectFactory& GetObjectFactory();

			Object::ObjectServer& GetObjectServer();

			UI::UI& GetUI();
		protected:
			Application::GameMain& _gameMain;        //!< ゲームメインクラスへの参照
			std::int_fast8_t _fadeCount;             //!< 自動フェードインアウト用カウンタ
			static std::int_fast16_t _count;         //!< タイマー用フレームカウント
			static std::int_fast16_t _countSeconds;  //!< タイマー用フレームカウント
		};
	} // namespace Mode
} // namespace GlassHeart