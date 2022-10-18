/*****************************************************************//**
 * @file   SoundManager.h
 * @brief  �T�E���h�}�l�[�W���[�N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <string>
 /**
  * @namespace AppFrame
  * @brief  �A�v���P�[�V�����t���[��
  */
namespace AppFrame {
  class GameBase;
  /**
   * @namespace Sound 
   * @brief �T�E���h�֌W
   */
  namespace Sound {
    /**
     * @class SoundManager
     * @brief �T�E���h�}�l�[�W���[�N���X�̐錾
     */
    class SoundManager {
    public:
      /**
       * @brief �R���X�g���N�^
       *
       * @param[in] game �Q�[���x�[�X�N���X�ւ̎Q��
       */
      SoundManager(GameBase& game) : _game{ game } {};
      /**
       * @brief �f�X�g���N�^
       *
       */
      virtual ~SoundManager();
      /**
       * @brief �Đ�(���[�v����)
       *
       * @param[in] key �o�^�ς݂̕�����
       */
      void Play(std::string_view key);
      /**
       * @brief ���[�v�Đ�
       *
       * @param[in] key �o�^�ς݂̕�����
       */
      void PlayLoop(std::string_view key);
      /**
       * @brief ���ʂ�ݒ�
       *
       * @param[in] key �o�^�ς݂̕�����
       * @param volume  ����
       */
      void SetVolume(std::string_view key, int volume);
      /**
       * @brief�@��~
       *
       * @param[in] key �o�^�ς݂̕�����
       */
      void StopSound(std::string_view key);

      inline void SetMute(bool isMute) { _isMute = isMute; }
    private:
      /**
       * @brief�@�Đ�
       *
       * @param[in] key       �o�^�ς݂̕�����
       * @param[in] playType  �Đ��̎��
       */
      void Play(std::string_view key, int playType);

      GameBase& _game;        //!< �Q�[���x�[�X�N���X�ւ̎Q��
      bool _isMute{ false };  //!< �~���[�g�ɂ��邩�̃t���O
    };
  } // namespace Sound
} // namespace AppFrame