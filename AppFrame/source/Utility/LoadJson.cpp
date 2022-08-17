#include "LoadJson.h"
#ifdef _DEBUG
#include <Windows.h>
#include <stdexcept>
#endif // _DEBUG

namespace {
	constexpr	auto json = ".json";
}

namespace AppFrame {

	namespace Utility {
		LoadJson::~LoadJson()	{}

		std::unordered_map<std::string, nlohmann::json> LoadJson::GetParameter(std::filesystem::path path, std::vector<std::string_view> fileName) {

			// ファイルの拡張子が.jsonでない場合はreturnを返す
			if (path.extension() != json) {
				return;
			}
			// データを格納しているフォルダへのパスを取得
			auto jsonPath = (GetFilePath() / path).generic_string() + json;

			// ファイルを読み取り専用で開く
			std::ifstream reading(jsonPath, std::ios::in);

#ifdef _DEBUG
			try {
				if (reading.fail()) {
					auto error = "-----------" + jsonPath + "Failed to open this file." + "-----------\n";
					throw std::logic_error(error);
				}
			}
			catch (const std::logic_error& e)	{
				OutputDebugString(e.what());
			}
#endif // _DEBUG

			// ファイルが存在しない場合はreturnを返す
			if (reading.fail()) {
				return;
			}

			nJson value;
			// ファイルの中身を取り出す
			reading >> value;
			// ファイルを閉じる
			reading.close();

			auto paramArray = value[path.generic_string()];

			std::unordered_map<std::string, nJson> paramMap;

			paramMap.clear();

			for (auto i = 0; i < fileName.size(); ++i) {
				for (auto&& paramData : paramArray) {
					const auto param = paramData[fileName[i].data()];
					paramMap.emplace(fileName[i], param);
				}
			}
			return paramMap;
		}
	}
}
