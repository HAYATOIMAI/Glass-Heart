
/*********************************************************************
 * @file   Player.h
 * @brief  �v���C���[�N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Object/ObjectBase.h"
#include <string>
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
             * @brief �F���
             */
            enum class ColourState {
                White,
                Black,
            };
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
            /**
             * @brief �ړ�����
             *
             * @param[in] forward
             */
            virtual void Move(const VECTOR& forward);
            /**
             * @brief �F���菈��
             * 
             */
            void ColorCollisionDetectionSystem();
            /**
             * @brief ���X�|�[���V�X�e��
             * 
             */
            void ResetPos();

            void ReturnCheckPoint();

            float GetForwardSpeed() { return _forwardSpeed; }
            void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }

            std::string& GetCrName() { return _stateName; }

            VECTOR GetLastPosition() { return _lastPosition; }

            VECTOR GetHighestPosition() { return _highestPosition; }

            ColourState& GetColourState() { return _crState; }
        protected:

            ColourState _crState{ ColourState::White }; //!< �F��Ԃ��Ǘ�����ϐ�
            float _forwardSpeed{ 0.0f };  //!< �O�i�X�s�[�h
            float _angularSpeed{ 0.0f };  //!< 
            VECTOR _lastPosition{ 0.0f, 0.0f, 0.0f };
            VECTOR _highestPosition{ 0.0f, 0.0f, 0.0f };
            std::string _stateName{ "White" }; //!< ��Ԗ��ϐ�
            int _colourCount{ 0 };  //!< �F�ύX�N�[���^�C���p�J�E���^�[
            bool _checkPointFlag{ false };
        };
    }
}