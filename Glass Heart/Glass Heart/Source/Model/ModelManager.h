/*****************************************************************//**
 * @file   ModelManager.h
 * @brief  ���f���}�l�[�W���[�N���X�̐錾
 *
 * @author Hayato Imai, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <string_view>
#include <cstdint>
 /**
  * @namespace GlassHeart
  * @brief �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }
  /**
   * @namespace Model
   * @brief     ���f���֌W
   */
  namespace Model {
    /**
     * @class ModelManager
     * @brief ���f���}�l�[�W���[�N���X�̐錾
     */
    class ModelManager {
    public:
      /**
       * @brief              �R���X�g���N�^
       *
       * @param[in] owner    �I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
       */
      ModelManager(GlassHeart::Object::ObjectBase& owner);
      /**
       * @brief              �f�X�g���N�^
       */
      virtual ~ModelManager();
      /**
       * @brief              ������
       */
      virtual void Init();
      /**
       * @brief              �X�V����
       */
      virtual void Update();
      /**
       * @brief              �`�揈��
       */
      virtual void Draw();
      /**
       * @brief              ���f���̎擾
       *                                 
       * @param[in] key      ResourceServer�ɓo�^�ς݂̃L�[
       * @param[in] no       ���ꃂ�f���̒ʂ��ԍ�
       * @return             ���f���̏��
       */
      virtual std::int_fast32_t handle(std::string_view key, int no = 0);
      /**
       * @brief              ���f���̐ݒ�
       *                                
       * @param[in] key      ResourceServer�ɓo�^�ς݂̃L�[
       * @param[in] no       ���ꃂ�f���̒ʂ��ԍ�
       * @return             ���ۂɓo�^�����ʂ��ԍ�
       */
      virtual std::int_fast32_t SetModel(std::string_view key, int no = 0);
      /**
       * @brief              ���W�̐ݒ�
       *                               
       * @param[in] position ���Wx,y,z
       */
      virtual void SetPosition(VECTOR position);
      /**
       * .@brief             ��]�p�x�̐ݒ�
       *                     
       * @param[in] rotation ��]�p�xx,y,z
       */
      virtual void SetRotation(VECTOR rotation);
      /**
       * @brief              �g�嗦�̐ݒ�
       *                     
       * @param[in] scale    �g�嗦
       */                    
      virtual void SetScale(VECTOR scale);
      /**
       * @brief              ���[���h�s��̐ݒ�
       *                     
       * @param[in] world    ���[���h���W
       */
      virtual void SetMatrix(MATRIX& world);
      /**
       * @brief              �O���t�B�b�N�n���h�����Z�b�g����
       * 
       * @param[in] handle   �Z�b�g����O���t�B�b�N�n���h��
       */
      inline void SetHandle(const std::int_fast32_t handle) { _handle = handle; }
      /**
       * @brief              �O���t�B�b�N�n���h�����擾����
       * 
       * @return             �O���t�B�b�N�n���h��
       */
      inline std::int_fast32_t GetHandle() const { return _handle; }
      /**
       * @brief              ���f���̃J���[���Z�b�g����
       * 
       * @param[in] index    �ʂ��ԍ�
       * @param[in] r        �ԐF�̃J���[�l
       * @param[in] g        �ΐF�̃J���[�l
       * @param[in] b        �F�̃J���[�l
       */
      void SetColor(std::int_fast32_t index, float r, float g, float b);
    protected:
      Object::ObjectBase& _owner;       //!< �I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
      std::int_fast32_t _handle{ -1 };  //!< ���f���p�n���h��
      std::string _key{ "" };           //!< ������
      bool _isLighting{ true };         //!< ���C�e�B���O���������邩�̃t���O
    };
  } //  namespace Model
} // namespace GlassHeart