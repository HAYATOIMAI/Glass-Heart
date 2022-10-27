/*********************************************************************
 * @file   StateBaseRoot.h
 * @brief  ��Ԃ̊��N���X�̐錾
 *
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#pragma once
#include "../Input/InputManager.h"
 /**
  * @namespace AppFrame
  * @brief  �A�v���P�[�V�����t���[��
  */
namespace AppFrame {
  /**
   * @namespace State
   * @brief �v���C���[�X�e�[�g�֌W
   */
  namespace State {
    /**
     * @class StateBaseRoot
     * @brief ��Ԃ̊��N���X
     */
    class StateBaseRoot {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      StateBaseRoot() {};
      /**
       * @brief ���������
       */
      virtual void Enter() {};
      /**
       * @brief ���͏���
       *
       * @param[in] input  �C���v�b�g�}�l�[�W���[�N���X�̎Q��
       */
      virtual void Input(Input::InputManager& input) {};
      /**
       * @brief�@�X�V����
       *
       */
      virtual void Update() {};
      /**
       * @brief �`�揈��
       *
       */
      virtual void Draw() {};
    };
  } // namespace State
} // namespace AppFrame