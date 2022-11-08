/*****************************************************************//**
 * @file   ModeMain.h
 * @brief  モードの基底クラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include <cstdint>
 /**
  * @namespace GlassHeart
  * @brief     プロジェクト名
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Object {
    class ObjectServer;
    class ObjectFactory;
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
     * @class ModeMain
     * @brief モードの基底クラスの宣言
     */
    class ModeMain : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief           コンストラクタ
       *
       * @param[in] game　ゲームメインクラスの参照
       */
      ModeMain(Application::GameMain& game);
      /**
       * @brief           デストラクタ
       */
      ~ModeMain() = default;
      /**
       * @brief           初期化処理
       */
      virtual void Init() override {};
      /**
       * @brief           入り口処理
       */
      virtual void Enter() override {};
      /**
       * @brief           入力処理
       *
       * @param[in] input インプットマネージャークラスへの参照
       */
      virtual void Input(AppFrame::Input::InputManager& input) override {};
      /**
       * @brief           更新処理
       */
      virtual void Process()override {};
      /**
       * @brief　         描画処理
       */
      virtual void Render() override {};
      /**
       * @brief           終了処理
       */
      virtual void Exit() override {};
      /**
       * @brief           ゲームメインクラスを取得する
       * 
       * @return          ゲームメインクラスの参照
       */
      inline Application::GameMain& GetGameMain() const { return _gameMain; }
      /**
       * @brief           オブジェクトファクトリーを取得する
       * 
       * @return          オブジェクトファクトリーの参照
       */
      Object::ObjectFactory& GetObjectFactory();
      /**
       * @brief           オブジェクトサーバーを取得する
       * 
       * @return          オブジェクトサーバーの参照
       */
      Object::ObjectServer& GetObjectServer();
      /**
       * @brief           UIを取得する
       * 
       * @return          UIの参照
       */
      UI::UI& GetUI();
    protected:
      Application::GameMain& _gameMain;   //!< ゲームメインクラスへの参照
      int_fast16_t _fadeCount;            //!< 自動フェードインアウト用カウンタ
      static int_fast16_t _count;         //!< タイマー用フレームカウント
      static int_fast16_t _countSeconds;  //!< タイマー用フレームカウント
    };
  } // namespace Mode
} // namespace GlassHeart