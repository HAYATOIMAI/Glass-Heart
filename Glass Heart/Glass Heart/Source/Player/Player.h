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
 * @brief �v���W�F�N�g��
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
   * @brief �v���C���[�֌W
   */
  namespace Player {
    /**
     * @class Player
     * @brief �v���C���[�N���X�̐錾
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
       * @brief �R���X�g���N�^
       *
       * @param[in] game �Q�[�����C���N���X�ւ̎Q��
       */
      Player(Application::GameMain& game);
      /**
       * @brief �f�X�g���N�^
       *
       */
      virtual~Player() override = default;
      /**
       * @brief ���͏���
       *
       * @param[in] input  �C���v�b�g�}�l�[�W���[�N���X�̎Q��
       */
      virtual void Input(AppFrame::Input::InputManager& input) override;
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
       * @brief �I�u�W�F�N�g�^�C�v
       */
      ObjectType GetObjectType() const override { return ObjectType::Player; };
      /**
       * @brief ���[���h���W�ϊ�
       *
       */
      void ComputeWorldTransform() override;
      /**
       * @brief �ړ�����
       *
       * @param[in] forward �����x�N�g��
       */
      virtual void Move(const VECTOR& forward);
      /**
       * @brief �F���菈��
       *
       */
      void ColorChange();
      /**
       * @brief �v���C���[�̐F�𔒂ɕύX
       *
       */
      void SetWhite();
      /**
       * @brief �v���C���[�̐F�����ɕύX
       *
       */
      void SetBlack();
      /**
       * @brief 
       *
       */
      void ResetPos();
      /**
       * @ �v���C���[�̈ړ����x�̈ړ����x�̃Q�b�^�[
       * 
       * @return �v���C���[�̈ړ����x
       */
      inline float GetForwardSpeed() { return _forwardSpeed; }
      /**
       * @ �v���C���[�̈ړ����x�̃Z�b�^�[
       * 
       * @param[in] forwardSpeed �v���C���[�̈ړ����x�ɃZ�b�g����l
       */
      inline void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }
      /**
       * @ �f�o�b�O�p�X�e�[�g���ϐ��̃Q�b�^�[
       * 
       * @return �X�e�[�g��
       */
      inline std::string& GetCrName() { return _stateName; }
      /**
       * @ �F��Ԃ��擾����Q�b�^�[
       * 
       * @return �v���C���[�̐F
       */
      inline ColourState& GetColourState() { return _crState; }
      /**
       * @ �W�����v���x���擾����Q�b�^�[
       * 
       * @return �W�����v���x
       */
      inline VECTOR GetJumpVelocity() { return _jumpVelocity; }
      /**
       * @ �W�����v���x���Z�b�g����
       * 
       * @param[in] jump �Z�b�g����W�����v���x
       */
      inline void SetJumpVelocity(VECTOR jump) { _jumpVelocity = jump; }
      /**
       * @ �`�F�b�N�|�C���g��ʉ߂������̃t���O�̃Q�b�^�[
       * 
       * @return �ʉ߂������̃t���O
       */
      inline bool GetCheckPointFlag() { return _checkPointFlag; }
      /**
       * @ �`�F�b�N�|�C���g��ʉ߂������̃t���O�̃Z�b�^�[
       * 
       * @param[in] flag
       */
      inline void SetCheckPointFlag(bool flag) { _checkPointFlag = flag; }
    protected:
      bool _checkPointFlag{ false };               //!< �`�F�b�N�|�C���g�t���O
      ColourState _crState{ ColourState::White };  //!< �F��Ԃ��Ǘ�����ϐ�
      float _forwardSpeed{ 0.0f };                 //!< �ړ����x
      std::int_fast16_t _deathCoolCount{ 0 };      //!< ���S�������̕����܂ł̃N�[���^�C��
      std::int_fast8_t _recastCount{ 0 };          //!< �F�ύX�N�[���^�C���p�J�E���^
      std::string _stateName{ "White" };           //!< �f�o�b�O�p��Ԗ��ϐ�
      VECTOR _jumpVelocity{ 0.0f, 0.0f, 0.0f };    //!< �W�����v���x
    };
  } // namespace Player
} // namespace GlassHeart