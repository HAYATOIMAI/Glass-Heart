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
	constexpr float ALPHA_MIN = 0.f;        //!< アルファ値最低値
	constexpr float ALPHA_MAX = 255.f;     //!< アルファ値最大値
	constexpr float FADE_TIME = 75.555f;  //!< 暗転時間
	constexpr float ALPHA_DELTA = (ALPHA_MAX / FADE_TIME);  //!< アルファ値の差分
}

namespace AppFrame {
	namespace Mode {
		/** コンストラクタ */
		ModeFadeOut::ModeFadeOut(GameBase& game) : ModeFade{ game } {}
		/** デストラクタ */
		ModeFadeOut::~ModeFadeOut() {}
		/** 入り口処理 */
		void ModeFadeOut::Enter() {
			_alpha = ALPHA_MIN;
			_deltaAlpha = ALPHA_DELTA;
		}
		/** 更新処理 */
		void ModeFadeOut::Process() {
			_alpha += _deltaAlpha;
			if (_alpha >= ALPHA_MAX) {
				_alpha = ALPHA_MAX;
				GetModeServer().PopBack(); // FadeOut自身をポップバック
				GetModeServer().PopBack(); // FadeOut下のシーンも一緒にポップバック
			}
		}
	} // namespace Mode
} // namespace AppFrame 