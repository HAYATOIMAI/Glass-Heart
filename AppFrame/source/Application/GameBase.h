/*****************************************************************//**
 * @file   GameBase.h
 * @brief  �A�v���P�[�V�����̊��N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
#include <DxLib.h>

namespace {
	std::string WindowName = "";
	constexpr auto WindowWidth = 1920;
	constexpr auto WindowHeight = 1080;
}
/**
 * @namespace AppFrame
 * @brief  �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
	namespace Resource {
		class ResourceServer;
	}
	namespace Input {
		class InputManager;
	}
	namespace Sound {
		class SoundManager;
	}
	namespace Mode {
		class ModeServer;
	}
	namespace Utility {
		class Utility;
	}
	/**
	 * @class GameBase
	 * @brief �A�v���P�[�V�����̊��N���X�̐錾
	 */
	class GameBase {
	public:
		/**
		 * @enumclass  GameState
		 * @brief �Q�[���̏��
		 */
		enum class GameState {
			Active,  //!< �A�N�e�B�u
			Pause,   //!< ���f
			End       //!< �I��
		};
		/**
		 * @brief �R���X�g���N�^
		 *
		 */
		GameBase();
		/**
		 * @brief �f�X�g���N�^
		 *
		 */
		virtual ~GameBase();
		/**
		 * @brief  ����������
		 *
		 * @return �����������̉�
		 */
		virtual bool Initialize(HINSTANCE hInstance);
		/**
		 * @brief  �������
		 *
		 */
		virtual void Terminate();
		/**
		 * @brief �X�V����
		 *
		 */
		virtual void Process();
		/**
		 * @brief �`�揈��
		 *
		 */
		virtual void Render();
		/**
		 * @brief ���͏���
		 *
		 */
		virtual void Input();
		/**
		 * @brief ���C�����[�v
		 *
		 */
		virtual void Run();

		inline virtual std::string SetWindowName() { return WindowName; }

		inline virtual int SetWindowWidthSize() { return WindowWidth; }

		inline virtual int SetWindowHeightSize() { return WindowHeight; }

		inline Mode::ModeServer& GetModeServer() const { return *_modeServer; }

		inline Resource::ResourceServer& GetResourceServer()	const { return *_resServer; }

		inline Sound::SoundManager& GetSoundManager()	const { return *_soundManage; }

		inline static GameBase* GameInstance() { return _gameInstance; }

	protected:
		static GameBase* _gameInstance;                                 //!< �Q�[���x�[�X�N���X�̃C���X�^���X
		GameState _gameState{ GameState::Active };                  //!< �Q�[���̏��
		std::unique_ptr<Mode::ModeServer> _modeServer;            //!< ���[�h�T�[�o�[�̃��j�[�N�|�C���^
		std::unique_ptr<Resource::ResourceServer> _resServer;  //!< ���\�[�X�T�[�o�[�̃��j�[�N�|�C���^
		std::unique_ptr<Input::InputManager> _inputManage;       //!< �C���v�b�g�}�l�[�W���[�̃��j�[�N�|�C���^
		std::unique_ptr<Sound::SoundManager> _soundManage;      //!< �T�E���h�}�l�[�W���[�̃��j�[�N�|�C���^
	};
} // namespace AppFrame