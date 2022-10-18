/*********************************************************************
 * @file   FollowCamera.h
 * @brief  �t�H���[�J�����N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date   February 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
 /**
  * @namespace GlassHeart
  * @brief �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Camera {
    class CameraManager;
  }
  /**
   * @namespace Camera
   * @brief �J�����֌W
   */
  namespace Camera {
    /**
     * @class FollowCamera
     * @brief �v���C���[��Ǐ]����J����
     */
    class FollowCamera : public Object::ObjectBase {
    public:
      /**
       * @brief �R���X�g���N�^
       *
       * @param game �Q�[�����C���N���X�ւ̎Q��
       */
      FollowCamera(Application::GameMain& game);
      /**
       * @brief �f�X�g���N�^
       *
       */
      virtual ~FollowCamera() override = default;
      /**
       * @brief �X�V����
       *
       */
      void Process() override;
      /**
       * @brief �`�揈��
       *
       */
      void Render() override;
      /**
       * @brief �^�C�v�̎擾
       * @return �^�C�vID
       */
      ObjectType GetObjectType() const override { return ObjectType::Camera; };
      /**
       * @brief �J�����̃X�s�[�h�ݒ�
       * @param[in] forwardSpeed �ړ����x
       * @return �ړ����x
       */
      void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }
    protected:
      float _angularSpeed{ 0 };  
      float _forwardSpeed{ 0 };  
      int _waitTime{ 0 };        
    };
  } // namespace Camera
} // namespace GlassHeart