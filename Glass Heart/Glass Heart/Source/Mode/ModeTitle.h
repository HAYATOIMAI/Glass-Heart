/*****************************************************************//**
 * @file   ModeTitle.h
 * @brief  �^�C�g����ʃN���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeMain.h"
#include <AppFrame.h>
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
		 * @class ModeTitle
		 * @brief �^�C�g����ʃN���X�̐錾
		 */
		class ModeTitle : public ModeMain {
		public:
			/**
			 * @brief �R���X�g���N�^
			 *
			 * @param game�@�Q�[���x�[�X�N���X
			 */
			ModeTitle(Application::GameMain& game);
			/**
			 * @brief �f�X�g���N�^
			 *
			 */
			~ModeTitle() = default;
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
			std::int_fast16_t _alpha{ 0 };          //!< �A���t�@�l
			std::int_fast32_t _title{ -1 };         //!< �^�C�g���摜
			std::int_fast32_t _titleBg{ -1 };       //!< �^�C�g���w�i
			std::int_fast32_t _titleButton{ -1 };   //!< �^�C�g���{�^���摜
			std::int_fast32_t _titleExit{ -1 };     //!< Exit�{�^���摜
			std::int_fast32_t _titleLogo{ -1 };     //!< �^�C�g�����S
			std::int_fast32_t _titlePlate{ -1 };    //!< ��������摜
			std::int_fast32_t _titlePlate2{ -1 };   //!< ��������摜
			std::int_fast16_t _x{ 0 };              //!< ��������摜�ʒu
		};
	} // namespace Mode
} // namespace GlassHeart