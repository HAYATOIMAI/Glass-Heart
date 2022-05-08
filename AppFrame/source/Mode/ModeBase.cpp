/*****************************************************************//**
 * @file   ModeBase.cpp
 * @brief モードの基底クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeBase.h"
#include "../Application/GameBase.h"

namespace AppFrame {

	namespace Mode {
		/** コンストラクタ */
		ModeBase::ModeBase(GameBase& game) : _game{ game } {}
		/** デストラクタ */
		ModeBase::~ModeBase() {}

		Resource::ResourceServer& ModeBase::GetResourceServer() {
			return _game.GetResourceServer();
		}

		Sound::SoundManager& ModeBase::GetSoundManager() {
			return _game.GetSoundManager();
		}

		ModeServer& ModeBase::GetModeServer() {
			return _game.GetModeServer();
		}
	} // namespace Mode
} // namespace AppFrame 