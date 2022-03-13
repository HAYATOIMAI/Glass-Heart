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

namespace GlassHeart {

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
			UI(GameMain& game);
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
			 * @brief
			 */
			virtual void Input();
			/**
			 * @brief �X�V����
			 */
			virtual void Process(int counttime);
			/**
			 * @brief �`�揈��
			 * 
			 * @param x
			 * @param y
			 * @param interval �Ԋu
			 */
			virtual void Render(int x, int y, int interval);
			/**
			 * @brief ��̈ʂ̒l�𒊏o���鏈��
			 * 
			 * @param dismantvalue ��̈ʂ̒l�𒊏o���鏈��
			 * @return ��̈ʂ̒l
			 */
			int GetNumberPlace(int dismantvalue);

			int GetDigit(int value);

			GameMain& GetGame() { return _game; }
		private:
			GameMain& _game;
			int _numberhandle[3];
			int digit{ -1 };
			int _onehandle{ -1 };     //��̈ʂ̐����摜
			int _tenhandle{ -1 };  //�\�̈ʂ̐����摜
			int _hundhandle{ -1 }; //�S�̈ʂ̐����摜
			int _interval{ 100 };  //�������m�̊Ԋu
			int _second{ 0 };
		};
	}
}





