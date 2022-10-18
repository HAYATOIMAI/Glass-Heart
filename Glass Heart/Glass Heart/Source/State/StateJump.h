/*****************************************************************//**
 * @file   StateJump.h
 * @brief  �v���C���[�̃W�����v��ԃN���X�̐錾
 *
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "StateBase.h"
#include <AppFrame.h>

 /**
  * @namespace GlassHeart
  * @brief �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Player {
    class Player;
  }
  /**
   * @namespace State
   * @brief  �v���C���[�̃X�e�[�g�֌W
   */
  namespace State {
    /**
     * @class StateJump
     * @brief �W�����v���
     */
    class StateJump : public StateBase {
    public:
      /**
      * @brief �R���X�g���N�^
      *
      * @param owner �v���C���[�N���X�ւ̎Q��
      */
      StateJump(Player::Player& owner);
      /**
       * @brief ���������
       *
       */
      void Enter() override;
      /**
       * @brief ���͏���
       *
       * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief �X�V����
       *
       */
      void Update() override;
    };
  } // namespace State
} // namespace GlassHeart