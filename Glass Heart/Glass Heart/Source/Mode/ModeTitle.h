
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
   
    class GameMain;

    namespace Mode {
        /**
         * @class 
         * @brief 
         */
        class ModeTitle :  public ModeMain {
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
            int _title{ -1 };               //!< タイトル画像
            int _titleBgHandle{ -1 };       //!< ゲームタイトル画像
            int _titleButtonHandle{ -1 };   //!< Press Any Button画像
            int _titleLogo{ -1 };           //!< 背景画像
        };
    }
}
