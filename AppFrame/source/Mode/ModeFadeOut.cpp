/*********************************************************************
 * @file   ModeFadeOut.cpp
 * @brief  フェードアウトクラスの処理
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#include "ModeFadeOut.h"
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
    ModeFadeOut::ModeFadeOut(GameBase& game) : ModeFade{ game } {}
    /** デストラクタ */
    ModeFadeOut::~ModeFadeOut() {}
    /** 入り口処理 */
    void ModeFadeOut::Enter() {
      _alpha = AlphaMin;
      _deltaAlpha = AlphaDelta;
    }
    /** 更新処理 */
    void ModeFadeOut::Process() {
      _alpha += _deltaAlpha;
      if (_alpha >= AlphaMax) {
        _alpha = AlphaMax;
        GetModeServer().PopBack(); // FadeOut自身をポップバック
        GetModeServer().PopBack(); // FadeOut下のシーンも一緒にポップバック
      }
    }
  } // namespace Mode
} // namespace AppFrame 