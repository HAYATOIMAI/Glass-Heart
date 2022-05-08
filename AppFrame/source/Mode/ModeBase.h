/*****************************************************************//**
 * @file   ModeBase.h
 * @brief モードの基底クラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>

namespace AppFrame {
    class GameBase;
    namespace Input {
        class InputManager;
    }
    namespace Resource {
        class ResourceServer;
    }
    namespace Sound {
        class SoundManager;
    } // namespace
    namespace Mode {
        class ModeServer;
        /**
         * @class ModeBase
         * @brief モードの基底クラス
         */
        class ModeBase {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param[in] game　ゲームベースクラス
             */
            ModeBase(GameBase& game);
            /**
             * @brief デストラクタ
             *
             */
            virtual ~ModeBase();
            /**
             * @brief 初期化処理
             *
             */
            virtual void Init() = 0;
            /**
             * @brief 入り口処理
             */
            virtual void Enter() {};
            /**
             * @brief 入力処理
             *
             * @param[in] input インプットマネージャークラスへの参照
             */
            virtual void Input(Input::InputManager& input) {};
            /**
             * @brief 更新処理
             */
            virtual void Process() {};
            /**
             * @brief 描画処理
             */
            virtual void Render() {};
            /**
             * @brief 出口処理
             */
            virtual void Exit() {};

            inline GameBase& GetGame() const { return _game; };

            Resource::ResourceServer& GetResourceServer();

            Sound::SoundManager& GetSoundManager();

            ModeServer& GetModeServer();

        protected:
            GameBase& _game;  //!< ゲームベースクラスへの参照
        };
    } // namespace Mode
} // namespace AppFrame