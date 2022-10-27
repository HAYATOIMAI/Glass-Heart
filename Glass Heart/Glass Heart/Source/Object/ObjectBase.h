/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  �I�u�W�F�N�g�̊��N���X
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <memory>
#include <numbers>

namespace {
  constexpr VECTOR Position = { 0.0f, 0.0f, 0.0f };
  constexpr VECTOR Rotation = { 0.0f, 0.0f, 0.0f };
  constexpr VECTOR Scale = { 1.0f, 1.0f, 1.0f };

}
/**
 * @namespace AppFrame
 * @brief     �t���[�����[�N
 */
namespace AppFrame {
  namespace Resource {
    class ResourceServer;
  }
  namespace Input {
    class InputManager;
  } // namespace
}
/**
 * @namespace GlassHeart
 * @brief �v���W�F�N�g��
 */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Collision {
    class CollisionManager;
  }
  namespace Model {
    class ModelAnimeManager;
  }
  namespace Camera {
    class CameraManager;
  }
  namespace State {
    class StateManager;
  }
  namespace UI {
    class UI;
  } // namespace
  /**
   * @namespace Object
   * @brief     �I�u�W�F�N�g�֌W
   */
  namespace Object {
    class ObjectServer;
    class ObjectFactory;
    /**
     * @class ObjectBase
     * @brief �I�u�W�F�N�g�̊��N���X
     */
    class ObjectBase {
    public:
      /**
      * @brief�@�I�u�W�F�N�g�̎��
      */
      enum class ObjectType {
        Object = 0,
        Player,
        Girl,
        Camera,
        Stage,
        CheckPoint,
        GoalPoint
      };
      /**
       * @brief �I�u�W�F�N�g�̏��
       */
      enum class ObjectState {
        Active,              //!< ����
        Pause,               //!< ��~
        Dead                 //!< ���S
      };
      /**
       * @brief              �R���X�g���N�^
       *                     
       * @param[in] game     �Q�[�����C���N���X�ւ̎Q��
       */
      ObjectBase(Application::GameMain& game);
      /**
       * @brief              �f�X�g���N�^
       *
       */
      virtual ~ObjectBase();
      /**
       * @brief              ����������
       */
      virtual	void Init() {};
      /**
       * @brief              ���͏���
       *                     
       * @param[in] input    �C���v�b�g�}�l�[�W���[�N���X�̎Q��
       */
      virtual	void Input(AppFrame::Input::InputManager& input) {};
      /**
       * @brief              �X�V����
       */
      virtual	void Process() {};
      /**
       * @brief              �`�揈��
       */
      virtual	void Render() {};
      /**
       * @brief�@            �I�u�W�F�N�g�̎�ނ��擾
       *                     
       * @return             �I�u�W�F�N�g�̎��
       */
      virtual ObjectType GetObjectType() const = 0;
      /**
       * @brief              ���S��ԂɂȂ��Ă��邩
       *                     
       * @return             �I�u�W�F�N�g�̏��
       */
      inline bool IsDead() const { return (_objectState == ObjectState::Dead); }
      /**
       * @brief              ������ԂɂȂ��Ă��邩
       *                     
       * @return             �I�u�W�F�N�g�̏��
       */
      inline bool IsActive() const { return (_objectState == ObjectState::Active); }
      /**
       * @brief              ���[���h���W�ϊ�
       */
      virtual void ComputeWorldTransform();
      /**
       * @brief              �J�������猩�ĉE�����̌������擾
       *                     
       * @return             �E�����̌���
       */
      inline float RightRotation() const { return 90.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @brief              �J�������猩�č������̌������擾
       *                     
       * @return             �������̌���
       */
      inline float LeftRotation() const { return 270.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @brief              �Q�[�����C���N���X���擾����
       *                     
       * @return             �Q�[�����C���N���X�̎Q��
       */
      inline Application::GameMain& GetGame() const { return _game; }
      /**
       * @brief              ���[���h���W���擾����
       *                     
       * @return             �I�u�W�F�N�g�̃��[���h���W
       */
      inline const MATRIX& GetWorldTransform() const { return _worldTransform; }
      /**
       * @brief              �O���x�N�g�����擾����
       *                     
       * @return             �I�u�W�F�N�g�̑O���x�N�g��
       */
      inline VECTOR GetForward() const { return VTransform({ 0.0f, 0.0f, 1.0f }, MGetRotY(_rotation.y)); }
      /**
       * @brief              �I�u�W�F�N�g�̈ʒu���W���Z�b�g����
       *                     
       * @param[in] position �Z�b�g����ʒu���W
       */
      inline void SetPosition(const VECTOR& position) { _position = position; }
      /**
       * @brief              �I�u�W�F�N�g�̈ʒu���W�̂��擾����
       *                     
       * @return             �擾�����I�u�W�F�N�g�̈ʒu���W
       */
      inline VECTOR GetPosition() const { return _position; }
      /**
       * @brief              �I�u�W�F�N�g�̊p�x���Z�b�g����
       *                     
       * @param[in] rotation �Z�b�g����I�u�W�F�N�g�̊p�x
       */
      inline void SetRotation(const VECTOR& rotation) { _rotation = rotation; }
      /**
       * @brief              �I�u�W�F�N�g�̊p�x���擾����
       *                     
       * @return             �擾�����I�u�W�F�N�g�̊p�x
       */
      inline VECTOR GetRotation() const { return _rotation; }
      /**
       * @brief              �I�u�W�F�N�g�̊g�嗦���Z�b�g����
       *                      
       * @param[in] scale    �Z�b�g����I�u�W�F�N�g�̊g�嗦
       */
      inline void SetScale(const VECTOR& scale) { _scale = scale; }
      /**
       * @brief              �I�u�W�F�N�g�̊g�嗦���擾����
       *                     
       * @return             �擾�����I�u�W�F�N�g�̊g�嗦
       */
      inline VECTOR GetScale() const { return _scale; }
      /**
       * @brief              �~�Ɖ~�̓����蔻��p���a���Z�b�g����
       *                     
       * @param[in] radius   �Z�b�g���锼�a�̑傫��
       */                                               
      inline void SetRadius(const float radius) { _radius = radius; }
      /**
       * @brief              �~�Ɖ~�̓����蔻��p���a���擾����
       *                     
       * @return             �擾�������a��Ԃ�
       */
      inline float GetRadius() const { return _radius; }
      /**
       * @brief              ���S������Ƃ郁�b�V���ɓ����������̃t���O���Z�b�g����
       *                     
       * @param[in] hitFlag  �Z�b�g����t���O
       */
      inline void SetHitFlag(const bool hitFlag) { _hitFlag = hitFlag; }
      /**
       * @brief              ���S������Ƃ郁�b�V���ɓ����������̃t���O���擾����
       *                     
       * @return             �����������̃t���O��Ԃ�
       */
      inline bool GetHitFlag() const { return _hitFlag; }
      /**
       * @brief              ���S�����̂��̃t���O���擾����
       *                     
       * @return             ���S�����̂��̃t���O��Ԃ�
       */
      inline bool GetDeadFlag() const { return _deadFlag; }
      /**
       * @brief              �X�e�[�g�}�l�[�W���[���擾����
       *                     
       * @return             �X�e�[�g�}�l�[�W���[�̎Q��
       */
      inline State::StateManager& GetStateManage() const { return *_stateManage; }
      /**
       * @brief              �R���W�����}�l�[�W���[���擾����
       *                     
       * @return             �R���W�����}�l�[�W���[�̎Q��
       */
      inline Collision::CollisionManager& GetCollision() const { return *_collsionManage; }
      /**
       * @brief              �J�����}�l�[�W���[���擾����
       *                     
       * @return             �J�����}�l�[�W���[�̎Q��
       */
      inline Camera::CameraManager& GetCamera() const { return *_cameraManage; }
      /**
       * @brief              ���f���A�j���}�l�[�W���[���擾����
       *                     
       * @return             ���f���A�j���}�l�[�W���[�̎Q��
       */
      inline Model::ModelAnimeManager& GetModelAnime() const { return *_modelAnimeManage; }
      /**
       * @brief              �X�e�[�g�}�l�[�W���[���Z�b�g����
       *                     
       * @param[in] state    �X�e�[�g�}�l�[�W���[�̃��j�[�N�|�C���^
       */
      void SetStateManage(std::unique_ptr<State::StateManager> state);
      /**
       * @brief              ���f���A�j���}�l�[�W���[���Z�b�g����
       *                     
       * @param[in] model    ���f���A�j���}�l�[�W���[�̃��j�[�N�|�C���^
       */
      void SetModelManage(std::unique_ptr<Model::ModelAnimeManager> model);
      /**
       * @brief              �J�����}�l�[�W���[���Z�b�g����
       *                     
       * @param[in] camera   �J�����}�l�[�W���[�̃V�F�A�[�h�|�C���^
       */
      void SetCameraManage(std::shared_ptr<Camera::CameraManager> camera);
      /**
       * @brief              �I�u�W�F�N�g�Ǘ�����}�l�[�W���[���擾����
       *
       * @return             �I�u�W�F�N�g�T�[�o�[�̎Q��
       */
      ObjectServer& GetObjectServer();
    protected:
      /**
       * @brief              �I�u�W�F�N�g�̃X�e�[�g���擾����
       *                     
       * @return             �I�u�W�F�N�g�̃X�e�[�g
       */
      inline ObjectState GetObjectState() const { return _objectState; }
      /**
       * @brief              �I�u�W�F�N�g�̃X�e�[�g���Z�b�g����
       *                     
       * @param[in] objstate �I�u�W�F�N�g�̃X�e�[�g
       */
      inline void SetObjectState(const ObjectState objstate) { _objectState = objstate; }
      /** �X�e�[�g�}�l�[�W���[�̃��j�[�N�|�C���^ */
      std::unique_ptr<State::StateManager> _stateManage{ nullptr };
      /** �R���W�����}�l�[�W���[�̃V�F�A�[�h�|�C���^ */
      std::shared_ptr<Collision::CollisionManager> _collsionManage{ nullptr };
      /** �J�����}�l�[�W���[�̃V�F�A�[�h�|�C���^ */
      std::shared_ptr<Camera::CameraManager> _cameraManage{ nullptr };
      /** ���f���A�j���}�l�[�W���[�̃��j�[�N�|�C���^ */
      std::unique_ptr<Model::ModelAnimeManager> _modelAnimeManage{ nullptr };
      Application::GameMain& _game;                     //!< �Q�[�����C���N���X�̎Q��
      bool _deadFlag{ false };                          //!< ���S�������̃t���O
      bool _hitFlag{ false };                           //!< �R���W�����p�t���O
      float _radius{ 0.0f };                            //!< �R���W�����p���a
      MATRIX _worldTransform{ MGetIdent() };            //!< ���[���h���W�ϊ�
      VECTOR _position{ Position };                     //!< �ʒu���
      VECTOR _rotation{ Rotation };                     //!< �p�x
      VECTOR _scale{ Scale };                           //!< �g�嗦
      ObjectState _objectState{ ObjectState::Active };  //!< �I�u�W�F�N�g�̃X�e�[�g
    };
  } // namespace Object
} // namespace GlassHeart