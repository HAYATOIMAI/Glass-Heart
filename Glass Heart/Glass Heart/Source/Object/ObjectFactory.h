/*****************************************************************//**
 * @file   ObjectFactory.h
 * @brief  �I�u�W�F�N�g�t�@�N�g���[�N���X�̐錾
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <DxLib.h>
#include "CreateBase.h"
 /**
  * @namespace GlassHeart
  * @brief     �v���W�F�N�g��
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  /**
   * @namespace Object
   * @brief     �I�u�W�F�N�g�֌W
   */
  namespace Object {
    class CreateBase;
    /**
     * @class ObjectFactory
     * @brief �I�u�W�F�N�g�̐������ꌳ�Ǘ�����
     *        �����������I�u�W�F�N�g�p�̃N���G�C�^�[��o�^���Ďg�p����
     */
    class ObjectFactory {
    public:
      /**
       * @brief              �R���X�g���N�^
       *                     
       * @param[in] game     �Q�[�����C���N���X�ւ̎Q��
       */
      ObjectFactory(Application::GameMain& game);
      /**
       * @brief              �N���G�C�^�[�̓o�^
       *
       * @param[in] type     ������L�[
       * @param[in] creator  �o�^����N���G�C�^�[�̃C���X�^���X
       * @return             �o�^�̐���
       */
      bool Register(std::string_view type, std::unique_ptr<CreateBase> creator);
      /**
       * @brief              �I�u�W�F�N�g�̐���
       *                     
       * @param[in] type     ������L�[
       * @return             ���������C���X�^���X�̃|�C���^
       */
      std::unique_ptr<ObjectBase> Create(std::string_view type);
      /**
       * @brief              �S�I�u�W�F�N�g����
       */
      void Clear();
    private:
      //!< �Q�[�����C���N���X�ւ̎Q��
      Application::GameMain& _game; 
      //!< �����������I�u�W�F�N�g�p�̃N���G�C�^�[�}�b�v
      std::unordered_map<std::string, std::unique_ptr<CreateBase>> _creatorMap;
    };
  } // namespace Object
} // namespace GlassHeart