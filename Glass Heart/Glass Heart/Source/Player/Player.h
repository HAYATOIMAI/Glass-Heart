/*********************************************************************
 * @file   Player.h
 * @brief  �v���C���[�N���X�̐錾
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include <string>

namespace AppFrame {
  namespace Input {
    class InputManager;
  }
  namespace Sound {
    class SoundManager;
  }
}
/**
 * @namespace GlassHeart
 * @brief     �v���W�F�N�g��
 */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Camera {
    class CameraManager;
  }
  namespace Model {
    class ModelAnimeManager;
  }
  /**
   * @namespace Player 
   * @brief     �v���C���[�֌W
   */
  namespace Player {
    /**
     * @class Player
     * @brief �v���C���[�N���X
     */
    class Player : public Object::ObjectBase {
    public:
      /**
       * @brief �F���
       */
      enum class ColourState {
        White,
        Black,
      };
      /**
       * @brief                  �R���X�g���N�^
       *
       * @param[in] game         �Q�[�����C���N���X�ւ̎Q��
       */
      Player(Application::GameMain& game);
      /**
       * @brief                  �f�X�g���N�^
       */
      virtual~Player() override = default;
      /**
       * @brief                  ���͏���
       *                         
       * @param[in] input        �C���v�b�g�}�l�[�W���[�N���X�̎Q��
       */
      virtual void Input(AppFrame::Input::InputManager& input) override;
      /**
       * @brief                  �X�V����
       */
      virtual void Process() override;
      /**
       * @brief                  �`�揈��
       */
      void Render() override;
      /**
       * @brief                  �I�u�W�F�N�g�^�C�v
       */
      ObjectType GetObjectType() const override { return ObjectType::Player; };
      /**
       * @brief                  ���[���h���W�ϊ�
       */
      void ComputeWorldTransform() override;
      /**
       * @brief                  �ړ�����
       *                         
       * @param[in] forward      �����x�N�g��
       */
      virtual void Move(const VECTOR& forward);
      /**
       * @brief                  �F���菈��
       */
      void ColorChange();
      /**
       * @brief                  �v���C���[�̐F�𔒂ɕύX
       */
      void SetWhite();
      /**
       * @brief                  �v���C���[�̐F�����ɕύX
       */
      void SetBlack();
      /**
       * @brief                  �v���C���[�̈ʒu��������
       */
      void ResetPos();
      /**
       * @brief                  �v���C���[�̈ړ����x�̈ړ����x���擾
       *                         
       * @return                 �v���C���[�̈ړ����x
       */
      inline float GetForwardSpeed() const { return _forwardSpeed; }
      /**
       * @brief                  �v���C���[�̈ړ����x���Z�b�g����
       * 
       * @param[in] forwardSpeed �v���C���[�̈ړ����x�ɃZ�b�g����l
       */
      inline void SetForwardSpeed(const float forwardSpeed) { _forwardSpeed = forwardSpeed; }
      /**
       * @brief                  �f�o�b�O�p�X�e�[�g���ϐ����擾
       *                         
       * @return                 �X�e�[�g���̎Q��
       */
      inline std::string& GetCrName() { return _stateName; }
      /**
       * @brief                  �v���C���[�̐F��Ԃ��擾
       *                         
       * @return                 �v���C���[�̐F�̎Q��
       */
      inline ColourState& GetColourState() { return _colorState; }
      /**
       * @brief                  �W�����v���x���擾����
       *                         
       * @return                 �W�����v���x
       */
      inline VECTOR GetJumpVelocity() const { return _jumpVelocity; }
      /**
       * @brief                  �W�����v���x���Z�b�g����
       *                        
       * @param[in] jump         �Z�b�g����W�����v���x
       */
      inline void SetJumpVelocity(const VECTOR jump) { _jumpVelocity = jump; }
      /**
       * @brief                  �`�F�b�N�|�C���g��ʉ߂������̃t���O���擾
       *                         
       * @return                 �ʉ߂������̃t���O
       */
      inline bool GetCheckPointFlag() const { return _checkPointFlag; }
      /**
       * @brief                  �`�F�b�N�|�C���g��ʉ߂������̃t���O���擾
       *                        
       * @param[in] flag         �ʉ߂������̃t���O
       */
      inline void SetCheckPointFlag(const bool flag) { _checkPointFlag = flag; }
    protected:
      /**
       * @brief 
       * 
       */
      void CollisionDetectionByColor();
      /**
       * @brief 
       * 
       */
      void IsHitCheckPoint();
      bool _checkPointFlag{ false };                  //!< �`�F�b�N�|�C���g�t���O
      ColourState _colorState{ ColourState::White };  //!< �F��Ԃ��Ǘ�����ϐ�
      float _forwardSpeed{ 0.0f };                    //!< �ړ����x
      int_fast16_t _deathCoolCount{ 0 };              //!< ���S�������̕����܂ł̃N�[���^�C��
      int_fast16_t _recastCount{ 0 };                 //!< �F�ύX�N�[���^�C���p�J�E���^
      std::string _stateName{ "White" };              //!< �f�o�b�O�p��Ԗ��ϐ�
      VECTOR _jumpVelocity{ 0.0f, 0.0f, 0.0f };       //!< �W�����v���x
    };
  } // namespace Player
} // namespace GlassHeart