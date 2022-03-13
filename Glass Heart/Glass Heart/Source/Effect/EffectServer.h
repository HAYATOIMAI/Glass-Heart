/*****************************************************************//**
 * @file   EffectServer.h
 * @brief  �G�t�F�N�g�Ǘ��N���X�̐錾
 *
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <EffekseerForDXLib.h>
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <string>
#include "../Application/GameMain.h"

namespace GlassHeart {
	namespace Effect {
		class EffectServer {
		public:

			using EffectMap = std::unordered_map<std::string, std::pair<std::string, float>>;

			EffectServer(GameMain& game);
			~EffectServer();
			/**
			 * @brief ������
			 * 
			 */
			void Initialize();
			/**
			 * @brief ���\�[�X�̏�������
			 * 
			 */
			void Clear();
			/**
			 * @brief �G�t�F�N�g���\�[�X�̃��[�h
			 * 
			 * @param[in] key �L�[�ƂȂ镶����
			 * @param[in] filename �t�@�C����
			 * @param[in] magnification �g�嗦
			 */
			void LoadEffect(std::string_view key, std::string_view filename, float magnification);
			/**
			 * @brief �G�t�F�N�g���\�[�X�ꊇ�ǂݍ���
			 * 
			 * @param effectmap
			 */
			void LoadEfeects(const EffectMap& effectmap);
			/**
			 * @brief ���΃p�X�̕ύX
			 * 
			 * @param[in] path ���΃p�X��
			 */
			void ChangeCurrentFile(std::string_view path);
			/**
			 * @brief �G�t�F�N�g���\�[�X�̎擾
			 * 
			 * @param key
			 * @return �G�t�F�N�g�̃��\�[�X�n���h�� 
			 */
			int GetEffectResHandle(std::string_view key);
			/**
			 * @brief �G�t�F�N�g���\�[�X�����݂��Ă��邩��Ԃ�
			 * 
			 * @param key
			 * @return ���\�[�X�����邩�̐^�U
			 */
			bool GetEffectResContein(std::string_view key);
		private:
			GameMain& _game;
			std::filesystem::path _currentdirectory;
			std::unordered_map<std::string, int> _effects;
		};
	}
}
