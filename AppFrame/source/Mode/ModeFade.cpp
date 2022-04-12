/*****************************************************************//**
 * @file   ModeFade.cpp
 * @brief  モードのフェードクラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeFade.h"
#include "ModeServer.h"
#include <DxLib.h>

namespace {
	constexpr float ALPHA_MIN = 0.f;                       //!< アルファ値最低値
	constexpr float ALPHA_MAX = 255.f;                     //!< アルファ値最大値
	constexpr float FADE_TIME = 75.555f;                   //!< 暗転時間
	constexpr float ALPHA_DELTA = (ALPHA_MAX / FADE_TIME); //!< アルファ値の差分
}

namespace AppFrame {
	/** コンストラクタ */
	ModeFade::ModeFade(GameBase& game) : ModeBase{ game }, _color{ GetColor(0, 0, 0) }{}
	/** デストラクタ */
	ModeFade::~ModeFade() {}

	void ModeFade::Init() {
		_color = GetColor(0, 0, 0);
	}

	void ModeFade::Enter() {}

	void ModeFade::Process() {}

	void ModeFade::Render() {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
		DrawBox(0, 0, _width, _height, _color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	/** コンストラクタ */
	ModeFadeIn::ModeFadeIn(GameBase& game) : ModeFade{ game }{}
	/** デストラクタ */
	ModeFadeIn::~ModeFadeIn() {}

	void ModeFadeIn::Enter() {
		_alpha = ALPHA_MAX;
		_deltaAlpha = -ALPHA_DELTA;
	}

	void ModeFadeIn::Process() {
		_alpha += _deltaAlpha;
		if (_alpha <= ALPHA_MIN) {
			_alpha = ALPHA_MIN;
			GetModeServer().PopBack(); // FadeIn自身をポップバック
		}
	}
	/** コンストラクタ */
	ModeFadeOut::ModeFadeOut(GameBase& game) : ModeFade{ game }{}
	/** デストラクタ */
	ModeFadeOut::~ModeFadeOut() {}

	void ModeFadeOut::Enter() {
		_alpha = ALPHA_MIN;
		_deltaAlpha = ALPHA_DELTA;
	}

	void ModeFadeOut::Process() {
		_alpha += _deltaAlpha;
		if (_alpha >= ALPHA_MAX) {
			_alpha = ALPHA_MAX;
			GetModeServer().PopBack(); // FadeOut自身をポップバック
			GetModeServer().PopBack(); // FadeOut下のシーンも一緒にポップバック
		}
	}
}

