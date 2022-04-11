
#pragma once
#include <nlohmann/json.hpp>

namespace AppFrame {
	/**
	 * @class LoadJson
	 * @brief Json�t�@�C������e��f�[�^���擾����N���X�̐錾
	 */
	class LoadJson {
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		LoadJson() {};
		/**
		 * @brief �f�X�g���N�^
		 */
		~LoadJson() {};

		using ParamMap = std::unordered_map<std::string, nlohmann::json>;
		using FilePath = std::filesystem::path;
		/**
		 * @brief 
		 * 
		 * @param[in] jsonName�@json�t�@�C����
		 * @param[in] parameter �o�^����p�����[�^�̃R���e�i
		 * @return 
		 */
		static std::unordered_map<std::string, nlohmann::json> GetParameter(const FilePath jsonName, 
			const std::vector<std::string_view> parameter);

	private:
		static FilePath GetFilePath() {
			auto filePath = "resource/Json/";
			return filePath;
		}
	};
} // namespace AppFrame