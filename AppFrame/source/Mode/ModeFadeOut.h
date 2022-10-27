/*********************************************************************
 * @file   ModeFadeOut.h
 * @brief フェードアウトクラスの宣言
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#pragma once
#include "ModeFade.h"
 /**
  * @namespace AppFrame
  * @brief     アプリケーションフレーム
  */
namespace AppFrame {
  class GameBase;
  /**
   * @namespace Mode
   * @brief     モード関係
   */
  namespace Mode {
    /**
     * @class ModeFadeOut
     * @brief フェードアウトクラスの宣言
     */
    class ModeFadeOut : public ModeFade {
    public:
      /**
       * @brief           コンストラクタ
       *
       * @param[in] game　ゲームベースクラス
       */
      ModeFadeOut(GameBase& game);
      /**
       * @brief           デストラクタ
       */
      virtual ~ModeFadeOut();
      /**
       * @brief           入り口処理
       */
      void Enter() override;
      /**
       * @brief           更新処理
       */
      void Process() override;
    };
  } // namespace Mode
} // namespace AppFrame