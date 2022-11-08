/*****************************************************************//**
 * @file   ModeMain.h
 * @brief  ���[�h�̊��N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include <cstdint>
 /**
  * @namespace GlassHeart
  * @brief     �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Object {
    class ObjectServer;
    class ObjectFactory;
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
     * @class ModeMain
     * @brief ���[�h�̊��N���X�̐錾
     */
    class ModeMain : public AppFrame::Mode::ModeBase {
    public:
      /**
       * @brief           �R���X�g���N�^
       *
       * @param[in] game�@�Q�[�����C���N���X�̎Q��
       */
      ModeMain(Application::GameMain& game);
      /**
       * @brief           �f�X�g���N�^
       */
      ~ModeMain() = default;
      /**
       * @brief           ����������
       */
      virtual void Init() override {};
      /**
       * @brief           ���������
       */
      virtual void Enter() override {};
      /**
       * @brief           ���͏���
       *
       * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
       */
      virtual void Input(AppFrame::Input::InputManager& input) override {};
      /**
       * @brief           �X�V����
       */
      virtual void Process()override {};
      /**
       * @brief�@         �`�揈��
       */
      virtual void Render() override {};
      /**
       * @brief           �I������
       */
      virtual void Exit() override {};
      /**
       * @brief           �Q�[�����C���N���X���擾����
       * 
       * @return          �Q�[�����C���N���X�̎Q��
       */
      inline Application::GameMain& GetGameMain() const { return _gameMain; }
      /**
       * @brief           �I�u�W�F�N�g�t�@�N�g���[���擾����
       * 
       * @return          �I�u�W�F�N�g�t�@�N�g���[�̎Q��
       */
      Object::ObjectFactory& GetObjectFactory();
      /**
       * @brief           �I�u�W�F�N�g�T�[�o�[���擾����
       * 
       * @return          �I�u�W�F�N�g�T�[�o�[�̎Q��
       */
      Object::ObjectServer& GetObjectServer();
      /**
       * @brief           UI���擾����
       * 
       * @return          UI�̎Q��
       */
      UI::UI& GetUI();
    protected:
      Application::GameMain& _gameMain;   //!< �Q�[�����C���N���X�ւ̎Q��
      int_fast16_t _fadeCount;            //!< �����t�F�[�h�C���A�E�g�p�J�E���^
      static int_fast16_t _count;         //!< �^�C�}�[�p�t���[���J�E���g
      static int_fast16_t _countSeconds;  //!< �^�C�}�[�p�t���[���J�E���g
    };
  } // namespace Mode
} // namespace GlassHeart