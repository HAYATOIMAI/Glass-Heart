/*****************************************************************//**
 * @file   ModeClear.h
 * @brief  ゲームクリアクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include "ModeMain.h"
#include <cstdint>
#include "../Object/ObjectBase.h"
 /**
  * @namespace GlassHeart
  * @brief プロジェクト名
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  /**
   * @namespace Mode
   * @brief モード関係
   */
  namespace Mode {
    /**
     * @class ModeClear
     * @brief ゲームクリアクラスの宣言
     */
    class ModeClear : public ModeMain {
    public:
      /**
       * @brief コンストラクタ
       *
       * @param game　ゲームベースクラス
       */
      ModeClear(Application::GameMain& game);
      /**
       * @brief デストラクタ
       *
       */
      ~ModeClear() = default;
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
      std::int_fast32_t _gameClear{ -1 };  //!< ゲームクリア画像
      std::int_fast32_t _gameOver{ -1 };   //!< ゲームオーバー画像
    };
  }// namespace Mode
} // namespace GlassHeart 