/*****************************************************************//**
 * @file   ModeLoading.h
 * @brief  ���[�f�B���O��ʃN���X�̐錾
 *
 * @author Hayato Imai
 * @date   March 2022
 *********************************************************************/
#pragma once
#include "ModeMain.h"
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
		 * @class ModeLoading
		 * @brief ���[�f�B���O��ʃN���X�̐錾
		 */
		class ModeLoading : public ModeMain {
		public:
			/**
			 * @brief �R���X�g���N�^
			 *
			 * @param[in] game
			 */
			ModeLoading(Application::GameMain& game);
			/**
			 * @brief �f�X�g���N�^
			 *
			 */
			~ModeLoading() = default;
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
			 * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�ւ̎Q��
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
		private:
			std::uint16_t _cnt{ 0 };              //!< ���[�f�B���O����
			std::int_fast32_t _loadHandle{ -1 };  //!< ���[�f�B���OGIF�摜�p�n���h��
		};
	} // namespace Mode
} // namespace GlassHeart