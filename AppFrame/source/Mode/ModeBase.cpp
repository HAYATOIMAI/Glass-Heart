
/*****************************************************************//**
 * @file   ModeBase.cpp
 * @brief  モードの基底クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeBase.h"
#include "../Application/GameBase.h"

namespace AppFrame {

	ModeBase::ModeBase(GameBase& game) : _game{ game } {
	}

	ModeBase::~ModeBase() {
	}

	ResourceServer& ModeBase::GetResourceServer() {
		return _game.GetResourceServer();
	}

	SoundManager& ModeBase::GetSoundManager() {
		return _game.GetSoundManager();
	}

	ModeServer& ModeBase::GetModeServer() {
		return _game.GetModeServer();
	}
}

