/*****************************************************************//**
 * @file   ModelAnimeManager.h
 * @brief  3D���f���Ǘ�
 *
 * @author Hayato Imai, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "ModelManager.h"
#include <string_view>
#include <unordered_map>

 /**
	* @namespace GlassHeart
	* @brief �v���W�F�N�g��
	*/
namespace GlassHeart {
	namespace Object {
		class ObjectBase;
	}
	/**
	 * @namespace Model
	 * @brief ���f���֌W
	 */
	namespace Model {
		/**
		 * @class ModelAnimeManager
		 * @brief ���f���A�j���[�V�����Ǘ��N���X
		 */
		class ModelAnimeManager : public ModelManager {
		public:
			/**
			 * @brief�@�R���X�g���N�^
			 *
			 * @param[in] owner �I�u�W�F�N�g�x�[�X�N���X�ւ̎Q��
			 */
			ModelAnimeManager(GlassHeart::Object::ObjectBase& owner);
			/**
			 * @brief�@�f�X�g���N�^
			 *
			 */
			virtual ~ModelAnimeManager() override;
			/**
			 * @brief ������
			 *
			 */
			void Init() override;
			/**
			 * @brief �A�j���[�V�����̓o�^
			 *
			 * @param[in] key �C�ӂ̕�����L�[
			 * @param[in] animIndex �֘A�t����A�j���C���f�b�N�X
			 */
			void Register(std::string_view key, int animIndex);
			/**
			 * @brief �X�V
			 *
			 */
			void Update() override;
			/**
			 * @brief �`��
			 *
			 */
			void Draw() override;
			/**
			 * @brief �A�j���[�V�����̕ύX
			 *
			 * @param key       �C�ӂ̕�����L�[
			 * @param repeate �A�j���[�V�����̃��[�v��
			 * @param[in] newAnimIndex �A�j���C���f�b�N�X
			 */
			void ChangeAnime(std::string_view key, bool repeate = false);
			/**
			 * @brief �A�j���[�V�����u�����h
			 *
			 */
			void AnimeBlend();
			/**
			 * @brief �A�j���[�V�������J��Ԃ����񐔂̎擾
			 *
			 * @return �J��Ԃ�����
			 */
			int GetRepeatedCount() const { return _repeatedCount; }
			/**
			 * @brief �A�j���[�V�����̑����Ԃ��擾
			 *
			 * @return ������
			 */
			float GetPlayTime() const { return _playTime; }
			/**
			 * @brief �A�j���[�V�����̑����Ԃ��擾
			 *
			 * @return ������
			 */
			float GetPlayProgress() const { return _playTime / _totalTime; }
			/**
			 * @brief �Đ����Ԃ̊|���ݒ�
			 *
			 * @param[in] timeRate �Đ����Ԃ̊|��
			 */
			void SetTimeRate(float timeRate) { _timeRate = timeRate; }
			/**
			 * @brief �Đ����Ԋ|���̎擾
			 *
			 * @return �Đ����Ԋ|��
			 */
			float GetTimeRate() { return _timeRate; }
		private:
			bool _repeate{ false };      //!< �A�j���[�V�����̃��[�v��
			float _animrate{ 1.f };       //!< �A�j���[�V�����u�����h��
			float _playTime{ 0 };          //!< ������
			float _timeRate{ 1.f };       //!< �Đ����Ԋ|��
			float _totalTime{ 0 };        //!< �A�j���[�V�����̑�����
			int _animIndex{ -1 };          //!< �A�j���[�V�����ԍ�
			int _attachIndex{ -1 };       //!< �A�^�b�`����ԍ�
			int _oldattachIndex{ -1 };  //!< �O�̃A�^�b�`�ԍ�
			int _repeatedCount{ 0 };     //!< �A�j���[�V�������J��Ԃ�����
			//!< ���W�X�g��
			std::unordered_map<std::string, int> _registry;
		};
	} //  namespace Model
} //  namespace GlassHeart