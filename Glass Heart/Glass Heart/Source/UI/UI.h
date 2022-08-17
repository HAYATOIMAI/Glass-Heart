/*****************************************************************//**
 * @file   UI.h
 * @brief  ���[�U�[�C���^�[�t�F�[�X�N���X�̐錾
 *
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "../Application/GameMain.h"
#include <unordered_map>
#include <vector>
 /**
	* @namespace GlassHeart
	* @brief �v���W�F�N�g��
	*/
namespace GlassHeart {
	/**
	 * @namespace UI
	 * @brief UI�֌W
	 */
	namespace UI {
		/**
		 * @class UI
		 * @brief ���[�U�[�C���^�[�t�F�[�X
		 */
		class UI {
		public:
			/**
			 * @brief �R���X�g���N�^
			 *
			 */
			UI(Application::GameMain& game);
			/**
			 * @brief �f�X�g���N�^
			 *
			 */
			~UI();
			/**
			 * @brief ����������
			 *
			 */
			virtual void Init();
			/**
			 * @brief ��������
			 *
			 */
			virtual void Enter();
			/**
			 * @brief ���͏���
			 */
			virtual void Input();
			/**
			 * @brief �X�V����
			 */
			virtual void Process(int counttime);
			/**
			 * @brief �`�揈��
			 *
			 * @param x X���W�`��ʒu
			 * @param y Y���W�`��ʒu
			 * @param interval �Ԋu
			 */
			virtual void Render(int x, int y, double exrate);
			/**
			 * @brief �c�莞�ԗp�`�揈��
			 *
			 * @param x X���W�`��ʒu
			 * @param y Y���W�`��ʒu
			 * @param interval �Ԋu
			 * @param exrate   �g�嗦
			 */
			void NumberRender(int x, int y, int interval, double exrate);
			/**
			 * @brief ��̈ʂ̒l�𒊏o���鏈��
			 *
			 * @param dismantvalue ��̈ʂ̒l�𒊏o���鏈��
			 * @return ��̈ʂ̒l
			 */
			int GetNumberPlace(int dismantvalue);
			/**
			 * @brief �����̎擾
			 *
			 * @param value �������擾����l
			 * @return  ����
			 */
			int GetDigit(int value);

			inline Application::GameMain& GetGame() { return _game; }
		private:
			Application::GameMain& _game;  //!< �v���W�F�N�g
			int _interval{ 100 };             //!< �������m�̊Ԋu
			int _numberhandle[3]{ 0,0,0 };  //!< �����̉摜�n���h��
			int _second{ 0 };                   //!< �c��b��
			int _timerhandle{ 0 };            //!< �^�C�}�[�̉摜�n���h��
			int digit{ -1 };                     //!< ��
		};
	} // namespace UI
} // namespace GlassHeart