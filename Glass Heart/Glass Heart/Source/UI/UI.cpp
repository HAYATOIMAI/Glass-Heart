/*****************************************************************//**
 * @file   UI.cpp
 * @brief  ユーザーインターフェースクラスの処理
 * 
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#include "UI.h"
#include "../Object/ObjectBase.h"
#include <AppFrame.h>

using namespace GlassHeart;

UI::UI::UI(GameMain& game) : _game(game){}

UI::UI::~UI() {}
//初期化
void UI::UI::Init() {}
//入口処理
void UI::UI::Enter() {
}
//入力処理
void UI::UI::Input() {}
//更新処理
void UI::UI::Process(int counttime) {
	int hundle = 0;
	digit = GetDigit(counttime);
	for (int i = 0; i < digit; i++) {
		int place = GetNumberPlace(counttime);
		counttime /= 10;
		switch (place) {
		case 0:
			hundle = _game.GetResourceServer().GetGraph("0");
			_numberhandle[i] = hundle;
			break;
		case 1:
			hundle = _game.GetResourceServer().GetGraph("1");
			_numberhandle[i] = hundle;
			break;
		case 2:
			hundle = _game.GetResourceServer().GetGraph("2");
			_numberhandle[i] = hundle;
			break;
		case 3:
			hundle = _game.GetResourceServer().GetGraph("3");
			_numberhandle[i] = hundle;
			break;
		case 4:
			hundle = _game.GetResourceServer().GetGraph("4");
			_numberhandle[i] = hundle;
			break;
		case 5:
			hundle = _game.GetResourceServer().GetGraph("5");
			_numberhandle[i] = hundle;
			break;
		case 6:
			hundle = _game.GetResourceServer().GetGraph("6");
			_numberhandle[i] = hundle;
			break;
		case 7:
			hundle = _game.GetResourceServer().GetGraph("7");
			_numberhandle[i] = hundle;
			break;
		case 8:
			hundle = _game.GetResourceServer().GetGraph("8");
			_numberhandle[i] = hundle;
			break;
		case 9:
			hundle = _game.GetResourceServer().GetGraph("9");
			_numberhandle[i] = hundle;
			break;
		}
	}
}
//描画処理
void UI::UI::Render(int x, int y, int interval) {
	int gx = x;
	int gy = y;
	for (int i = 0; i < digit; i++) {
		DrawRotaGraph(gx, gy, 1.0, 0.0, _numberhandle[i], TRUE);
		gx -= interval;
	}
}

int UI::UI::GetNumberPlace(int dismantvalue) {
	int placeone = dismantvalue % 10;
	return placeone;
}

int UI::UI::GetDigit(int value) {
	int getdigit = 0;
	while (value!=0) {
		value /= 10;
		getdigit++;
	}
	return getdigit;
}


