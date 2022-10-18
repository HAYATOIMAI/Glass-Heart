/*****************************************************************//**
 * @file   ModeTeamLogo.h
 * @brief  �`�[�����S��ʃN���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModeMain.h"
#include <cstdint>
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
		 * @class ModeTeamLogo
		 * @brief �`�[�����S��ʃN���X
		 */
		class ModeTeamLogo : public ModeMain {
		public:
			/**
			 * @brief �R���X�g���N�^
			 *
			 * @param game�@�Q�[���x�[�X�N���X
			 */
			ModeTeamLogo(Application::GameMain& game);
			/**
			 * @brief �f�X�g���N�^
			 *
			 */
			~ModeTeamLogo() = default;
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
			std::int_fast32_t _teamLogo{ -1 };  //!< �w�i�摜�p�n���h��
		};
	} // namespace Mode
} // namespace GlassHeart