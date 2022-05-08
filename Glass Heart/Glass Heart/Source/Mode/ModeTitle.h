/*****************************************************************//**
 * @file   ModeTitle.h
 * @brief  タイトル画面クラスの宣言
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
         * @class ModeTitle
         * @brief タイトル画面クラスの宣言
         */
        class ModeTitle : public ModeMain {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param game　ゲームベースクラス
             */
            ModeTitle(Application::GameMain& game);
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
            void Input(AppFrame::Input::InputManager& input) override;
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
            int _title{ -1 };            //!< タイトル画像
            int _titlePlate{ -1 };    //!< 操作説明画像
            int _titlePlate2{ -1 };   //!< 操作説明画像
            int _titleButton{ -1 };   //!< タイトルボタン画像
            int _titleLogo{ -1 };      //!< タイトルロゴ
            int _titleBg{ -1 };         //!< タイトル背景
            int _titleExit{ -1 };      //!< Exitボタン画像
            int _alpha{ 0 };             //!< アルファ値
            int _x{ 0 };                   //!< 
            int _x2{ 0 };                  //!< 
        };
    } // namespace Mode
} // namespace GlassHeart