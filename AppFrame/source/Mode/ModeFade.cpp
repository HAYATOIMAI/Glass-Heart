/*****************************************************************//**
 * @file   ModeFade.cpp
 * @brief  モードのフェードクラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ModeFade.h"
#include "ModeServer.h"
#include <DxLib.h>

namespace AppFrame {

	namespace Mode {
		/** コンストラクタ */
		ModeFade::ModeFade(GameBase& game) : ModeBase{ game }, _color{ GetColor(0, 0, 0) }{}
		/** デストラクタ */
		ModeFade::~ModeFade() {}
		/** 初期化処理 */
		void ModeFade::Init() {
			_color = GetColor(0, 0, 0);
		}
		/** 入り口処理 */
		void ModeFade::Enter() {}
		/** 更新処理 */
		void ModeFade::Process() {}
		/** 描画処理 */
		void ModeFade::Render() {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
			DrawBox(0, 0, _width, _height, _color, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	} // namespace Mode
} // namespace AppFrame