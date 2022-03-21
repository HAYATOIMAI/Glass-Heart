
/*****************************************************************//**
 * @file   CameraManager.h
 * @brief  �J�����}�l�[�W���[
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <utility>
#include <memory>
#include <DxLib.h>

namespace AppFrame {
    class InputManager;
}

namespace GlassHeart {

    namespace Camera {

        class CameraManager {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             */
            CameraManager();
            /**
             * @brief ����������
             * 
             */
            void Init();
            /**
             * @brief ���͏���
             * 
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            void Input(AppFrame::InputManager& input) {};
            /**
             * @brief �X�V����
             *
             */
            void Update();
            /**
             * @brief �`�揈��
             *
             */
            void Render();
             /**
              * @brief �J�������W(�n�_)�̐ݒ�
              * 
              * @param[in] position �J�����̈ʒu
              */
            inline void SetPosition(VECTOR position) { _position = position; }
            /// 
            /// @param[in] target
            /**
             * @brief �ڕW���W(�����_)�̐ݒ�
             * 
             * @param[in] target  �ڕW�̈ʒu
             * @param[in] forward �����x�N�g��
             */
            inline void SetTarget(VECTOR target, VECTOR forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }
            /**
             * @brief �����_�����̃x�N�g�����擾
             * 
             * @return �����_�����̒P�ʃx�N�g��
             */
            inline VECTOR GetForward() const { return VNorm(VSub(_target, _position)); }
        protected:
            VECTOR _position{ 0, 0, 0 };        //!< �J�����̈ʒu�x�N�g��
            VECTOR _target{ 0, 0, 0 };          //!< �ڕW�̈ʒu�x�N�g��
            VECTOR _forwardOfTarget{ 0, 0, 0 }; //!< �ڕW�̈ʒu�x�N�g��
            float targetDist{ 100.0f };         //!< �ڕW�Ƃ̋���
            float vertDist{ 100.0f };           //!< 
        };
    }
}