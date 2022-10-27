/*****************************************************************//**
 * @file   GameMain.h
 * @brief  ���̃v���W�F�N�g�̃��C������
 *
 * @author Hayato Imai, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <AppFrame.h>
#include <memory>

namespace {
  std::string AppWindowName = "Glass Heart";               //!< �A�v���P�[�V�����̖��O
  constexpr std::int_fast16_t AppWindowWidthSize = 1920;   //!< ��ʂ̏c��
  constexpr std::int_fast16_t AppWindowHeightSize = 1080;  //!< ��ʂ̉���
}
/**
 * @namespace GlassHeart
 * @brief     �v���W�F�N�g��
 */
namespace GlassHeart {
  namespace Object {
    class ObjectServer;
    class ObjectFactory;
  }
  namespace UI {
    class UI;
  } // namespace
  /**
   * @namespace Application
   * @brief     �Q�[���{��
   */
  namespace Application {
    /**
     * @class GameMain
     * @brief ���̃v���W�F�N�g�̃��C������
     */
    class GameMain : public AppFrame::GameBase {
      using base = AppFrame::GameBase;
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      GameMain();
      /**
       * @brief  �f�X�g���N�^
       */
      ~GameMain() override;
      /**
       * @brief  ����������
       *
       * @return �����������̉�
       */
      bool Initialize(HINSTANCE hInstance) override;
      /**
       *  @brief �������
       */
      void Terminate() override;
      /**
       * @brief  ���͏���
       */
      void Input() override;
      /**
       * @brief  �X�V����
       */
      void Process() override;
      /**
       * @brief  �`�揈��
       */
      void Render() override;
      /**
       * @brief  ���C�����[�v
       */
      void Run() override;
      /**
       * @brief  �A�v���P�[�V�����̖��O��ݒ肷��
       * 
       * @return �A�v���P�[�V�����̖��O��Ԃ�
       */
      inline std::string SetWindowName() override { return AppWindowName; }
      /**
       * @brief  ��ʂ̏c����ݒ肷��
       * 
       * @return ��ʂ̏c����Ԃ�
       */
      inline std::int_fast16_t SetWindowWidthSize() override { return AppWindowWidthSize; }
      /**
       * @brief  ��ʂ̉�����ݒ肷��
       * 
       * @return ��ʂ̉�����Ԃ�
       */
      inline std::int_fast16_t SetWindowHeightSize() override { return AppWindowHeightSize; }
      /**
       * @brief  �I�u�W�F�N�g�T�[�o�[�̎擾
       * 
       * @return �I�u�W�F�N�g�T�[�o�[�̎Q��
       */
      inline Object::ObjectServer& GetObjectServer() const { return *_objServer; }
      /**
       * @brief  �I�u�W�F�N�g�t�@�N�g���[�̎擾
       * 
       * @return �I�u�W�F�N�g�t�@�N�g���[�̎Q��
       */
      inline Object::ObjectFactory& GetObjectFactory() const { return *_objFactory; }
      /**
       * @brief  UI�̎擾
       * 
       * @return UI�̎Q��
       */
      inline UI::UI& GetUI() const { return *_ui; }
    private:
      std::unique_ptr<Object::ObjectServer> _objServer{ nullptr };    //!< �I�u�W�F�N�g�T�[�o�[�̃��j�[�N�|�C���^
      std::unique_ptr<Object::ObjectFactory> _objFactory{ nullptr };  //!< �I�u�W�F�N�g�t�@�N�g���[�̃��j�[�N�|�C���^
      std::unique_ptr<UI::UI> _ui{ nullptr };                         //!< UI�̃��j�[�N�|�C���^
    };
  } // namespace Application
} // namespace GlassHeart