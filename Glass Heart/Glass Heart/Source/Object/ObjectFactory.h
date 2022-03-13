
/*****************************************************************//**
 * @file   ObjectFactory.h
 * @brief  オブジェクトファクトリークラスの宣言
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
    /** 二重インクルード防止 */
    class GameMain;

    namespace Object {

        class ObjectBase;
        class CreateBase;
        /**
         * @class ObjectFactory 
         * @brief オブジェクトの生成を一元管理する
         *        生成したいオブジェクト用のクリエイターを登録して使用する
         */
        class ObjectFactory {
        public:
            /**
             * @brief コンストラクタ
             *
             * @param game
             */
            ObjectFactory(GameMain& game);
            /**
             * @brief クリエイターの登録
             *
             * @param type    文字列キー
             * @param creator 登録するクリエイターのインスタンス
             * @return        登録の成否
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
             * @brief オブジェクトの生成
             *
             * @param type 文字列キー
             * @return     生成したインスタンスのポインタ
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
             * @brief 全オブジェクト消去
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
         * @brief ObjectFactoryに登録するクリエイターの基底クラス
         * 　　　　このクラスを継承してクリエイターを定義する
         */
        class CreateBase {
        public:
            virtual ~CreateBase() = default;
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game) = 0;
        };
        /**
        * @class GirlCreate
        * @brief ガール用のクリエイター
        */
        class GirlCreate : public CreateBase {
        public:
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
        * @class GoalPointCreate
        * @brief ゴールポイント用のクリエイター
        */
        class GoalPointCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class PlayerCreate
         * @brief プレイヤー用のクリエイター
         */
        class PlayerCreate : public CreateBase {
        public:
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class EnemyCreate
         * @brief エネミー用のクリエイター
         */
        class CheckPointCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class StageCreate
         * @brief ステージ用のクリエイター
         */
        class StageCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
        /**
         * @class StageCreate
         * @brief カメラフォロー用のクリエイター
         */
        class FollowCameraCreate : public CreateBase {
            virtual std::unique_ptr<ObjectBase> Create(GameMain& game);
        };
    }
}


