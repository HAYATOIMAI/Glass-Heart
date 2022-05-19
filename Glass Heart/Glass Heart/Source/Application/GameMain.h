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
	std::string AppWindowName = "Glass Heart";
	constexpr auto AppWindowWidthSize = 1920;
	constexpr auto AppWindowHeightSize = 1080;
}
/**
 * @namespace GlassHeart
 * @brief �v���W�F�N�g��
 */
namespace GlassHeart {
	namespace Object {
		class ObjectServer;
		class ObjectFactory;
	}
	namespace Effect {
		class EffectServer;
	}
	namespace UI {
		class UI;
	} // namespace
	/**
	 * @namespace Application
	 * @brief �Q�[���{��
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
			 * @brief �R���X�g���N�^
			 *
			 */
			GameMain();
			/**
			 * @brief �f�X�g���N�^
			 *
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
			 * @brief ���͏���
			 */
			void Input() override;
			/**
			 * @brief �X�V����
			 */
			void Process() override;
			/**
			 * @brief �`�揈��
			 */
			void Render() override;
			/**
			 * @brief ���C�����[�v
			 */
			void Run() override;

			inline std::string SetWindowName() override { return AppWindowName; }

			inline int SetWindowWidthSize() override { return AppWindowWidthSize; }

			inline int SetWindowHeightSize() override { return AppWindowHeightSize; }

			inline Object::ObjectServer& GetObjectServer() const { return *_objServer; }

			inline Object::ObjectFactory& GetObjectFactory() const { return *_objFactory; }

			inline UI::UI& GetUI() const { return *_ui; }
		private:
			std::unique_ptr<Object::ObjectServer> _objServer;     //!< �I�u�W�F�N�g�T�[�o�[�̃��j�[�N�|�C���^
			std::unique_ptr<Object::ObjectFactory> _objFactory;	  //!< �I�u�W�F�N�g�t�@�N�g���[�̃��j�[�N�|�C���^
			std::unique_ptr<GlassHeart::UI::UI> _ui;                    //!< UI�̃��j�[�N�|�C���^
		};
	} // namespace Application
} // namespace GlassHeart