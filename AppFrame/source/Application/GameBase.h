/*****************************************************************//**
 * @file   GameBase.h
 * @brief  アプリケーションの基底クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
#include <DxLib.h>

namespace {
	std::string WindowName = "";
	constexpr auto WindowWidth = 1920;
	constexpr auto WindowHeight = 1080;
}
/**
 * @namespace AppFrame
 * @brief  アプリケーションフレーム
 */
namespace AppFrame {
	namespace Resource {
		class ResourceServer;
	}
	namespace Input {
		class InputManager;
	}
	namespace Sound {
		class SoundManager;
	}
	namespace Mode {
		class ModeServer;
	}
	namespace Utility {
		class Utility;
	}
	/**
	 * @class GameBase
	 * @brief アプリケーションの基底クラスの宣言
	 */
	class GameBase {
	public:
		/**
		 * @enumclass  GameState
		 * @brief ゲームの状態
		 */
		enum class GameState {
			Active,  //!< アクティブ
			Pause,   //!< 中断
			End       //!< 終了
		};
		/**
		 * @brief コンストラクタ
		 *
		 */
		GameBase();
		/**
		 * @brief デストラクタ
		 *
		 */
		virtual ~GameBase();
		/**
		 * @brief  初期化処理
		 *
		 * @return 初期化成功の可否
		 */
		virtual bool Initialize(HINSTANCE hInstance);
		/**
		 * @brief  解放処理
		 *
		 */
		virtual void Terminate();
		/**
		 * @brief 更新処理
		 *
		 */
		virtual void Process();
		/**
		 * @brief 描画処理
		 *
		 */
		virtual void Render();
		/**
		 * @brief 入力処理
		 *
		 */
		virtual void Input();
		/**
		 * @brief メインループ
		 *
		 */
		virtual void Run();

		inline virtual std::string SetWindowName() { return WindowName; }

		inline virtual int SetWindowWidthSize() { return WindowWidth; }

		inline virtual int SetWindowHeightSize() { return WindowHeight; }

		inline Mode::ModeServer& GetModeServer() const { return *_modeServer; }

		inline Resource::ResourceServer& GetResourceServer()	const { return *_resServer; }

		inline Sound::SoundManager& GetSoundManager()	const { return *_soundManage; }

		inline static GameBase* GameInstance() { return _gameInstance; }

	protected:
		static GameBase* _gameInstance;                                 //!< ゲームベースクラスのインスタンス
		GameState _gameState{ GameState::Active };                  //!< ゲームの状態
		std::unique_ptr<Mode::ModeServer> _modeServer;            //!< モードサーバーのユニークポインタ
		std::unique_ptr<Resource::ResourceServer> _resServer;  //!< リソースサーバーのユニークポインタ
		std::unique_ptr<Input::InputManager> _inputManage;       //!< インプットマネージャーのユニークポインタ
		std::unique_ptr<Sound::SoundManager> _soundManage;      //!< サウンドマネージャーのユニークポインタ
	};
} // namespace AppFrame