/*****************************************************************//**
 * @file   ModeAmg.h
 * @brief  AMG��ʃN���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include "ModeMain.h"
 /**
  * @namespace GlassHeart
  * @brief     �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  /**
   * @namespace Mode
   * @brief     ���[�h�֌W
   */
  namespace Mode {
    /**
     * @class ModeAmg
     * @brief AMG��ʃN���X�̐錾
     */
    class ModeAmg : public ModeMain {
    public:
      /**
       * @brief           �R���X�g���N�^
       *                  
       * @param game�@    �Q�[���x�[�X�N���X
       */
      ModeAmg(Application::GameMain& game);
      /**
       * @brief           �f�X�g���N�^
       *
       */
      ~ModeAmg() = default;
      /**
       * @brief           ����������
       *
       */
      void Init() override;
      /**
       * @brief           ���������
       *
       */
      virtual void Enter() override;
      /**
       * @brief           ���͏���
       *
       * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief           �X�V����
       *
       */
      void Process() override;
      /**
       * @brief           �`�揈��
       *
       */
      void Render() override;
    private:
      std::int_fast32_t _amgLogoHandle{ -1 };  //!< AMG���S�摜
    };
  } // namespace Mode
} // namespace GlassHeart