/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  コリジョンマネージャークラスの宣言
 * 
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <DxLib.h>

namespace GlassHeart {
    namespace Object {
        class ObjectBase;
    }
    namespace Collision {
        /**
         * @class CollisionManager
         * @brief 衝突判定管理用クラス
         */
        class CollisionManager {
        public:
            /**
             * @brief　コンストラクタ
             * 
             * @param owner　オブジェクトベースクラスへの参照
             */
            CollisionManager(GlassHeart::Object::ObjectBase& owner);
            /**
             * @brief  床との当たり判定
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward 移動量ベクトル
             * @return 位置ベクトル
             */
            VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief 空中の足場との当たり判定
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward  移動量ベクトル
             * @return  位置ベクトル
             */
            VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief 空中の足場の底面や側面との当たり判定
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward 移動量ベクトル
             * @return 位置ベクトル
             */
            VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief 白いデスメッシュとの当たり判定
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward 移動量ベクトル
             * @return 位置ベクトル
             */
            VECTOR CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief 黒いデスメッシュとの当たり判定 
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward 移動量ベクトル
             * @return 位置ベクトル
             */
            VECTOR CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief デバッグ用当たり判定描画処理
             * 
             * @param[in] circlePos 円の位置ベクトル
             * @param[in] range 範囲
             * @param[in] color 色情報
             */
            void RenderCircle(const VECTOR circlePos, float range, unsigned int color);
            /**
             * @brief 円の当たり判定
             * 
             * @param[in] owner  チェックポイント
             * @param[in] target プレイヤー
             * @return 接触しているか
             */
            bool CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target);

           // 各種ゲッター
           inline MV1_COLL_RESULT_POLY GetHitFloor() { return _floor; }
           inline MV1_COLL_RESULT_POLY_DIM GetSideAndBottom() { return _sideBottom; }
           inline MV1_COLL_RESULT_POLY GetStand() { return _stand; }
           inline MV1_COLL_RESULT_POLY GetWThrough() { return _wThrough; }
           inline MV1_COLL_RESULT_POLY GetBThrough() { return _bThrough; }
           inline MV1_COLL_RESULT_POLY_DIM GetWDeathMesh() { return _wDeath; }
           inline MV1_COLL_RESULT_POLY_DIM GetBDeathMesh() { return _bDeath; }
           inline MV1_COLL_RESULT_POLY_DIM GetBWallThroughMesh() { return _bWallThrough; }
           inline MV1_COLL_RESULT_POLY_DIM GetWWallThroughMesh() { return _wWallThrough; }
        private:
            Object::ObjectBase& _owner;                  //!< オブジェクトベースクラスへの参照
            MV1_COLL_RESULT_POLY _floor;               //!< 床との当たり判定用変数
            MV1_COLL_RESULT_POLY _stand;               //!< ジャンプ用床との当たり判定変数
            MV1_COLL_RESULT_POLY _wThrough;           //!< 白い床との当たり判定用変数
            MV1_COLL_RESULT_POLY _bThrough;           //!< 黒い床との当たり判定用変数
            MV1_COLL_RESULT_POLY_DIM _sideBottom;  //!< 底面や側面との当たり判定用変数
            MV1_COLL_RESULT_POLY_DIM _wDeath;        //!< 白いデスメッシュとの当たり判定用変数
            MV1_COLL_RESULT_POLY_DIM _bDeath;        //!< 黒いデスメッシュとの当たり判定用変数
            MV1_COLL_RESULT_POLY_DIM _bWallThrough;   //!< 白い底面や側面との当たり判定用変数
            MV1_COLL_RESULT_POLY_DIM _wWallThrough;   //!< 黒い底面や側面との当たり判定用変数
        
            float _radius1{ 0.0f };   //!< チェックポイントとの当たり判定用半径
            float _radius2{ 0.0f };   //!< チェックポイントとの当たり判定用半径
        };
    } // namespce Collision
} // namespace GlassHeart