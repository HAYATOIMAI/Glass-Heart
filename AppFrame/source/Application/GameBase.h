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
#include <cstdint>
#include <DxLib.h>
#ifdef _DEBUG
#include <Windows.h>
#include <stdexcept>
#endif // _DEBUG
namespace {
  std::string WindowName = "";                     //!< �E�B���h�E�̖��O
  constexpr std::int_fast16_t WindowWidth = 1920;  //!< �E�B���h�E�̏c��
  constexpr std::int_fast16_t WindowHeight = 1080; //!< �E�B���h�E�̉���
}
/**
 * @namespace AppFrame
 * @brief     �A�v���P�[�V�����t���[��
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
     * @enumclass GameState
     * @brief     �Q�[���̏��
     */
    enum class GameState {
      Active,  //!< �A�N�e�B�u
      Pause,   //!< ���f
      End      //!< �I��
    };
    /**
     * @brief  �R���X�g���N�^
     *
     */
    GameBase();
    /**
     * @brief  �f�X�g���N�^
     *
     */
    virtual ~GameBase();
    /**
     * @brief   ����������
     *
     * @return  �����������̉�
     */
    virtual bool Initialize(HINSTANCE hInstance);
    /**
     * @brief   �������
     *
     */
    virtual void Terminate();
    /**
     * @brief  �X�V����
     *
     */
    virtual void Process();
    /**
     * @brief  �`�揈��
     *
     */
    virtual void Render();
    /**
     * @brief  ���͏���
     *
     */
    virtual void Input();
    /**
     * @brief  ���C�����[�v
     *
     */
    virtual void Run();
    /**
     * @brief  �E�B���h�E�̖��O��ݒ肷��
     *         GameMain����override���A�Q�[�����ƂɓK�؂Ȗ��O�ɂ���
     * 
     * @return �E�B���h�E�̖��O
     */
    inline virtual std::string SetWindowName() { return WindowName; }
    /**
     * @brief  �E�B���h�E�̏c����ݒ肷��
     *         GameMain����override���A�Q�[�����ƂɓK�؂ȃT�C�Y�ɂ���
     * 
     * @return �E�B���h�E�̏c��
     */
    inline virtual std::int_fast16_t SetWindowWidthSize() { return WindowWidth; }
    /**
     * @brief  �E�B���h�E�̉�����ݒ肷��
     *         GameMain����override���A�Q�[�����ƂɓK�؂ȃT�C�Y�ɂ���
     * 
     * @return �E�B���h�E�̉��� 
     */
    inline virtual std::int_fast16_t SetWindowHeightSize() { return WindowHeight; }
    /**
     * @brief  ���[�h�T�[�o�[�̃|�C���^��Ԃ�
     * 
     * @return ���[�h�T�[�o�[�̃��j�[�N�|�C���^
     */
    inline Mode::ModeServer& GetModeServer() const { return *_modeServer; }
    /**
     * @brief  ���\�[�X�T�[�o�[�̎擾
     * 
     * @return ���\�[�X�T�[�o�[�̎Q��
     */
    inline Resource::ResourceServer& GetResourceServer()	const { return *_resServer; }
    /**
     * @brief  �T�E���h�}�l�[�W���[�̎擾
     * 
     * @return �T�E���h�}�l�[�W���[�̎Q��
     */
    inline Sound::SoundManager& GetSoundManager()	const { return *_soundManage; }
    /**
     * @brief  �Q�[���x�[�X�N���X�̃C���X�^���X���擾
     * 
     * @return �Q�[���x�[�X�N���X�̃C���X�^���X
     */
    inline static GameBase* GameInstance() { return _gameInstance; }
  protected:
    static GameBase* _gameInstance;                                   //!< �Q�[���x�[�X�N���X�̃C���X�^���X
    GameState _gameState{ GameState::Active };                        //!< �Q�[���̏��
    std::unique_ptr<Mode::ModeServer> _modeServer{ nullptr };         //!< ���[�h�T�[�o�[�̃��j�[�N�|�C���^
    std::unique_ptr<Resource::ResourceServer> _resServer{ nullptr };  //!< ���\�[�X�T�[�o�[�̃��j�[�N�|�C���^
    std::unique_ptr<Input::InputManager> _inputManage{ nullptr };     //!< �C���v�b�g�}�l�[�W���[�̃��j�[�N�|�C���^
    std::unique_ptr<Sound::SoundManager> _soundManage{ nullptr };     //!< �T�E���h�}�l�[�W���[�̃��j�[�N�|�C���^
  };
} // namespace AppFrame