
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

namespace GlassHeart {
   
    namespace Object {
        class ObjectBase;
    }

    namespace Model {
        /**
         * @class ModelManager
         * @brief ���f���}�l�[�W���[�N���X�̐錾
         */
        class ModelManager {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param[in] owner �I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
             */
            ModelManager(GlassHeart::Object::ObjectBase& owner);
            /**
             * @brief �f�X�g���N�^
             *
             */
            virtual ~ModelManager();
            /**
             * @brief ������
             *
             */
            virtual void Init();
            /**
             * @brief �X�V
             *
             */
            virtual void Update();
            /**
             * @brief �`��
             *
             */
            virtual void Draw();
            /**
             * @brief ���f���̎擾
             * 
             * @param[in] key ResourceServer�ɓo�^�ς݂̃L�[
             * @param[in] no  ���ꃂ�f���̒ʂ��ԍ�
             * @return ���f���̏��
             */
            virtual int handle(std::string_view key, int no = 0);
            /**
             * @brief     ���f���̐ݒ�
             *
             * @param[in] key ResourceServer�ɓo�^�ς݂̃L�[
             * @param[in] no  ���ꃂ�f���̒ʂ��ԍ�
             * @return    ���ۂɓo�^�����ʂ��ԍ�
             */
            virtual int SetModel(std::string_view key, int no = 0);
            /**
             * @brief ���W�̐ݒ�
             *
             * @param[in] position  ���Wx,y,z
             */
            virtual void SetPosition(VECTOR position);
            /**
             * .@brief ��]�p�x�̐ݒ�
             *
             * @param[in] rotation ��]�p�xx,y,z
             */
            virtual void SetRotation(VECTOR rotation);
            /**
             * @brief �g�嗦�̐ݒ�
             *
             * @param[in] scale �g�嗦
             */
            virtual void SetScale(VECTOR scale);
            /**
             * @brief ���[���h�s��̐ݒ�
             *
             * @param[in] world ���[���h���W
             */
            virtual void SetMatrix(MATRIX& world);

            inline void SetHandle(int handle) { _handle = handle; }
            inline int GetHandle() { return _handle; }
            void SetColor(int index, float r, float g, float b);
        protected:
            GlassHeart::Object::ObjectBase& _owner; //!< �I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
            int _handle{ -1 };                      //!< ���f���p�n���h��
            std::string _key;                       //!< ������
            bool _isLighting{ true };               //!< ���C�e�B���O���������邩�̃t���O
        };
    } // Model
} // GlassHeart