
/*****************************************************************//**
 * @file   GameBase.h
 * @brief  アプリケーションの基底クラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <DxLib.h>
#include <EffekseerForDXLib.h>

namespace AppFrame {
    /** 二重インクルード防止 */
    class ResourceServer;
    class InputManager;
    class SoundManager;
    class ModeServer;
    /**
     * @class GameBase
     * @brief アプリケーションの基底クラスの宣言
     */
    class GameBase {
    public:
        /**
         * @enumclass  Enum
         * @brief ゲームの状態
         */
        enum class GameState {
            Active,  //!< アクティブ
            Pause,   //!< 中断
            End      //!< 終了
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

        inline ModeServer& GetModeServer() const { return *_modeServer; }

        inline ResourceServer& GetResourceServer()	const { return *_resServer; }

        inline SoundManager& GetSoundManager()	const { return *_soundManage; }

        inline static GameBase* GameInstance() { return _gameInstance; }

    protected:
        static GameBase* _gameInstance;              //!< ゲームベースクラスのインスタンス
        GameState _gameState{ GameState::Active };   //!< ゲームの状態
        std::unique_ptr<ModeServer> _modeServer;     //!< モードサーバーのユニークポインタ
        std::unique_ptr<ResourceServer> _resServer;  //!< リソースサーバーのユニークポインタ
        std::unique_ptr<InputManager> _inputManage;  //!< インプットマネージャーのユニークポインタ
        std::unique_ptr<SoundManager> _soundManage;  //!< サウンドマネージャーのユニークポインタ
    };
} //AppFrame