
/*****************************************************************//**
 * @file   Stage.h
 * @brief  ステージクラスの宣言
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include <memory>

namespace GlassHeart {

    namespace Model {
        class ModelManager;
    }

    class GameMain;

    namespace Stage {
        /**
         * @class Stage
         * @brief ステージクラス
         */
        class Stage : public  Object::ObjectBase {
        public:
            /**
             * @brief コンストラクタ
             * 
             * @param game ゲームメインクラスへの参照
             */
            Stage(GameMain& game);
            /**
             * @brief 更新処理
             * 
             */
            virtual void Process() override;
            /**
             * @brief 描画処理
             * 
             */
            void Render() override;
            ObjectType GetObjectType() const override { return ObjectType::Stage; }
        private:
            //std::unique_ptr<Model::ModelManager> _skySphere;
            //std::unique_ptr<Model::ModelManager> _ground;
            //std::unique_ptr<Model::ModelManager> _test;
            std::unique_ptr<Model::ModelManager> _testStage; //!< ステージ用ユニークポインタ
            std::unique_ptr<Model::ModelManager> _secondStage;
            std::unique_ptr<Model::ModelManager> _backGround;   //!< 
        };
    } // Stage
} // GlassHeart


