/*********************************************************************
 * @file   ModeFadeOut.h
 * @brief �t�F�[�h�A�E�g�N���X�̐錾
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#pragma once
#include "ModeFade.h"
 /**
  * @namespace AppFrame
  * @brief     �A�v���P�[�V�����t���[��
  */
namespace AppFrame {
  class GameBase;
  /**
   * @namespace Mode
   * @brief     ���[�h�֌W
   */
  namespace Mode {
    /**
     * @class ModeFadeOut
     * @brief �t�F�[�h�A�E�g�N���X�̐錾
     */
    class ModeFadeOut : public ModeFade {
    public:
      /**
       * @brief           �R���X�g���N�^
       *
       * @param[in] game�@�Q�[���x�[�X�N���X
       */
      ModeFadeOut(GameBase& game);
      /**
       * @brief           �f�X�g���N�^
       */
      virtual ~ModeFadeOut();
      /**
       * @brief           ���������
       */
      void Enter() override;
      /**
       * @brief           �X�V����
       */
      void Process() override;
    };
  } // namespace Mode
} // namespace AppFrame