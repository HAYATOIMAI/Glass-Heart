/*****************************************************************//**
 * @file   Stage.h
 * @brief  �X�e�[�W�N���X�̐錾
 *
 * @author Hayato Imai
 * @date    December 2021
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include <memory>

 /**
	* @namespace GlassHeart
	* @brief �v���W�F�N�g��
	*/
namespace GlassHeart {
	namespace Model {
		class ModelManager;
	}
	namespace Application {
		class GameMain;
	}
	/**
	 * @namespace Stage
	 * @brief  �X�e�[�W�֌W
	 */
	namespace Stage {
		/**
		 * @class Stage
		 * @brief �X�e�[�W�N���X
		 */
		class Stage : public  Object::ObjectBase {
		public:
			/**
			 * @brief �R���X�g���N�^
			 *
			 * @param game �Q�[�����C���N���X�ւ̎Q��
			 */
			Stage(Application::GameMain& game);
			/**
			 * @brief �X�V����
			 *
			 */
			virtual void Process() override;
			/**
			 * @brief �`�揈��
			 *
			 */
			void Render() override;

			inline ObjectType GetObjectType() const override { return ObjectType::Stage; }
		private:
			std::unique_ptr<Model::ModelManager> _backGround;   //!< �X�J�C�X�t�B�A�p���j�[�N�|�C���^
			std::unique_ptr<Model::ModelManager> _stage;          //!< �X�e�[�W�p���j�[�N�|�C���^
		};
	} // namespace Stage
} // namespace GlassHeart