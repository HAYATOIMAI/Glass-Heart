/*****************************************************************//**
 * @file   ModeMain.cpp
 * @brief  モードの基底クラスの処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/

#include "ModeMain.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

Mode::ModeMain::ModeMain(Application::GameMain& game) : AppFrame::ModeBase{ game }, _gameMain{game} {
    _count = 0;
    _countSeconds = 0;
    _fadeCount = 0;
}

Object::ObjectFactory& Mode::ModeMain::GetObjectFactory() {
    return _gameMain.GetObjectFactory();
}

Object::ObjectServer& Mode::ModeMain::GetObjectServer() {
    return _gameMain.GetObjectServer();
}

UI::UI& Mode::ModeMain::GetUI() {
    return _gameMain.GetUI();
}

