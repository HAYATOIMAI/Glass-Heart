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

namespace AppFrame {
  namespace Resource {
    class ResourceServer;
  }
  namespace Input {
    class InputManager;
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
   * @brief�I�u�W�F�N�g�֌W
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
        Active,
        Pause,
        Dead
      };
      /**
       * @brief �R���X�g���N�^
       *
       * @param[in] game �Q�[�����C���N���X�ւ̎Q��
       */
      ObjectBase(Application::GameMain& game);
      /**
       * @brief �f�X�g���N�^
       *
       */
      virtual ~ObjectBase();
      /**
       * @brief ����������
       */
      virtual	void Init() {};
      /**
       * @brief ���͏���
       *
       * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
       */
      virtual	void Input(AppFrame::Input::InputManager& input) {};
      /**
       * @brief �X�V����
       */
      virtual	void Process() {};
      /**
       * @brief �`�揈��
       */
      virtual	void Render() {};
      /**
       * @brief�@�I�u�W�F�N�g�̎�ނ��擾
       *
       * @return �I�u�W�F�N�g�̎��
       */
      virtual ObjectType GetObjectType() const = 0;
      /**
       * @brief ���S��ԂɂȂ��Ă��邩
       *
       * @return �I�u�W�F�N�g�̏��
       */
      inline bool IsDead() { return (_objectState == ObjectState::Dead); }
      /**
       * @brief ������ԂɂȂ��Ă��邩
       *
       * @return  �I�u�W�F�N�g�̏��
       */
      inline bool IsActive() { return (_objectState == ObjectState::Active); }
      /**
       * @brief ���[���h���W�ϊ�
       */
      virtual void ComputeWorldTransform();
      /**
      * @ �J�������猩�ĉE�����̌������擾
      *
      * @return �E�����̌���
      */
      float RightRotation() const { return 90.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @ �J�������猩�č������̌������擾
       *
       * @return �������̌���
       */
      float LeftRotation() const { return 270.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @ �Q�[�����C���N���X�̎Q�Ƃ̃Q�b�^�[
       * 
       * @return �Q�[�����C���N���X�̎Q��
       */
      inline Application::GameMain& GetGame() { return _game; }
      /**
       * @ ���[���h���W�̃Q�b�^�[
       * 
       * @return 
       */
      inline const MATRIX& GetWorldTransform() const { return _worldTransform; }
      /**
       * @ �O���x�N�g�����擾����Q�b�^�[
       * 
       * @return �I�u�W�F�N�g�̑O���x�N�g��
       */
      inline VECTOR GetForward() const { return VTransform({ 0.0f, 0.0f, 1.0f }, MGetRotY(_rotation.y)); }
      /**
       * @ �I�u�W�F�N�g�̈ʒu���W���Z�b�g����
       * 
       * @param[in] position �Z�b�g����ʒu���W
       */
      inline void SetPosition(const VECTOR& position) { _position = position; }
      /**
       * @ �I�u�W�F�N�g�̈ʒu���W�̃Q�b�^�[
       * 
       * @return �擾�����I�u�W�F�N�g�̈ʒu���W
       */
      inline VECTOR GetPosition() const { return _position; }
      /**
       * @ �I�u�W�F�N�g�̊p�x���Z�b�g����
       * 
       * @param[in] rotation �Z�b�g����I�u�W�F�N�g�̊p�x
       */
      inline void SetRotation(const VECTOR& rotation) { _rotation = rotation; }
      /**
       * @ �I�u�W�F�N�g�̊p�x�̃Q�b�^�[
       * 
       * @return �擾�����I�u�W�F�N�g�̊p�x
       */
      inline VECTOR GetRotation() const { return _rotation; }
      /**
       * @ �I�u�W�F�N�g�̊g�嗦���Z�b�g����
       * 
       * @param[in] scale �Z�b�g����I�u�W�F�N�g�̊g�嗦
       */
      inline void SetScale(const VECTOR& scale) { _scale = scale; }
      /**
       * @ �I�u�W�F�N�g�̊g�嗦�̃Q�b�^�[
       * 
       * @return �擾�����I�u�W�F�N�g�̊g�嗦
       */
      inline VECTOR GetScale() const { return _scale; }
      /**
       * @ �~�Ɖ~�̓����蔻��p���a���Z�b�g����
       * 
       * @param[in] radius �Z�b�g���锼�a�̑傫��
       */
      inline void SetRadius(const float radius) { _radius = radius; }
      /**
       * @ �~�Ɖ~�̓����蔻��p���a���擾����
       * 
       * @return �擾�������a
       */
      inline float GetRadius() const { return _radius; }
      /**
       * @ ���S������Ƃ郁�b�V���ɓ����������̃t���O���Z�b�g����
       * 
       * @param[in] hitFlag �Z�b�g����t���O
       */
      inline void SetHitFlag(const bool hitFlag) { _hitFlag = hitFlag; }
      /**
       * @ ���S������Ƃ郁�b�V���ɓ����������̃t���O�̃Q�b�^�[
       * 
       * @return �擾�����t���O
       */
      inline bool GetHitFlag() const { return _hitFlag; }
      /**
       * @ ���S�����̂��̃t���O�̃Q�b�^�[
       * 
       * @return ���S�����̂��̃t���O
       */
      inline bool GetDeadFlag() { return _deadFlag; }
      /**
       * @ �X�e�[�g�}�l�[�W���[�̃Q�b�^�[
       * 
       * @return �X�e�[�g�}�l�[�W���[�̃��j�[�N�|�C���^
       */
      inline State::StateManager& GetStateManage() { return *_stateManage; }
      /**
       * @ �R���W�����}�l�[�W���[�̃Q�b�^�[
       * 
       * @return �R���W�����}�l�[�W���[�̃V�F�A�[�h�|�C���^
       */
      inline Collision::CollisionManager& GetCollision() { return *_collsionManage; }
      /**
       * @ �J�����}�l�[�W���[�̃Q�b�^�[
       * 
       * @return �J�����}�l�[�W���[�̃V�F�A�[�h�|�C���^
       */
      inline Camera::CameraManager& GetCamera() { return *_cameraManage; }
      /**
       * @ ���f���A�j���}�l�[�W���[�̃Q�b�^�[
       * 
       * @return ���f���A�j���}�l�[�W���[�̃��j�[�N�|�C���^
       */
      inline Model::ModelAnimeManager& GetModelAnime() { return *_modelAnimeManage; }
      /**
       * @ �X�e�[�g�}�l�[�W���[�̃Z�b�^�[
       * 
       * @param[in] state �X�e�[�g�}�l�[�W���[�̃��j�[�N�|�C���^
       */
      void SetStateManage(std::unique_ptr<State::StateManager> state);
      /**
       * @ ���f���A�j���}�l�[�W���[�̃Z�b�^�[
       * 
       * @param[in] model ���f���A�j���}�l�[�W���[�̃��j�[�N�|�C���^
       */
      void SetModelManage(std::unique_ptr<Model::ModelAnimeManager> model);
      /**
       * @  �J�����}�l�[�W���[�̃Z�b�^�[
       * 
       * @param[in] camera �J�����}�l�[�W���[�̃V�F�A�[�h�|�C���^
       */
      void SetCameraManage(std::shared_ptr<Camera::CameraManager> camera);
      /**
       * @ �I�u�W�F�N�g�Ǘ�����}�l�[�W���[�̃Q�b�^�[
       * 
       * @return �I�u�W�F�N�g�T�[�o�[�̃��j�[�N�|�C���^
       */
      ObjectServer& GetObjectServer();
    protected:
      /**
       * @ �I�u�W�F�N�g�̃X�e�[�g�̃Q�b�^�[
       *
       * @return �I�u�W�F�N�g�̃X�e�[�g
       */
      inline ObjectState GetObjectState() const { return _objectState; }
      /**
       * @ �I�u�W�F�N�g�̃X�e�[�g�̃Z�b�^�[
       *
       * @param[in] objstate �I�u�W�F�N�g�̃X�e�[�g
       */
      inline void SetObjectState(ObjectState objstate) { _objectState = objstate; }
      //!< �X�e�[�g�}�l�[�W���[�̃��j�[�N�|�C���^
      std::unique_ptr<State::StateManager> _stateManage{ nullptr };
      //!< �R���W�����̃V�F�A�[�h�|�C���^
      std::shared_ptr<Collision::CollisionManager> _collsionManage{ nullptr };
      //!< �J�����̃V�F�A�[�h�|�C���^
      std::shared_ptr<Camera::CameraManager> _cameraManage{ nullptr };
      //!< ���f���A�j���}�l�[�W���[�̃��j�[�N�|�C���^
      std::unique_ptr<Model::ModelAnimeManager> _modelAnimeManage{ nullptr };
    protected:
      Application::GameMain& _game;                     //!< �Q�[�����C���N���X�̎Q��
      bool _deadFlag{ false };                          //!< ���S�������̃t���O
      bool _hitFlag{ false };                           //!< �R���W�����p�t���O
      float _radius{ 0.0f };                            //!< �R���W�����p���a
      MATRIX _worldTransform{ MGetIdent() };            //!< ���[���h���W�ϊ�
      VECTOR _position{ 0.0f, 0.0f, 0.0f };             //!< �ʒu���
      VECTOR _rotation{ 0.0f, 0.0f, 0.0f };             //!< �p�x
      VECTOR _scale{ 1.0f, 1.0f, 1.0f };                //!< �g�嗦
      ObjectState _objectState{ ObjectState::Active };  //!< �I�u�W�F�N�g�̃X�e�[�g
    };
  } // namespace Object
} // namespace GlassHeart