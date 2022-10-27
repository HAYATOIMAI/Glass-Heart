/*****************************************************************//**
 * @file   ModeClear.cpp
 * @brief  ゲームクリアクラスの宣言
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#include "ModeClear.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectServer.h"
#include "../UI/UI.h"
#include "../Application/GameMain.h"

std::int_fast16_t GlassHeart::Mode::ModeMain::_count;
std::int_fast16_t GlassHeart::Mode::ModeMain::_countSeconds;
/** コンストラクタ */
GlassHeart::Mode::ModeClear::ModeClear(Application::GameMain& game) : ModeMain{ game } {}
/** 初期化処理 */
void GlassHeart::Mode::ModeClear::Init() {
  // 使用する画像のテーブル
  const AppFrame::Resource::ResourceServer::GraphMap useGraph{
 {"TitleBG",    {"Title/TitleBG.png",     1, 1, 1920, 1080}},
 {"Result",     {"Result/result4.png",    1, 1, 1920, 1080}},
 {"GameClear",  {"Result/GameClear.png",  1, 1, 1920, 1080}},
 {"GameOver",   {"Result/GameOver.png",   1, 1, 1920, 1080}},
  };

  // リソースサーバーを取得
  auto& res = GetResourceServer();
  // 画像の読み込み
  res.LoadGraphics(useGraph);
  // 画像のハンドルの取得
  _gameClear = res.GetGraph("GameClear");
  _gameOver = res.GetGraph("GameOver");
}
/** 入り口処理 */
void GlassHeart::Mode::ModeClear::Enter() {}
/** 入力処理 */
void GlassHeart::Mode::ModeClear::Input(AppFrame::Input::InputManager& input) {
  if (input.GetJoyPad().GetXinputButtonB()) {
    GetModeServer().GoToMode("Title");
  }
}
/** 更新処理 */
void GlassHeart::Mode::ModeClear::Process() {}
/** 描画処理 */
void GlassHeart::Mode::ModeClear::Render() {
  if (_countSeconds == 0) {
    DrawGraph(0, 0, _gameOver, FALSE);
  }
  else {
    DrawGraph(0, 0, _gameClear, FALSE);
  }
  GetUI().NumberRender(1650, 700, 200, 2.0);

  auto x = 0; auto y = 0; auto size = 32;
  auto black = GetColor(0, 0, 0);

  DrawFormatString(x, y, black, "現在の時間: %d ", _count); y += size;
  DrawFormatString(x, y, black, "現在の時間: %d秒 ", _countSeconds); y += size;
}
/** 終了処理 */
void GlassHeart::Mode::ModeClear::Exit() {
  //!< オブジェクトを消去
  GetObjectServer().AllClear();
}