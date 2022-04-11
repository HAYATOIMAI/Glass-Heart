/*****************************************************************//**
 * @file   ModeTeamLogo.h
 * @brief  チームロゴ画面クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeMain.h"
#include <AppFrame.h>

namespace GlassHeart {
    namespace Application {
        class GameMain;
    }
    namespace Mode {
        /**
         * @class ModeTeamLogo
         * @brief チームロゴ画面クラス
         */
        class ModeTeamLogo : public ModeMain {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param game　ゲームベースクラス
             */
            ModeTeamLogo(Application::GameMain& game);
            /**
             * @brief デストラクタ
             *
             */
            ~ModeTeamLogo() = default;
            /**
             * @brief 初期化処理
             *
             */
            void Init() override;
            /**
             * @brief 入り口処理
             *
             */
            virtual void Enter() override;
            /**
             * @brief 入力処理
             *
             * @param input インプットマネージャークラスへの参照
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
        private:
            int _teamLogo{ -1 };   //!< 背景画像用ハンドル    
        };
    } // Mode
} // GlassHeart