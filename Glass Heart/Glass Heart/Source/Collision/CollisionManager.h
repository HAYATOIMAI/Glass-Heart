
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
        /**
         * @class CollisionManager
         * @brief �Փ˔���Ǘ��p�N���X
         */
        class CollisionManager {
        public:
            /**
             * @brief�@�R���X�g���N�^
             * 
             * @param owner�@�I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
             */
            CollisionManager(GlassHeart::Object::ObjectBase& owner);
            /**
             * @brief �O���X�e�[�W:���Ƃ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief  �O���X�e�[�W:�󒆂̑���Ƃ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward  �ړ��ʃx�N�g��
             * @return  �ʒu�x�N�g��
             */
            VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief  �O���X�e�[�W: �󒆂̑���̒�ʂ⑤�ʂƂ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief �O���X�e�[�W: 
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �O���X�e�[�W: 
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �O���X�e�[�W: �󒆂̑���̗�������
             * 
             * @param[in] pos
             * @param[in] forward
             * @return 
             */
            VECTOR CheckFall(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �~�̓����蔻��`��
             * 
             * @param[in] circlePos �~�̈ʒu�x�N�g��
             * @param[in] range �͈�
             * @param[in] color �F���
             */
            void RenderCircle(const VECTOR circlePos, float range, unsigned int color);
            /**
             * @brief �~�̓����蔻��
             * 
             * @param[in] owner
             * @param[in] target
             * @return 
             */
            bool CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target);

           // �e��Q�b�^�[
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
        
            float _radius1{ 0.0f };
            float _radius2{ 0.0f };
        };
    }
}