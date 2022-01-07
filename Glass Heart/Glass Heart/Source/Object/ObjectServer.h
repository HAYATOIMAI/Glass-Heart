
/*****************************************************************//**
 * @file   ObjectServer.h
 * @brief  オブジェクトサーバーの宣言
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
        * @brief オブジェクトを一括管理する
        */
        class ObjectServer {
        public:
            /**
             * @brief オブジェクトの追加
             *
             * @param obj
             */
            void Add(std::unique_ptr<ObjectBase> obj);
            /**
             * @brief 入力処理
             *
             * @param[in] input インプットマネージャークラスの参照
             */
            void Input(AppFrame::InputManager& input);
            /**
             * @brief 更新処理
             *
             */
            void Process();
            /**
             * @brief 描画処理
             *
             */
            void Render();
            /**
             * @brief 全オブジェクト消去
             *
             */
            void AllClear();
            /**
             * @brief オブジェクトの登録
             * 　　　 登録するとオブジェクトから情報を得ることができる
             *
             * @param[in] key 任意の文字列キー
             * @param[in] vec オブジェクトの位置
             */
            void Register(std::string_view key, VECTOR vec);
            /**
             * @brief オブジェクトの一覧を取得
             *
             * @return オブジェクトの一覧の参照
             */
            std::vector<std::unique_ptr<ObjectBase>>& GetObjectLists() { return _objects; }
            /**
             * @brief 登録したオブジェクトの位置を得る
             *
             * @param[in] key 登録済みのキー
             * @return  登録したオブジェクトの位置
             */
            VECTOR GetPosition(std::string_view key);
            /**
             * @brief 登録したアクターの前進方向を得る
             *
             * @param[in] key 登録済みのキー
             * @return 登録したオブジェクトの前進方向単位ベクトル
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


