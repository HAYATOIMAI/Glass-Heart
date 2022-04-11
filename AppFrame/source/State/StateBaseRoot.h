/*********************************************************************
 * @file   StateBaseRoot.h
 * @brief  ��Ԃ̊��N���X�̐錾
 * 
 * @author Hayato Imai
 * @date   April 2022
 *********************************************************************/
#pragma once

#include "../Input/InputManager.h"

namespace AppFrame {
	/**
	 * @class StateBaseRoot
	 * @brief ��Ԃ̊��N���X
	 */
	class StateBaseRoot {
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		StateBaseRoot() {};
		/**
		 * @brief ���������
		 */
		virtual void Enter() {};
		/**
		 * @brief ���͏���
		 *
		 * @param[in] input  �C���v�b�g�}�l�[�W���[�N���X�̎Q��
		 */
		virtual void Input(InputManager& input) {};
		/**
		 * @brief�@�X�V����
		 *
		 */
		virtual void Update() {};
		/**
	     * @brief �`�揈��
	     *
	     */
		virtual void Draw() {};
	};
} // namespace AppFrame