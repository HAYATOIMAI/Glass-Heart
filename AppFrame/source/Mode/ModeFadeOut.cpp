/*********************************************************************
 * @file   ModeFadeOut.cpp
 * @brief  フェードアウトクラスの処理
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#include "ModeFadeOut.h"
#include "ModeServer.h"
#include <DxLib.h>

namespace {
	constexpr float AlphaMin = 0.f;        //!< アルファ値最低値
	constexpr float AlphaMax = 255.f;      //!< アルファ値最大値
	constexpr float FadeTime = 75.555f;    //!< 暗転時間
	constexpr float AlphaDelta = (AlphaMax / FADE_TIME);  //!< アルファ値の差分
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