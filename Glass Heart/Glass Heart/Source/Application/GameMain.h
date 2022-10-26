/*****************************************************************//**
 * @file   GameMain.h
 * @brief  このプロジェクトのメイン処理
 *
 * @author Hayato Imai, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include <memory>

namespace {
  std::string AppWindowName = "Glass Heart";               //!< アプリケーションの名前
  constexpr std::int_fast16_t AppWindowWidthSize = 1920;   //!< 画面の縦幅
  constexpr std::int_fast16_t AppWindowHeightSize = 1080;  //!< 画面の横幅
}
/**
 * @namespace GlassHeart
 * @brief     プロジェクト名
 */
namespace GlassHeart {
  namespace Object {
    class ObjectServer;
    class ObjectFactory;
  }
  namespace UI {
    class UI;
  } // namespace
  /**
   * @namespace Application
   * @brief     ゲーム本体
   */
  namespace Application {
    /**
     * @class GameMain
     * @brief このプロジェクトのメイン処理
     */
    class GameMain : public AppFrame::GameBase {
      using base = AppFrame::GameBase;
    public:
      /**
       * @brief  コンストラクタ
       */
      GameMain();
      /**
       * @brief  デストラクタ
       */
      ~GameMain() override;
      /**
       * @brief  初期化処理
       *
       * @return 初期化成功の可否
       */
      bool Initialize(HINSTANCE hInstance) override;
      /**
       *  @brief 解放処理
       */
      void Terminate() override;
      /**
       * @brief  入力処理
       */
      void Input() override;
      /**
       * @brief  更新処理
       */
      void Process() override;
      /**
       * @brief  描画処理
       */
      void Render() override;
      /**
       * @brief  メインループ
       */
      void Run() override;
      /**
       * @brief  アプリケーションの名前を設定する
       * 
       * @return アプリケーションの名前を返す
       */
      inline std::string SetWindowName() override { return AppWindowName; }
      /**
       * @brief  画面の縦幅を設定する
       * 
       * @return 画面の縦幅を返す
       */
      inline std::int_fast16_t SetWindowWidthSize() override { return AppWindowWidthSize; }
      /**
       * @brief  画面の横幅を設定する
       * 
       * @return 画面の横幅を返す
       */
      inline std::int_fast16_t SetWindowHeightSize() override { return AppWindowHeightSize; }
      /**
       * @brief  オブジェクトサーバーの取得
       * 
       * @return オブジェクトサーバーの参照
       */
      inline Object::ObjectServer& GetObjectServer() const { return *_objServer; }
      /**
       * @brief  オブジェクトファクトリーの取得
       * 
       * @return オブジェクトファクトリーの参照
       */
      inline Object::ObjectFactory& GetObjectFactory() const { return *_objFactory; }
      /**
       * @brief  UIの取得
       * 
       * @return UIの参照
       */
      inline UI::UI& GetUI() const { return *_ui; }
    private:
      std::unique_ptr<Object::ObjectServer> _objServer{ nullptr };    //!< オブジェクトサーバーのユニークポインタ
      std::unique_ptr<Object::ObjectFactory> _objFactory{ nullptr };  //!< オブジェクトファクトリーのユニークポインタ
      std::unique_ptr<UI::UI> _ui{ nullptr };                         //!< UIのユニークポインタ
    };
  } // namespace Application
} // namespace GlassHeart