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
#include <cstdint>
 /**
  * @namespace GlassHeart
  * @brief プロジェクト名
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Camera {
    class CameraManager;
  }
  namespace Object {
    class ObjectFactory;
    class PlayerCreate;
    class GirlCreate;
    class StageCreate;
    class FollowCameraCreate;
    class CheckPointCreate;
    class GoalPointCreate;
  }
  namespace UI {
    class UI;
  } // namespace
  /**
   * @namespace Mode
   * @brief     モード関係
   */
  namespace Mode {
    /**
     * @class ModeGame
     * @brief ゲーム内クラスの宣言
     */
    class ModeGame : public ModeMain {
    public:
      /**
       * @brief           コンストラクタ
       *
       * @param[in] game  ゲームメインクラスへの参照
       */
      ModeGame(Application::GameMain& game);
      /**
       * @brief           デストラクタ
       */
      ~ModeGame() = default;
      /**
       * @brief           初期化処理
       */
      void Init() override;
      /**
       * @brief           入り口処理
       */
      void Enter() override;
      /**
       * @brief           入力処理 
       *
       * @param[in] input インプットマネージャークラスへの参照
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief           更新処理
       */
      void Process() override;
      /**
       * @brief           描画処理
       */
      void Render() override;
      /**
       * @brief           終了処理
       */
      void Exit() override;
    private:
      /**
       * @brief           オブラートを生成
       */
      void ObjectRegister();
      /**
       * @brief           タイマー経過処理
       */
      void TimerProcess();
      /**
       * @brief           UIを描画
       */
      void UiRenderring();
      std::int_fast32_t _deathDrawHundle{ -1 };  //!< 死亡時に表示する画像用ハンドル
      std::int_fast32_t _teamLogo{ -1 };         //!< チームロゴ画像用ハンドル
      std::int_fast32_t _titleLogo{ -1 };        //!< タイトル画像用ハンドル
    };
  } // namespace Mode
} // namespace GlassHeart