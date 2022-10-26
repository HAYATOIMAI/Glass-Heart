/*********************************************************************
 * @file   ModeFadeIn.h
 * @brief �t�F�[�h�C���N���X�̐錾
 *
 * @author Hayato Imai
 * @date   May 2022
 *********************************************************************/
#pragma once
#include "ModeFade.h"
 /**
  * @namespace AppFrame
  * @brief  �A�v���P�[�V�����t���[��
  */
namespace AppFrame {
  class GameBase;
  /**
   * @namespace Mode
   * @brief ���[�h�֌W
   */
  namespace Mode {
    /**
     * @class ModeFadeIn
     * @brief �t�F�[�h�C���N���X�̐錾
     */
    class ModeFadeIn : public ModeFade {
    public:
      /**
       * @brief           �R���X�g���N�^
       *
       * @param[in] game�@�Q�[���x�[�X�N���X
       */
      ModeFadeIn(GameBase& game);
      /**
       * @brief �f�X�g���N�^
       *
       */
      virtual ~ModeFadeIn();
      /**
      * @brief ���������
      */
      void Enter() override;
      /**
       * @brief �X�V����
       */
      void Process() override;
    };
  } // namespace Mode
} // namespace AppFrame