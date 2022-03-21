
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
    class SoundManager;
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
             * @brief �I�u���[�g�^�C�v
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
            void SetWhite();
            void SetBlack();
            /**
             * @brief ���X�|�[���V�X�e��
             * 
             */
            void ResetPos();

            inline float GetForwardSpeed() { return _forwardSpeed; }
            inline void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }
            
            inline std::string& GetCrName() { return _stateName; }
            
            inline ColourState& GetColourState() { return _crState; }
            
            inline VECTOR GetJumpVelocity() { return _jumpVelocity; }
            inline void SetJumpVelocity(VECTOR jump) { _jumpVelocity = jump; }

            inline bool GetCheckPointFlag() { return _checkPointFlag; }
            inline void SetCheckPointFlag(bool flag) { _checkPointFlag = flag; }
        protected:
            ColourState _crState{ ColourState::White }; //!< �F��Ԃ��Ǘ�����ϐ�
            float _forwardSpeed{ 0.0f };                //!< �O�i�X�s�[�h
            std::string _stateName{ "White" };          //!< �f�o�b�O�p��Ԗ��ϐ�
            int _recastCount{ 0 };                      //!< �F�ύX�N�[���^�C���p�J�E���^�[
            int _deathCoolCount{ 0 };                   //!<���S�������̕����N�[���^�C��
            bool _checkPointFlag{ false };              //!< �`�F�b�N�|�C���g�t���O
            VECTOR _jumpVelocity{ 0.f, 0.f, 0.f };      //!< �W�����v���x
        };
    } // Player
} // GlassHeart 