
/*****************************************************************//**
 * @file   Utility.cpp
 * @brief  
 * 
 * @author Hayato Imai
 * @date   January 2022
 *********************************************************************/
#include "Utility.h"
#include <cmath>
#include <random>
#include "Vector4.h"

namespace {
	std::random_device SeedGen;
	std::mt19937_64 random(SeedGen());
}


namespace AppFrame {

	int Utility::GetRandom(const int min, const int max) {
		std::uniform_int_distribution<int>  distr(min, max);

		return distr(random);
	}
}