
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
	constexpr float ALPHA_MIN = 0.f;
	constexpr float ALPHA_MAX = 255.f;
	constexpr float FADE_TIME = 75.555f;
	constexpr float ALPHA_DELTA = (ALPHA_MAX / FADE_TIME);
}

namespace AppFrame {

	ModeFade::ModeFade(GameBase& game) : ModeBase{ game }
		, _color{ GetColor(0, 0, 0) }
	{
	}

	ModeFade::~ModeFade() {
	}

	void ModeFade::Init() {
		_color = GetColor(0, 0, 0);
	}

	void ModeFade::Enter() {

	}

	void ModeFade::Process() {
	}

	void ModeFade::Render() {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
		DrawBox(0, 0, _width, _height, _color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	ModeFadeIn::ModeFadeIn(GameBase& game) : ModeFade{ game }
	{
	}

	ModeFadeIn::~ModeFadeIn() {
	}

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

	ModeFadeOut::ModeFadeOut(GameBase& game) : ModeFade{ game }
	{
	}

	ModeFadeOut::~ModeFadeOut() {
	}

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

