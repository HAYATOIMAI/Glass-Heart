/*****************************************************************//**
 * @file   ModeClear.h
 * @brief  �Q�[���N���A�N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include "ModeMain.h"
#include <cstdint>
#include "../Object/ObjectBase.h"
 /**
  * @namespace GlassHeart
  * @brief �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  /**
   * @namespace Mode
   * @brief ���[�h�֌W
   */
  namespace Mode {
    /**
     * @class ModeClear
     * @brief �Q�[���N���A�N���X�̐錾
     */
    class ModeClear : public ModeMain {
    public:
      /**
       * @brief �R���X�g���N�^
       *
       * @param game�@�Q�[���x�[�X�N���X
       */
      ModeClear(Application::GameMain& game);
      /**
       * @brief �f�X�g���N�^
       *
       */
      ~ModeClear() = default;
      /**
       * @brief ����������
       *
       */
      void Init() override;
      /**
       * @brief ���������
       *
       */
      virtual void Enter() override;
      /**
       * @brief ���͏���
       *
       * @param input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief �X�V����
       *
       */
      void Process() override;
      /**
       * @brief �`�揈��
       *
       */
      void Render() override;
      /**
      * @brief �I������
      *
      */
      void Exit() override;

    private:
      std::int_fast32_t _gameClear{ -1 };  //!< �Q�[���N���A�摜
      std::int_fast32_t _gameOver{ -1 };   //!< �Q�[���I�[�o�[�摜
    };
  }// namespace Mode
} // namespace GlassHeart 