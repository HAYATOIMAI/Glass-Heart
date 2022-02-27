
/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  �R���W�����}�l�[�W���[�N���X�̐錾
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

        class CollisionManager {
        public:
            enum class ReportId {
                None,
                HitFromPlayer,
                HitFromEnemy,
            };
            /**
             * @brief�@�R���X�g���N�^
             * 
             * @param owner�@�I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
             */
            CollisionManager(GlassHeart::Object::ObjectBase& owner);
            /**
             * @brief ���Ƃ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �󒆂̑���Ƃ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward  �ړ��ʃx�N�g��
             * @return  �ʒu�x�N�g��
             */
            VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �ǂƂ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitWall(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �󒆂̑���̒�ʂ⑤�ʂƂ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughWMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckHitDeathMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughBMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughWWallMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckThroughBWallMesh(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckFall(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckBFall(const VECTOR& pos, const VECTOR& forward);
            VECTOR CheckWFall(const VECTOR& pos, const VECTOR& forward);
            // �~�̓����蔻��`��
            void RenderCircle(const VECTOR circlePos, float range, unsigned int color);
            // �~�̓����蔻��
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
            MV1_COLL_RESULT_POLY GetFall() { return _fall; }
            MV1_COLL_RESULT_POLY GetBFall() { return _bFall; }
            MV1_COLL_RESULT_POLY GetWFall() { return _wFall; }
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
            MV1_COLL_RESULT_POLY _fall;
            MV1_COLL_RESULT_POLY _bFall;
            MV1_COLL_RESULT_POLY _wFall;

            VECTOR _debugNum1{ 0, 0, 0 };
            VECTOR _debugNum2{ 0, 0, 0 };

            float _radius1{ 0.0f };
            float _radius2{ 0.0f };
        };
    }
}