
/*****************************************************************//**
 * @file   ObjectServer.h
 * @brief  �I�u�W�F�N�g�T�[�o�[�̐錾
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <DxLib.h>
#include "ObjectBase.h"

namespace AppFrame {
    class InputManager;
}

namespace GlassHeart {

    namespace Object {
        /**
        * @class ObjectServer
        * @brief �I�u�W�F�N�g���ꊇ�Ǘ�����
        */
        class ObjectServer {
        public:
            /**
             * @brief �I�u�W�F�N�g�̒ǉ�
             *
             * @param obj
             */
            void Add(std::unique_ptr<ObjectBase> obj);
            /**
             * @brief ���͏���
             *
             * @param[in] input �C���v�b�g�}�l�[�W���[�N���X�̎Q��
             */
            void Input(AppFrame::InputManager& input);
            /**
             * @brief �X�V����
             *
             */
            void Process();
            /**
             * @brief �`�揈��
             *
             */
            void Render();
            /**
             * @brief �S�I�u�W�F�N�g����
             *
             */
            void AllClear();
            /**
             * @brief �I�u�W�F�N�g�̓o�^
             * �@�@�@ �o�^����ƃI�u�W�F�N�g������𓾂邱�Ƃ��ł���
             *
             * @param[in] key �C�ӂ̕�����L�[
             * @param[in] vec �I�u�W�F�N�g�̈ʒu
             */
            void Register(std::string_view key, VECTOR vec);
            /**
             * @brief �I�u�W�F�N�g�̈ꗗ���擾
             *
             * @return �I�u�W�F�N�g�̈ꗗ�̎Q��
             */
            std::vector<std::unique_ptr<ObjectBase>>& GetObjectLists() { return _objects; }
            /**
             * @brief �o�^�����I�u�W�F�N�g�̈ʒu�𓾂�
             *
             * @param[in] key �o�^�ς݂̃L�[
             * @return  �o�^�����I�u�W�F�N�g�̈ʒu
             */
            VECTOR GetPosition(std::string_view key);
            /**
             * @brief �o�^�����A�N�^�[�̑O�i�����𓾂�
             *
             * @param[in] key �o�^�ς݂̃L�[
             * @return �o�^�����I�u�W�F�N�g�̑O�i�����P�ʃx�N�g��
             */
            VECTOR GetForward(std::string_view key);
        private:
            bool 	_updating{ false }; //!< 
            std::vector<std::unique_ptr<ObjectBase>> _objects;
            std::vector<std::unique_ptr<ObjectBase>> _pendingObjects;
            std::unordered_map<std::string, VECTOR> _registry;
        };
    }
}


