/*********************************************************************
 * @file   ModeFadeIn.h
 * @brief フェードインクラスの宣言
 * 
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#pragma once
#include "ModeFade.h"

namespace AppFrame {

    namespace Mode {
        /**
         * @class ModeFadeIn
         * @brief フェードインクラスの宣言
         */
        class ModeFadeIn : public ModeFade {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param[in] game　ゲームベースクラス
             */
            ModeFadeIn(GameBase& game);
            /**
             * @brief デストラクタ
             *
             */
            virtual ~ModeFadeIn();
            /**
            * @brief 入り口処理
            */
            void Enter() override;
            /**
             * @brief 更新処理
             */
            void Process() override;
        };
    } // namespace Mode
} // namespace AppFrame