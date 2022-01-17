
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
            CameraManager();
            /// ������
            void Init();
            /// ���͏���
            void Input(AppFrame::InputManager& input);
            /// �X�V����
            void Update();
            /// �`�揈��
            void Render();
            /// �J�������W(�n�_)�̐ݒ�
             /// @param[in] position
            void SetPosition(VECTOR position) { _position = position; }
            /// �ڕW���W(�����_)�̐ݒ�
            /// @param[in] target
            void SetTarget(VECTOR target, VECTOR forward = { 0,0,0 }) { _target = target; _forwardOfTarget = forward; }
            /// �����_�����̃x�N�g�����擾
            /// @return �����_�����̒P�ʃx�N�g��
            VECTOR GetForward() const { return VNorm(VSub(_target, _position)); }
        protected:
            VECTOR _position{ 0, 0, 0 };
            VECTOR _target{ 0, 0, 0 };
            VECTOR _forwardOfTarget{ 0, 0, 0 };
            float targetDist{ 100.0f };
            float vertDist{ 100.0f };
        };
    }
}