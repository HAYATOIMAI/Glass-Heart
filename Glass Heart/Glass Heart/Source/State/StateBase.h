/*****************************************************************//**
 * @file   StateBase.h
 * @brief  �v���C���[�̏�Ԋ��N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "StateManager.h"
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
   * @brief     �v���C���[�̃X�e�[�g�֌W
   */
  namespace State {
    /**
     * @class StateBase
     * @brief �v���C���[�̏�Ԋ��N���X
     */
    class StateBase : public AppFrame::State::StateBaseRoot {
    public:
      /**
       * @brief           �R���X�g���N�^
       *
       * @param[in] owner �v���C���[�N���X�ւ̎Q��
       */
      StateBase(Player::Player& owner) : _owner{ owner } {};
      /**
       * @brief           �`�揈��
       */
      void Draw() override;
    protected:
      Player::Player& _owner;  //!< �v���C���[�N���X�̎Q��
    };
  } // namespace State
} // namespace GlassHeart