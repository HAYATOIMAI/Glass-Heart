/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  �R���W�����}�l�[�W���[�N���X�̐錾
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
             * @brief  ���Ƃ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitFloor(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief �󒆂̑���Ƃ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward  �ړ��ʃx�N�g��
             * @return  �ʒu�x�N�g��
             */
            VECTOR CheckJumpStand(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief �󒆂̑���̒�ʂ⑤�ʂƂ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitSideAndBottom(const VECTOR& pos, const VECTOR& forward, int state);
            /**
             * @brief �����f�X���b�V���Ƃ̓����蔻��
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �����f�X���b�V���Ƃ̓����蔻�� 
             * 
             * @param[in] pos �ʒu�x�N�g��
             * @param[in] forward �ړ��ʃx�N�g��
             * @return �ʒu�x�N�g��
             */
            VECTOR CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward);
            /**
             * @brief �f�o�b�O�p�����蔻��`�揈��
             * 
             * @param[in] circlePos �~�̈ʒu�x�N�g��
             * @param[in] range �͈�
             * @param[in] color �F���
             */
            void RenderCircle(const VECTOR circlePos, float range, unsigned int color);
            /**
             * @brief �~�̓����蔻��
             * 
             * @param[in] owner  �`�F�b�N�|�C���g
             * @param[in] target �v���C���[
             * @return �ڐG���Ă��邩
             */
            bool CheckCircleToCircle(const GlassHeart::Object::ObjectBase& owner, const GlassHeart::Object::ObjectBase& target);

           // �e��Q�b�^�[
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
            Object::ObjectBase& _owner;                  //!< �I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
            MV1_COLL_RESULT_POLY _floor;               //!< ���Ƃ̓����蔻��p�ϐ�
            MV1_COLL_RESULT_POLY _stand;               //!< �W�����v�p���Ƃ̓����蔻��ϐ�
            MV1_COLL_RESULT_POLY _wThrough;           //!< �������Ƃ̓����蔻��p�ϐ�
            MV1_COLL_RESULT_POLY _bThrough;           //!< �������Ƃ̓����蔻��p�ϐ�
            MV1_COLL_RESULT_POLY_DIM _sideBottom;  //!< ��ʂ⑤�ʂƂ̓����蔻��p�ϐ�
            MV1_COLL_RESULT_POLY_DIM _wDeath;        //!< �����f�X���b�V���Ƃ̓����蔻��p�ϐ�
            MV1_COLL_RESULT_POLY_DIM _bDeath;        //!< �����f�X���b�V���Ƃ̓����蔻��p�ϐ�
            MV1_COLL_RESULT_POLY_DIM _bWallThrough;   //!< ������ʂ⑤�ʂƂ̓����蔻��p�ϐ�
            MV1_COLL_RESULT_POLY_DIM _wWallThrough;   //!< ������ʂ⑤�ʂƂ̓����蔻��p�ϐ�
        
            float _radius1{ 0.0f };   //!< �`�F�b�N�|�C���g�Ƃ̓����蔻��p���a
            float _radius2{ 0.0f };   //!< �`�F�b�N�|�C���g�Ƃ̓����蔻��p���a
        };
    } // namespce Collision
} // namespace GlassHeart