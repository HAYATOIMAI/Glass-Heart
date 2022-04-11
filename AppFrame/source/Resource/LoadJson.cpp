
#include "LoadJson.h"
#include <fstream>
#include <string_view>
#include <DxLib.h>

std::unordered_map<std::string, nlohmann::json> AppFrame::LoadJson::GetParameter(const FilePath jsonName, const std::vector<std::string_view> parameter) {
	//json�t�@�C�����i�[����Ă���t�@�C���̃p�X���擾
	auto file = GetFilePath();
	
	auto jsonPath = (file/jsonName).generic_string() + ".json";
	// json�t�@�C�����J��
	std::ifstream read(jsonPath.c_str(), std::ios_base::in);

	// �t�@�C�����J���̂Ɏ��s
	if (read.fail()) {
		printfDx("---Json�t�@�C�����J���܂���ł���---\n");
	}

	nlohmann::json value;
	// �t�@�C���̒��g���擾
	read >> value;
	// �t�@�C�������
	read.close();
	// �z��̃L�[����������w�肵�Ď擾
	auto jsonArray = value[jsonName.generic_string()];
	// �f�[�^���i�[����ׂ̘A�z�z��
	ParamMap paramMap;
	// �����̕�����̃R���e�i�����ׂď���
	for (auto i = 0; i < parameter.size(); ++i) {
		// �����̕�����ƈ�v���Ă���f�[�^���擾
		for (auto& itr : jsonArray) {
			auto param = itr[parameter[i].data()];
			// ��v���Ă��镶������L�[�ɁAnlhomann::json�^�f�[�^��A�z�z��ɓo�^
			paramMap.emplace(parameter[i], param);
		}
	}
	// �f�[�^��o�^�����A�z�z���Ԃ�
	return  paramMap;
}
