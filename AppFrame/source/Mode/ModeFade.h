/*****************************************************************//**
 * @file   ModeFade.h
 * @brief  モードのフェードクラス宣言
 *            画面の最前面にフルスクリーンサイズの画像を重ねてアルファ値によるフェードを行う
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeBase.h"

namespace AppFrame {

    namespace Mode {
        /**
         * @class ModeFade
         * @brief モードのフェードクラス宣言
         */
        class ModeFade : public ModeBase {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param[in] game　ゲームベースクラスへの参照
             */
            ModeFade(GameBase& game);
            /**
             * @brief デストラクタ
             *
             */
            virtual ~ModeFade();
            /**
             * @brief 初期化処理
             *
             */
            virtual void Init() override;
            /**
             * @brief 入り口処理
             */
            virtual void Enter() override;
            /**
             * @brief 更新処理
             */
            virtual void Process() override;
            /**
             * @brief 描画処理
             */
            virtual void Render() override;
        protected:
            int _width{ 1920 };          //!< 縦幅
            int _height{ 1080 };         //!< 横幅
            unsigned int _color{ 0 };  //!< 色情報
            float _alpha{ 0.f };         //!< アルファ値
            float _deltaAlpha{ 0.f };  //!< アルファ値との差分
        };
    } // namespace Mode
} // namespace AppFrame