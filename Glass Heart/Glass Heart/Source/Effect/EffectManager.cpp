/*****************************************************************//**
 * @file   EffectManager.cpp
 * @brief  エフェクト再生管理クラス
 * 
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#include "EffectManager.h"
#include "EffectServer.h"
#include "../Object/ObjectBase.h"

using namespace GlassHeart;

Effect::EffectManager::EffectManager(Object::ObjectBase& owner) : _owner(owner){
	
}

Effect::EffectManager::~EffectManager() {

}

void Effect::EffectManager::Init() {

}

void Effect::EffectManager::Update() {
	//Effekseer_Sync3DSetting();
	//UpdateEffekseer3D();
}

void Effect::EffectManager::Render(){
	//DrawEffekseer3D();
}

void Effect::EffectManager::Play(std::string_view key, VECTOR position, VECTOR rotation){
	/*if (_owner.GetGame().GetEffectServer().GetEffectResContein(key)) {
		auto handle = _owner.GetGame().GetEffectServer().GetEffectResHandle(key);
		auto nowplayhandle = PlayEffekseer3DEffect(handle);
		auto& [x, y, z] = position;
		SetPosPlayingEffekseer3DEffect(nowplayhandle, x, y, z);
		auto& [rx, ry, rz] = rotation;
		SetRotationPlayingEffekseer3DEffect(nowplayhandle, rx, ry, rz);
		_nowplayeffects.push_back(nowplayhandle);
	}*/
}
