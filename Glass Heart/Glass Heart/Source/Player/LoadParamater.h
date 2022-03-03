
/*********************************************************************
 * @file   LoadParamater.h
 * @brief  
 * 
 * @author Hayato Imai
 * @date   February 2022
 *********************************************************************/
#pragma once
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <string_view>

namespace GlassHeart {

	namespace Param {

		class LoadParamater {
		public:
			LoadParamater();
			~LoadParamater();

			using ParamMap = std::unordered_map<std::string, float>;

			//void LoadPlayerParameter(std::string_view key);

			void LoadPlayerParams(const ParamMap& para);

		private:
			std::unordered_map<std::string, float> _playerParam;
		};
	}
}



