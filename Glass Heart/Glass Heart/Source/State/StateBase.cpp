
/*****************************************************************//**
 * @file   StateBase.cpp
 * @brief  状態の基底クラス
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "StateBase.h"
#include "../Player/Player.h"
#include "../Model/ModelAnimeManager.h"

using namespace GlassHeart::State;

void StateBase::Draw() {
	_owner.GetModelAnime().MeshDraw();
}
