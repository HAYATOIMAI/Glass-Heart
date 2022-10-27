/*****************************************************************//**
 * @file   ModeAmg.h
 * @brief  AMG画面クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include "ModeMain.h"
 /**
  * @namespace GlassHeart
  * @brief     プロジェクト名
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  /**
   * @namespace Mode
   * @brief     モード関係
   */
  namespace Mode {
    /**
     * @class ModeAmg
     * @brief AMG画面クラスの宣言
     */
    class ModeAmg : public ModeMain {
    public:
      /**
       * @brief           コンストラクタ
       *                  
       * @param game　    ゲームベースクラス
       */
      ModeAmg(Application::GameMain& game);
      /**
       * @brief           デストラクタ
       *
       */
      ~ModeAmg() = default;
      /**
       * @brief           初期化処理
       *
       */
      void Init() override;
      /**
       * @brief           入り口処理
       *
       */
      virtual void Enter() override;
      /**
       * @brief           入力処理
       *
       * @param[in] input インプットマネージャークラスへの参照
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief           更新処理
       *
       */
      void Process() override;
      /**
       * @brief           描画処理
       *
       */
      void Render() override;
    private:
      std::int_fast32_t _amgLogoHandle{ -1 };  //!< AMGロゴ画像
    };
  } // namespace Mode
} // namespace GlassHeart