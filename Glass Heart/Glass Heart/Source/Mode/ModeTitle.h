
/*****************************************************************//**
 * @file   ModeTitle.h
 * @brief  タイトル画面クラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include <AppFrame.h>

namespace GlassHeart {

    class GameMain;

    namespace Mode {
        /**
         * @class 
         * @brief 
         */
        class ModeTitle :  public AppFrame::ModeBase {
        public:
            /**
             * @brief コンストラクタ
             * 
             * @param game　ゲームベースクラス
             */
            ModeTitle(GameMain& game);
            /**
             * @brief デストラクタ
             *
             */
            ~ModeTitle() = default;
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
            int _gameTitleHandle{ -1 };  //!< ゲームタイトル画像
            int _leftClickToStart{ -1 };  //!< Left click to Start画像
            int _titleBgHandle{ -1 };  //!< 背景画像
            int _alpha{ 0 };  //!< アルファ値
        };
    }

}
