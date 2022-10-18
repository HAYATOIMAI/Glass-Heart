#pragma once
#include "Singleton.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <unordered_map>
#include <fstream>

namespace AppFrame {

	namespace Utility {

		class LoadJson : public Singleton<LoadJson> {
		private:
			LoadJson();
			~LoadJson() override;
		public:
			friend class Singleton<LoadJson>;

			using nJson = nlohmann::json;

			std::unordered_map<std::string, nlohmann::json> GetParameter(std::filesystem::path path, std::vector<std::string_view> fileName);

		private:
			//!< 格納フォルダへのパス
			inline std::filesystem::path GetFilePath() {
				auto currentPath = "resource/json/";
				return currentPath;
			}
		};
	}
}
