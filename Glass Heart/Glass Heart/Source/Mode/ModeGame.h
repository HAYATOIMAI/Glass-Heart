/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  ゲーム内クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeMain.h"
#include <AppFrame.h>
#include <memory>

namespace GlassHeart {
    namespace Application {
        class GameMain;
    }
    namespace Camera {
        class CameraManager;
    }
    namespace Object {
        class ObjectFactory;
    }
    namespace UI {
        class UI;
    } // namespace
    namespace Mode {
        /**
         * @class ModeGame
         * @brief ゲーム内クラスの宣言
         */
        class ModeGame : public ModeMain {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param[in] game ゲームメインクラスへの参照
             */
            ModeGame(Application::GameMain& game);
            /**
             * @brief デストラクタ
             *
             */
            ~ModeGame() = default;
            /**
             * @brief 初期化処理
             *
             */
            void Init() override;
            /**
             * @brief 入り口処理
             *
             */
            void Enter() override;
            /**
             * @brief 入力処理
             *
             * @param[in] input インプットマネージャークラスへの参照
             */
            void Input(AppFrame::InputManager& input) override;
            /**
             * @brief 更新処理
             *
             */
            void Process() override;
            /**
             * @brief 描画処理
             *
             */
            void Render() override;
            /**
             * @brief 終了処理
             *
             */
            void Exit() override;
        private:
            int _teamLogo{ -1 };         //!< チームロゴ画像用ハンドル 
            int _titleLogo{ -1 };        //!< タイトル画像用ハンドル
            int _deathDrawHundle{ -1 };  //!< 死亡時に表示する画像用ハンドル
        };
    } // Mode
} // GlassHeart