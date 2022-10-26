/*********************************************************************
 * @file   ModeFadeIn.cpp
 * @brief  フェードインクラスの処理
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#include "ModeFadeIn.h"
#include "ModeServer.h"
#include "../Application/GameBase.h"
#include <DxLib.h>

namespace {
  constexpr auto AlphaMin = 0.f;                      //!< アルファ値最低値
  constexpr auto AlphaMax = 255.f;                    //!< アルファ値最大値
  constexpr auto FadeTime = 75.555f;                  //!< 暗転時間
  constexpr auto AlphaDelta = (AlphaMax / FadeTime);  //!< アルファ値の差分
}

namespace AppFrame {
  namespace Mode {
    /** コンストラクタ */
    ModeFadeIn::ModeFadeIn(GameBase& game) : ModeFade{ game } {}
    /** デストラクタ */
    ModeFadeIn::~ModeFadeIn() {}
    /** 入り口処理 */
    void ModeFadeIn::Enter() {
      _alpha = AlphaMax;
      _deltaAlpha = -AlphaDelta;
    }
    /** 更新処理 */
    void ModeFadeIn::Process() {
      _alpha += _deltaAlpha;
      if (_alpha <= AlphaMin) {
        _alpha = AlphaMin;
        GetModeServer().PopBack(); // FadeIn自身をポップバック
      }
    }
  } // namespace Mode
} // namespace AppFrame 