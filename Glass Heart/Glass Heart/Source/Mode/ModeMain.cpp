/*****************************************************************//**
 * @file   ModeMain.cpp
 * @brief  モードの基底クラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeMain.h"
#include "../Application/GameMain.h"
 /** コンストラクタ */
GlassHeart::Mode::ModeMain::ModeMain(Application::GameMain& game) : AppFrame::Mode::ModeBase{ game }, _gameMain{ game } {
  _count = 0;
  _countSeconds = 0;
  _fadeCount = 0;
}

GlassHeart::Object::ObjectFactory& GlassHeart::Mode::ModeMain::GetObjectFactory() {
  return _gameMain.GetObjectFactory();
}

GlassHeart::Object::ObjectServer& GlassHeart::Mode::ModeMain::GetObjectServer() {
  return _gameMain.GetObjectServer();
}

GlassHeart::UI::UI& GlassHeart::Mode::ModeMain::GetUI() {
  return _gameMain.GetUI();
}