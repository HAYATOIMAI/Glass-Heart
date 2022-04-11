
#pragma once
#include <nlohmann/json.hpp>

namespace AppFrame {
	/**
	 * @class LoadJson
	 * @brief Jsonファイルから各種データを取得するクラスの宣言
	 */
	class LoadJson {
	public:
		/**
		 * @brief コンストラクタ
		 */
		LoadJson() {};
		/**
		 * @brief デストラクタ
		 */
		~LoadJson() {};

		using ParamMap = std::unordered_map<std::string, nlohmann::json>;
		using FilePath = std::filesystem::path;
		/**
		 * @brief 
		 * 
		 * @param[in] jsonName　jsonファイル名
		 * @param[in] parameter 登録するパラメータのコンテナ
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