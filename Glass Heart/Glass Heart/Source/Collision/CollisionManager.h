
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
             * @brief
             * 
             * @param pos
             * @param forward
             * @return 
             */
            VECTOR CheckTerrain(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckHitWall(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckWThroughMeah(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckHitDeathFloor(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughBMesh(const VECTOR& pos, const VECTOR& forward);

            void Render();

            struct Report {
                ReportId id{ ReportId::None };
                VECTOR position{ 0, 0, 0 };
            };

            void SetReport(Report report) { *_report = report; }
            Report& GetReport() const { return *_report; }
            MV1_COLL_RESULT_POLY Mcrp() { return _mcrp; }
            MV1_COLL_RESULT_POLY_DIM CollPol() { return _collpol; }
            MV1_COLL_RESULT_POLY GetStand() { return _stand; }
            MV1_COLL_RESULT_POLY GetWThrough() { return _wThrough; }
            MV1_COLL_RESULT_POLY GetDeathMesh() { return _death; }
            MV1_COLL_RESULT_POLY GetBThrough() { return _bThrough; }
        private:
            Object::ObjectBase& _owner;
            std::unique_ptr<Report> _report;
            MV1_COLL_RESULT_POLY _mcrp;
            MV1_COLL_RESULT_POLY _stand;
            MV1_COLL_RESULT_POLY _wThrough;
            MV1_COLL_RESULT_POLY_DIM _collpol;
            MV1_COLL_RESULT_POLY _death;
            MV1_COLL_RESULT_POLY _bThrough;


            VECTOR _debugNum1{ 0, 0, 0 };
            VECTOR _debugNum2{ 0, 0, 0 };
        };
    }

   
}