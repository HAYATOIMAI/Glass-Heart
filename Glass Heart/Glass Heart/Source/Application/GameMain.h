/*****************************************************************//**
 * @file   GameMain.h
 * @brief  このプロジェクトのメイン処理
 *
 * @author Hayato Imai, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include <memory>

namespace {
	std::string AppWindowName = "Glass Heart";
	constexpr auto AppWindowWidthSize = 1920;
	constexpr auto AppWindowHeightSize = 1080;
}
/**
 * @namespace GlassHeart
 * @brief プロジェクト名
 */
namespace GlassHeart {
	namespace Object {
		class ObjectServer;
		class ObjectFactory;
	}
	namespace Effect {
		class EffectServer;
	}
	namespace UI {
		class UI;
	} // namespace
	/**
	 * @namespace Application
	 * @brief ゲーム本体
	 */
	namespace Application {
		/**
		 * @class GameMain
		 * @brief このプロジェクトのメイン処理
		 */
		class GameMain : public AppFrame::GameBase {
			using base = AppFrame::GameBase;
		public:
			/**
			 * @brief コンストラクタ
			 *
			 */
			GameMain();
			/**
			 * @brief デストラクタ
			 *
			 */
			~GameMain() override;
			/**
			 * @brief  初期化処理
			 *
			 * @return 初期化成功の可否
			 */
			bool Initialize(HINSTANCE hInstance) override;
			/**
			 *  @brief 解放処理
			 */
			void Terminate() override;
			/**
			 * @brief 入力処理
			 */
			void Input() override;
			/**
			 * @brief 更新処理
			 */
			void Process() override;
			/**
			 * @brief 描画処理
			 */
			void Render() override;
			/**
			 * @brief メインループ
			 */
			void Run() override;

			inline std::string SetWindowName() override { return AppWindowName; }

			inline int SetWindowWidthSize() override { return AppWindowWidthSize; }

			inline int SetWindowHeightSize() override { return AppWindowHeightSize; }

			inline Object::ObjectServer& GetObjectServer() const { return *_objServer; }

			inline Object::ObjectFactory& GetObjectFactory() const { return *_objFactory; }

			inline UI::UI& GetUI() const { return *_ui; }
		private:
			std::unique_ptr<Object::ObjectServer> _objServer;     //!< オブジェクトサーバーのユニークポインタ
			std::unique_ptr<Object::ObjectFactory> _objFactory;	  //!< オブジェクトファクトリーのユニークポインタ
			std::unique_ptr<GlassHeart::UI::UI> _ui;                    //!< UIのユニークポインタ
		};
	} // namespace Application
} // namespace GlassHeart