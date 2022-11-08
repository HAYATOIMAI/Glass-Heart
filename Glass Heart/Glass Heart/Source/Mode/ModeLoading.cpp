/*********************************************************************
 * @file   ModeLoading.cpp
 * @brief  ローディング画面クラスの処理
 *
 * @author Hayato Imai
 * @date   March 2022
 *********************************************************************/
#include "ModeLoading.h"
#include <AppFrame.h>

namespace {
  constexpr int_fast16_t LoadingTime = 30;          //!< ロード時間
  constexpr int_fast16_t LoadingCount= 60;          //!< ロードが終わっていなかった場合の再ロード時間
  constexpr int_fast16_t RenderingPositionX = 1700; //!< Gif画像の描画位置
  constexpr int_fast16_t RenderingPositionY = 900;  //!< Gif画像の描画位置
  constexpr auto Stage = "Stage";                   //!< リソースマネージャーから呼び出す文字列
  constexpr auto NextMode = "InGame";               //!< 遷移するモードの文字列
}

 /** コンストラクタ */
GlassHeart::Mode::ModeLoading::ModeLoading(Application::GameMain& game) : ModeMain(game) {}
/** 初期化処理 */
void GlassHeart::Mode::ModeLoading::Init() {
  _loadHandle = LoadGraph("resource/Loading/LoadGraphHeart.gif");
  _cnt = LoadingTime;
}
/** 入り口処理 */
void GlassHeart::Mode::ModeLoading::Enter() {}
/**  入力処理 */
void GlassHeart::Mode::ModeLoading::Input(AppFrame::Input::InputManager& input) {}
/** 更新処理 */
void GlassHeart::Mode::ModeLoading::Process() {
  // ロードのためのカウンタを減少
  if (_cnt > 0) {
    --_cnt;
  }
  auto [handle, no] = GetGame().GetResourceServer().GetModles(Stage);
  if (_cnt == 0) {
    // 非同期読み込みが終了しているか
    // FALSEなら終了、それ以外なら読み込みを再開
    if (CheckHandleASyncLoad(handle) == FALSE) {
      // 非同期読み込み終了
      SetUseASyncLoadFlag(FALSE);
      // ゲーム本編へ移動
      GetModeServer().GoToMode(NextMode);
    }
    else {
      _cnt = LoadingCount;
    }
  }
}
/** 描画処理 */
void GlassHeart::Mode::ModeLoading::Render() {
  PlayMovieToGraph(_loadHandle);
  DrawGraph(RenderingPositionX, RenderingPositionY, _loadHandle, FALSE);
}

void GlassHeart::Mode::ModeLoading::Exit() {
  DeleteGraph(_loadHandle);
}