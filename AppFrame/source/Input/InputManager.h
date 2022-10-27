/*****************************************************************//**
 * @file   InputManager.h
 * @brief  �C���v�b�g�}�l�[�W���[�N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "InputJoypad.h"
#include <DxLib.h>
#include <utility>
 /**
  * @namespace AppFrame
  * @brief     �A�v���P�[�V�����t���[��
  */
namespace AppFrame {
  /**
   * @namespace Input
   * @brief     ���͏����֌W
   */
  namespace Input {
    /**
     * @class InputManager
     * @brief �C���v�b�g�}�l�[�W���[�N���X�̐錾
     */
    class InputManager {
    public:
      /**
       * @brief �X�V����
       */
      void Process();
      /**
       * @brief Xinput���͂��擾
       * 
       * @return  Xinput���͂̎Q��
       */
      inline InputJoypad& GetJoyPad() { return _inputjoy; }
    private:
      InputJoypad _inputjoy;  //!< �C���v�b�g�W���C�p�b�h�N���X�̎Q��
    };
  }
} // namespace AppFrame