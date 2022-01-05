
/*****************************************************************//**
 * @file   ModelManager.h
 * @brief  3D���f���Ǘ��̊��N���X
 * 
 * @author Hayato Imai
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

        class ModelManager {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param owner ���L�҂ւ̎Q��
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
             * @brief �n���h���̎擾
             *
             * @return  ���f���̃n���h��
             */
            virtual int handle(std::string_view key, int no = 0);
            /**
             * @brief     ���f���̐ݒ�
             *
             * @param key ResourceServer�ɓo�^�ς݂̃L�[
             * @param no  ���ꃂ�f���̒ʂ��ԍ�
             * @return    ���ۂɓo�^���ʂ��ԍ�
             */
            virtual int SetModel(std::string_view key, int no = 0);
            /**
             * @brief ���W�̐ݒ�
             *
             * @param position  ���Wx,y,z
             */
            virtual void SetPosition(VECTOR position);
            /**
             * .@brief ��]�p�x�̐ݒ�
             *
             * @param rotation ��]�p�xx,y,z
             */
            virtual void SetRotation(VECTOR rotation);
            /**
             * @brief �g�嗦�̐ݒ�
             *
             * @param scale �g�嗦
             */
            virtual void SetScale(VECTOR scale);
            /**
             * @brief ���[���h�s��̐ݒ�
             *
             * @param world
             */
            virtual void SetMatrix(MATRIX& world);

            void SetHandle(int handle) { _handle = handle; }
            int GetHandle() { return _handle; }
            void SetColor(int index, float r, float g, float b);
        protected:
            GlassHeart::Object::ObjectBase& _owner;
            int _handle{ -1 };
            std::string _key;
            bool _isLighting{ true };
        };
    }
}




