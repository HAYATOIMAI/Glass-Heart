
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

        struct Sphere {
            Sphere(const VECTOR& center, float radius);
            bool Contains(const VECTOR& point) const;

            VECTOR center;
            float radius;
        };

        bool Intersect(const Sphere& a, const Sphere& b);

        class CollisionManager {
        public:
            enum class ReportId {
                None,
                HitFromPlayer,
                HitFromEnemy,
            };
            /**
             * @brief　コンストラクタ
             * 
             * @param owner　オブジェクトベースクラスへの参照
             */
            CollisionManager(GlassHeart::Object::ObjectBase& owner);
            /**
             * @brief 床との当たり判定
             * 
             * @param pos 位置ベクトル
             * @param forward フォワードベクトル
             * @return 
             */
            VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckHitWall(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughWMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckHitDeathMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughBMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughWWallMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughBWallMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckPlayerCapsule(const VECTOR& pos, const VECTOR& forward);

            // 円の当たり判定描画
            void RenderCircle(const VECTOR circlePos, float range, int red, int green, int blue);
            // 円の当たり判定
            bool CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target);

            void Render();

            struct Report {
                ReportId id{ ReportId::None };
                VECTOR position{ 0, 0, 0 };
            };

            void SetReport(Report report) { *_report = report; }
            Report& GetReport() const { return *_report; }
            MV1_COLL_RESULT_POLY Mcrp() { return _mcrp; }
            MV1_COLL_RESULT_POLY_DIM CollPol() { return _collpol; }
            MV1_COLL_RESULT_POLY_DIM GetSideAndBottom() { return _sideBottom; }
            MV1_COLL_RESULT_POLY GetStand() { return _stand; }
            MV1_COLL_RESULT_POLY GetWThrough() { return _wThrough; }
            MV1_COLL_RESULT_POLY_DIM GetDeathMesh() { return _death; }
            MV1_COLL_RESULT_POLY GetBThrough() { return _bThrough; }
            MV1_COLL_RESULT_POLY_DIM GetBWallThroughMesh() { return _bWallThrough; }
            MV1_COLL_RESULT_POLY_DIM GetWWallThroughMesh() { return _wWallThrough; }
            MV1_COLL_RESULT_POLY_DIM GetPlayerCapsule() { return _playercap; }
        private:
            Object::ObjectBase& _owner;
            std::unique_ptr<Report> _report;
            MV1_COLL_RESULT_POLY _mcrp;
            MV1_COLL_RESULT_POLY _stand;
            MV1_COLL_RESULT_POLY _wThrough;
            MV1_COLL_RESULT_POLY_DIM _collpol;
            MV1_COLL_RESULT_POLY_DIM _sideBottom;
            MV1_COLL_RESULT_POLY_DIM _death;
            MV1_COLL_RESULT_POLY _bThrough;
            MV1_COLL_RESULT_POLY_DIM _bWallThrough;
            MV1_COLL_RESULT_POLY_DIM _wWallThrough;
            MV1_COLL_RESULT_POLY_DIM _playercap;

            VECTOR _debugNum1{ 0, 0, 0 };
            VECTOR _debugNum2{ 0, 0, 0 };

            float _radius1{ 0.0f };
            float _radius2{ 0.0f };
        };
    }
}