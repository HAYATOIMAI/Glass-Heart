
#include "LoadJson.h"
#include <fstream>
#include <string_view>
#include <DxLib.h>

std::unordered_map<std::string, nlohmann::json> AppFrame::LoadJson::GetParameter(const FilePath jsonName, const std::vector<std::string_view> parameter) {
	//jsonファイルが格納されているファイルのパスを取得
	auto file = GetFilePath();
	
	auto jsonPath = (file/jsonName).generic_string() + ".json";
	// jsonファイルを開く
	std::ifstream read(jsonPath.c_str(), std::ios_base::in);

	// ファイルを開くのに失敗
	if (read.fail()) {
		printfDx("---Jsonファイルを開けませんでした---\n");
	}

	nlohmann::json value;
	// ファイルの中身を取得
	read >> value;
	// ファイルを閉じる
	read.close();
	// 配列のキーを引数から指定して取得
	auto jsonArray = value[jsonName.generic_string()];
	// データを格納する為の連想配列
	ParamMap paramMap;
	// 引数の文字列のコンテナをすべて処理
	for (auto i = 0; i < parameter.size(); ++i) {
		// 引数の文字列と一致しているデータを取得
		for (auto& itr : jsonArray) {
			auto param = itr[parameter[i].data()];
			// 一致している文字列をキーに、nlhomann::json型データを連想配列に登録
			paramMap.emplace(parameter[i], param);
		}
	}
	// データを登録した連想配列を返す
	return  paramMap;
}
