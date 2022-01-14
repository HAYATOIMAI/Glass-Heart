
/*****************************************************************//**
 * @file   Player.h
 * @brief  �v���C���[�N���X�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Object/ObjectBase.h"
#include <AppFrame.h>

namespace AppFrame {
    class InputManager;
}

namespace GlassHeart {

    class GameMain;

    namespace Camera {
        class CameraManager;
    }
    namespace Model {
        class ModelAnimeManager;
    }
    
    namespace Player {
        /**
         * @class Player
         * @brief �v���C���[
         */
        class Player : public  Object::ObjectBase {
        public:
            /**
             * @brief �R���X�g���N�^
             * 
             * @param game �Q�[�����C���N���X�ւ̎Q��
             */
            Player(GameMain& game);
            /**
             * @brief �f�X�g���N�^
             * 
             */
            virtual~Player() = default;
            /**
             * @brief ���͏���
             * 
             * @param[in] input  �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            virtual void Input(AppFrame::InputManager& input) override;
            /**
             * @brief �X�V����
             * 
             */
            virtual void Process() override;
            /**
             * @brief �`�揈��
             * 
             */
            void Render() override;
            /**
             * @brief 
             */
            ObjectType GetObjectType() const  override { return ObjectType::Player; };
            /**
             * @brief ���[���h���W�ϊ�
             * 
             */
            void ComputeWorldTransform() override;

            float GetForwardSpeed() { return _forwardSpeed; }
            void SetForwardSpeed(float forwardspeed) { _forwardSpeed = forwardspeed; }
            /**
             * @brief �ړ�����
             *
             * @param[in] forward
             */
            virtual void Move(const VECTOR& forward);
            void JumpFunction(const bool isJumpStart);
            void JumpStart();
            VECTOR JumpProcess();
            bool  JumpEnd(const VECTOR& jumppos);
        protected:
            float _forwardSpeed{ 0.0f };  //!< �O�i�X�s�[�h
            float _angularSpeed{ 0.0f };  //!< 
            VECTOR _backDelta{ 0, 0, 0 };  //!<
            double _gravity{ 9.8 };  //!< �d�͉����x
            double _jumpTimer{ 0.0 };
            double _groundY{ 0.0 };
            double _jumpPower{ 100.0 };
            double _jumpAngle{ 87.5 };
            bool _isJump{ false };
            VECTOR _jumpStartPosition;
            VECTOR _jumpVelocity;
            VECTOR _lastPosition;
            /**
             * @brief �G�Ƃ̐ڐG����
             * @details �g�p�\�薳��
             */
            void HitCheckEnemy();
        };
    }
}