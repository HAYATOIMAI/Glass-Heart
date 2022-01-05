
/*****************************************************************//**
 * @file   ModelManager.h
 * @brief  3Dモデル管理の基底クラス
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
             * @brief コンストラクタ
             *
             * @param owner 所有者への参照
             */
            ModelManager(GlassHeart::Object::ObjectBase& owner);
            /**
             * @brief デストラクタ
             *
             */
            virtual ~ModelManager();
            /**
             * @brief 初期化
             *
             */
            virtual void Init();
            /**
             * @brief 更新
             *
             */
            virtual void Update();
            /**
             * @brief 描画
             *
             */
            virtual void Draw();
            /**
             * @brief ハンドルの取得
             *
             * @return  モデルのハンドル
             */
            virtual int handle(std::string_view key, int no = 0);
            /**
             * @brief     モデルの設定
             *
             * @param key ResourceServerに登録済みのキー
             * @param no  同一モデルの通し番号
             * @return    実際に登録し通し番号
             */
            virtual int SetModel(std::string_view key, int no = 0);
            /**
             * @brief 座標の設定
             *
             * @param position  座標x,y,z
             */
            virtual void SetPosition(VECTOR position);
            /**
             * .@brief 回転角度の設定
             *
             * @param rotation 回転角度x,y,z
             */
            virtual void SetRotation(VECTOR rotation);
            /**
             * @brief 拡大率の設定
             *
             * @param scale 拡大率
             */
            virtual void SetScale(VECTOR scale);
            /**
             * @brief ワールド行列の設定
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




