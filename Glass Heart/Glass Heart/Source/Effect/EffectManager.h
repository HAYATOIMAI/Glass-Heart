/*****************************************************************//**
 * @file   EffectManager.h
 * @brief  エフェクト再生管理クラス宣言
 * 
 * @author Haruki Ikeda
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <DxLib.h>
#include <EffekseerForDXLib.h>

namespace GlassHeart {

	namespace Object{
		class ObjectBase;
	}

	namespace Effect {
		class EffectManager {
		public:
			EffectManager(Object::ObjectBase& owner);
			~EffectManager();
			void Init();
			void Update();
			void Render();
			void Play(std::string_view key, VECTOR position, VECTOR rotation);
		private:
			Object::ObjectBase& _owner;
			std::vector<int> _nowplayeffects;
		};
	}
}
