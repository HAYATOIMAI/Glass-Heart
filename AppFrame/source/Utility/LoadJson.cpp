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

			// �t�@�C���̊g���q��.json�łȂ��ꍇ��return��Ԃ�
			if (path.extension() != json) {
				return;
			}
			// �f�[�^���i�[���Ă���t�H���_�ւ̃p�X���擾
			auto jsonPath = (GetFilePath() / path).generic_string() + json;

			// �t�@�C����ǂݎ���p�ŊJ��
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

			// �t�@�C�������݂��Ȃ��ꍇ��return��Ԃ�
			if (reading.fail()) {
				return;
			}

			nJson value;
			// �t�@�C���̒��g�����o��
			reading >> value;
			// �t�@�C�������
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
