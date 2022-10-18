/*********************************************************************
 * @file   ModeFadeIn.cpp
 * @brief  フェードインクラスの処理
 *
 * @author Hayato Imai
 * @date    May 2022
 *********************************************************************/
#include "ModeFadeIn.h"
#include "ModeServer.h"
#include <DxLib.h>

namespace {
  constexpr float ALPHA_MIN = 0.f;        //!< アルファ値最低値
  constexpr float ALPHA_MAX = 255.f;     //!< アルファ値最大値
  constexpr float FADE_TIME = 75.555f;  //!< 暗転時間
  constexpr float ALPHA_DELTA = (ALPHA_MAX / FADE_TIME);  //!< アルファ値の差分
}

namespace AppFrame {
  namespace Mode {
    /** コンストラクタ */
    ModeFadeIn::ModeFadeIn(GameBase& game) : ModeFade{ game } {}
    /** デストラクタ */
    ModeFadeIn::~ModeFadeIn() {}
    /** 入り口処理 */
    void ModeFadeIn::Enter() {
      _alpha = ALPHA_MAX;
      _deltaAlpha = -ALPHA_DELTA;
    }
    /** 更新処理 */
    void ModeFadeIn::Process() {
      _alpha += _deltaAlpha;
      if (_alpha <= ALPHA_MIN) {
        _alpha = ALPHA_MIN;
        GetModeServer().PopBack(); // FadeIn自身をポップバック
      }
    }
  } // namespace Mode
} // namespace AppFrame 