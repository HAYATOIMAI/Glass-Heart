/*****************************************************************//**
 * @file   EffectServer.cpp
 * @brief  エフェクト管理クラスの処理
 *
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#include"EffectServer.h"

using namespace GlassHeart;

Effect::EffectServer::EffectServer(GameMain& game) : _game(game) {
	Initialize();
}

Effect::EffectServer::~EffectServer() {

}

void Effect::EffectServer::Initialize() {
	Clear();
}

void Effect::EffectServer::Clear() {
	_effects.clear();
}

void Effect::EffectServer::LoadEffect(std::string_view key, std::string_view filename, float magnification) {
	if (_effects.contains(key.data())) {
		return;
	}
	std::string loadfilename = (_currentdirectory / filename.data()).generic_string();
	auto handle = LoadEffekseerEffect(loadfilename.data(), magnification);
	_effects.emplace(key, handle);
}

void Effect::EffectServer::LoadEfeects(const EffectMap& effectmap) {
	for (auto&& [key,filename_mag]:effectmap) {
		auto [filename, mag] = filename_mag;
		filename = (_currentdirectory / filename).generic_string();
		LoadEffect(key, filename, mag);
	}
}

void Effect::EffectServer::ChangeCurrentFile(std::string_view path){
	_currentdirectory = path;
}

int Effect::EffectServer::GetEffectResHandle(std::string_view key){
	auto handle = _effects[key.data()];
	return handle;
}

bool Effect::EffectServer::GetEffectResContein(std::string_view key) {
	if (_effects.contains(key.data())) {
		return true;
	}
	return false;
}
