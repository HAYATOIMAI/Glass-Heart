
/*****************************************************************//**
 * @file   StateBase.cpp
 * @brief  ��Ԃ̊��N���X
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
