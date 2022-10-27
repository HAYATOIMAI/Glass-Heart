/*****************************************************************//**
 * @file   ModeGame.h
 * @brief  �Q�[�����N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeMain.h"
#include <AppFrame.h>
#include <memory>
#include <cstdint>
 /**
  * @namespace GlassHeart
  * @brief �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Camera {
    class CameraManager;
  }
  namespace Object {
    class ObjectFactory;
    class PlayerCreate;
    class GirlCreate;
    class StageCreate;
    class FollowCameraCreate;
    class CheckPointCreate;
    class GoalPointCreate;
  }
  namespace UI {
    class UI;
  } // namespace
  /**
   * @namespace Mode
   * @brief     ���[�h�֌W
   */
  namespace Mode {
    /**
     * @class ModeGame
     * @brief �Q�[�����N���X�̐錾
     */
    class ModeGame : public ModeMain {
    public:
      /**
       * @brief           �R���X�g���N�^
       *
       * @param[in] game  �Q�[�����C���N���X�ւ̎Q��
       */
      ModeGame(Application::GameMain& game);
      /**
       * @brief           �f�X�g���N�^
       */
      ~ModeGame() = default;
      /**
       * @brief           ����������
       */
      void Init() override;
      /**
       * @brief           ���������
       */
      void Enter() override;
      /**
       * @brief           ���͏��� 
       *
       * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
       */
      void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief           �X�V����
       */
      void Process() override;
      /**
       * @brief           �`�揈��
       */
      void Render() override;
      /**
       * @brief           �I������
       */
      void Exit() override;
    private:
      /**
       * @brief           �I�u���[�g�𐶐�
       */
      void ObjectRegister();
      /**
       * @brief           �^�C�}�[�o�ߏ���
       */
      void TimerProcess();
      /**
       * @brief           UI��`��
       */
      void UiRenderring();
      std::int_fast32_t _deathDrawHundle{ -1 };  //!< ���S���ɕ\������摜�p�n���h��
      std::int_fast32_t _teamLogo{ -1 };         //!< �`�[�����S�摜�p�n���h��
      std::int_fast32_t _titleLogo{ -1 };        //!< �^�C�g���摜�p�n���h��
    };
  } // namespace Mode
} // namespace GlassHeart