
/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  コリジョンマネージャークラスの宣言
 * 
 * @author Hayato Imai
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
             * @brief 床との当たり判定
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward 移動量ベクトル
             * @return 位置ベクトル
             */
            VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief 空中の足場との当たり判定
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward  移動量ベクトル
             * @return  位置ベクトル
             */
            VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief 空中の足場の底面や側面との当たり判定
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward 移動量ベクトル
             * @return 位置ベクトル
             */
            VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief
             * 
             * @param[in] pos 位置ベクトル
             * @param[in] forward 移動量ベクトル
             * @return 位置ベクトル
             */
            VECTOR CheckThroughWMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief 
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckThroughBMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckThroughWWallMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief 
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckThroughBWallMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckFall(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief 円の当たり判定描画
             * 
             * @param[in] circlePos 円の位置ベクトル
             * @param[in] range 範囲
             * @param[in] color 色情報
             */
            void RenderCircle(const VECTOR circlePos, float range, unsigned int color);
            /**
             * @brief 円の当たり判定
             * 
             * @param[in] owner
             * @param[in] target
             * @return 
             */
            bool CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target);

            VECTOR CheckHitSecondFloor(const VECTOR& pos, const VECTOR& forward);

            VECTOR CheckHitSecondJumpStand(const VECTOR& pos, const VECTOR& forward);

            VECTOR CheckHitSecondFall(const VECTOR& pos, const VECTOR& forward);

            VECTOR CheckHitSecondThroughWMesh(const VECTOR& pos, const VECTOR& forward);

            VECTOR CheckHitSecondThroughBMesh(const VECTOR& pos, const VECTOR& forward);

           // 各種ゲッター
           inline MV1_COLL_RESULT_POLY GetHitFloor() { return _floor; }
           inline MV1_COLL_RESULT_POLY_DIM GetHitwall() { return _collpol; }
           inline MV1_COLL_RESULT_POLY_DIM GetSideAndBottom() { return _sideBottom; }
           inline MV1_COLL_RESULT_POLY GetStand() { return _stand; }
           inline MV1_COLL_RESULT_POLY GetWThrough() { return _wThrough; }
           inline MV1_COLL_RESULT_POLY_DIM GetWDeathMesh() { return _wDeath; }
           inline MV1_COLL_RESULT_POLY_DIM GetBDeathMesh() { return _bDeath; }
           inline MV1_COLL_RESULT_POLY GetBThrough() { return _bThrough; }
           inline MV1_COLL_RESULT_POLY_DIM GetBWallThroughMesh() { return _bWallThrough; }
           inline MV1_COLL_RESULT_POLY_DIM GetWWallThroughMesh() { return _wWallThrough; }
           inline MV1_COLL_RESULT_POLY GetFall() { return _fall; }
           inline MV1_COLL_RESULT_POLY GetHitSecondFloor() { return _secondFloor; }
           inline MV1_COLL_RESULT_POLY GetSecondJumpStand() { return _seconsdStand; }
           inline MV1_COLL_RESULT_POLY GetSecondFall() { return _secondFall; }
           inline MV1_COLL_RESULT_POLY GetSecondWThroughMesh() { return _secondWThrough;}
           inline MV1_COLL_RESULT_POLY GetSecondBThroughMesh() { return _secondBThrough; }
        private:
            Object::ObjectBase& _owner;
            MV1_COLL_RESULT_POLY _floor;
            MV1_COLL_RESULT_POLY _stand;
            MV1_COLL_RESULT_POLY _wThrough;
            MV1_COLL_RESULT_POLY_DIM _collpol;
            MV1_COLL_RESULT_POLY_DIM _sideBottom;
            MV1_COLL_RESULT_POLY_DIM _wDeath;
            MV1_COLL_RESULT_POLY_DIM _bDeath;
            MV1_COLL_RESULT_POLY _bThrough;
            MV1_COLL_RESULT_POLY_DIM _bWallThrough;
            MV1_COLL_RESULT_POLY_DIM _wWallThrough;
            MV1_COLL_RESULT_POLY _fall;
            MV1_COLL_RESULT_POLY _secondFloor;
            MV1_COLL_RESULT_POLY _seconsdStand;
            MV1_COLL_RESULT_POLY _secondFall;
            MV1_COLL_RESULT_POLY _secondWThrough;
            MV1_COLL_RESULT_POLY _secondBThrough;

            float _radius1{ 0.0f };
            float _radius2{ 0.0f };
        };
    }
}