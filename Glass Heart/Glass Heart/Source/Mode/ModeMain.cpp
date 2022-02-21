
/*****************************************************************//**
 * @file   ModeMain.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/

#include "ModeMain.h"
#include "../Application/GameMain.h"

using namespace GlassHeart;

Mode::ModeMain::ModeMain(GameMain& game) : AppFrame::ModeBase{ game }, _gameMain{game} {}

Object::ObjectFactory& Mode::ModeMain::GetObjectFactory() {
    return _gameMain.GetObjectFactory();
}

Object::ObjectServer& Mode::ModeMain::GetObjectServer() {
    return _gameMain.GetObjectServer();
}



