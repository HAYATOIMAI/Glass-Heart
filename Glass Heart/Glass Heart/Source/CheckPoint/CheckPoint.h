/*********************************************************************
 * @file   CheckPoint.h
 * @brief  �`�F�b�N�|�C���g�N���X�̐錾
 *
 * @author Yoshihiro Takahashi
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "../Application/GameMain.h"
#include "../Object/ObjectBase.h"
#include "../Collision/CollisionManager.h"

namespace GlassHeart {
	namespace Model {
		class ModelManager;
	}
	namespace Application {
		class GameMain;
	}
	/**
   * @namespace CheckPoint
   * @brief �`�F�b�N�|�C���g�֌W
   */
	namespace CheckPoint {
		class CheckPoint : public Object::ObjectBase {
		public:
			/**
			 * @brief �R���X�g���N�^
			 *
			 * @param[in] game �Q�[�����C���N���X�ւ̎Q��
			 */
			CheckPoint(Application::GameMain& game);
			/**
			 * @brief�@�f�X�g���N�^
			 *
			 */
			virtual ~CheckPoint()override = default;
			/**
			 * @brief �X�V����
			 *
			 */
			void Process() override;
			/**
			 * @brief �`�揈��
			 *
			 */
			void Render() override;

			ObjectType GetObjectType() const override { return ObjectType::CheckPoint; };

		private:
			int _checkPoint{ -1 };                                     //!< �`�F�b�N�|�C���g�p�O���t�B�b�N�n���h��
			VECTOR _checkDrawPos{ 8190.0f, 5880.0f, 30.0f };  //!< �`�F�b�N�|�C���g�`��p
		};
	} // namespace CheckPoint
} // namespace GlassHeart 