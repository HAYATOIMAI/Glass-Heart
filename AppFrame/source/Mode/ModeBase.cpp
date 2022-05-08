/*****************************************************************//**
 * @file   ModeBase.cpp
 * @brief ���[�h�̊��N���X�̏���
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeBase.h"
#include "../Application/GameBase.h"

namespace AppFrame {

	namespace Mode {
		/** �R���X�g���N�^ */
		ModeBase::ModeBase(GameBase& game) : _game{ game } {}
		/** �f�X�g���N�^ */
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