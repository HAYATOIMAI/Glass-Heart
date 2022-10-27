/*****************************************************************//**
 * @file   ModeBase.h
 * @brief ���[�h�̊��N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
/**
 * @namespace AppFrame
 * @brief  �A�v���P�[�V�����t���[��
 */
namespace AppFrame {
  class GameBase;
  namespace Input {
    class InputManager;
  }
  namespace Resource {
    class ResourceServer;
  }
  namespace Sound {
    class SoundManager;
  } // namespace
  /**
   * @namespace Mode 
   * @brief ���[�h�֌W
   */
  namespace Mode {
    class ModeServer;
    /**
     * @class ModeBase
     * @brief ���[�h�̊��N���X
     */
    class ModeBase {
    public:
      /**
       * @brief �R���X�g���N�^
       *
       * @param[in] game�@�Q�[���x�[�X�N���X
       */
      ModeBase(GameBase& game);
      /**
       * @brief �f�X�g���N�^
       *
       */
      virtual ~ModeBase();
      /**
       * @brief ����������
       *
       */
      virtual void Init() = 0;
      /**
       * @brief ���������
       */
      virtual void Enter() {};
      /**
       * @brief ���͏���
       *
       * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
       */
      virtual void Input(Input::InputManager& input) {};
      /**
       * @brief �X�V����
       */
      virtual void Process() {};
      /**
       * @brief �`�揈��
       */
      virtual void Render() {};
      /**
       * @brief �o������
       */
      virtual void Exit() {};
      /**
       * @brief �Q�[���x�[�X�N���X�̎Q��
       */
      inline GameBase& GetGame() const { return _game; };
      /**
       * @brief ���\�[�X�T�[�o�[�̎擾
       * 
       * @return ���\�[�X�T�[�o�[�̎Q��
       */
      Resource::ResourceServer& GetResourceServer();
      /**
       * @brief �T�E���h�}�l�[�W���[�̎擾
       * 
       * @return �T�E���h�}�l�[�W���[�̎Q��
       */
      Sound::SoundManager& GetSoundManager();
      /**
       * @brief ���[�h�T�[�o�[�̎擾
       * 
       * @return ���[�h�T�[�o�[�̎Q��
       */
      ModeServer& GetModeServer();
    protected:
      GameBase& _game;  //!< �Q�[���x�[�X�N���X�ւ̎Q��
    };
  } // namespace Mode
} // namespace AppFrame