
/*****************************************************************//**
 * @file   ModeMain.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/

#include "ModeMain.h"
#include "../Application/GameMain.h"

using namespace GlassHeart::Mode;
using namespace GlassHeart::Object;


ModeMain::ModeMain(GameMain& game) : AppFrame::ModeBase{ game }, _gameMain{game} {

}

ObjectFactory& ModeMain::GetObjectFactory() {
	return _gameMain.GetObjectFactory();
}

ObjectServer& ModeMain::GetObjectServer() {
	return _gameMain.GetObjectServer();
}



