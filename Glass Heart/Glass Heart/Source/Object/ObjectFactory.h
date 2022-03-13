
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
#include <random>
#include <unordered_map>
#include <DxLib.h>

namespace GlassHeart {
    /** ��d�C���N���[�h�h�~ */
    class GameMain;

    namespace Object {

        class ObjectBase;
        class CreateBase;
        /**
         * @class ObjectFactory 
         * @brief �I�u�W�F�N�g�̐������ꌳ�Ǘ�����
         *        �����������I�u�W�F�N�g�p�̃N���G�C�^�[��o�^���Ďg�p����
         */
        class ObjectFactory {
        public:
            /**
             * @brief �R���X�g���N�^
             *
             * @param game
             */
            ObjectFactory(GameMain& game);
            /**
             * @brief �N���G�C�^�[�̓o�^
             *
             * @param type    ������L�[
             * @param creator �o�^����N���G�C�^�[�̃C���X�^���X
             * @return        �o�^�̐���
             */
            bool Register(std::string_view type, std::unique_ptr<CreateBase> creator);
            /**
             * @brief
             */
            struct SpawnRecord {
                unsigned int _progress{ 0 };
                std::string _key;
                VECTOR _position{ 0, 0, 0 };
                VECTOR _rosition{ 0, 0, 0 };
            };
            using SpawnTable = std::vector<SpawnRecord>;
            /**
             * @brief �I�u�W�F�N�g�̐���
             *
             * @param type ������L�[
             * @return     ���������C���X�^���X�̃|�C���^
             */
            std::unique_ptr<ObjectBase> Create(std::string_view type);
            /**
             * @brief
             *
             * @param spawnTable
             */
            void SetSpawnTable(SpawnTable spawnTable);
            /**
             * @brief
             *
             */
            void UpdateSpawn();
            /**
             * @brief �S�I�u�W�F�N�g����
             *
             */
            void Clear();

        private:
            GameMain& _game;
            std::unordered_map<std::string, std::unique_ptr<CreateBase>> _creatorMap;
            std::vector<SpawnRecord> _spawnTable;
            unsigned int _progress{ 0 };
            unsigned int _spawnProgress{ 0 };
        };

        /**
         * @class CreateBase
         * @brief ObjectFactory�ɓo�^����N���G�C�^�[�̊��N���X
         * �@�@�@�@���̃N���X���p�����ăN���G�C�^�[���`����
         */
        class CreateBase {
        public:
            virtual ~CreateBase() = default;
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game) = 0;
        };
        /**
        * @class GirlCreate
        * @brief �K�[���p�̃N���G�C�^�[
        */
        class GirlCreate : public CreateBase {
        public:
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
        * @class GoalPointCreate
        * @brief �S�[���|�C���g�p�̃N���G�C�^�[
        */
        class GoalPointCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class PlayerCreate
         * @brief �v���C���[�p�̃N���G�C�^�[
         */
        class PlayerCreate : public CreateBase {
        public:
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class EnemyCreate
         * @brief �G�l�~�[�p�̃N���G�C�^�[
         */
        class CheckPointCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class StageCreate
         * @brief �X�e�[�W�p�̃N���G�C�^�[
         */
        class StageCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class StageCreate
         * @brief �J�����t�H���[�p�̃N���G�C�^�[
         */
        class FollowCameraCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
    }
}


