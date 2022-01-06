
/*****************************************************************//**
 * @file   GameMain.h
 * @brief  このプロジェクトのメイン処理
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "AppFrame.h"

namespace GlassHeart {
	
	namespace Object {
		/** 二重インクルード防止 */
		class ObjectServer;
		class ObjectFactory;
	}
	/**
	 * @class GameMain
	 * @brief このプロジェクトのメイン処理
	 */
	class GameMain : public AppFrame::GameBase {
		using base = AppFrame::GameBase;
	public:
		GameMain();
		virtual ~GameMain() override;
		/**
		 * @brief  初期化処理
		 *
		 * @return 初期化成功の可否
		 */
		virtual bool Initialize(HINSTANCE hInstance) override;
		/**
		 *  @brief 解放処理
		 */
		virtual void Terminate() override;
		/**
		 * @brief 入力処理
		 */
		virtual void Input() override;
		/**
		 * @brief 更新処理
		 */
		virtual void Process() override;
		/**
		 * @brief 描画処理
		 */
		virtual void Render() override;
		/**
		 * @brief メインループ
		 */
		virtual void Run() override;

		Object::ObjectServer& GetObjectServer() const { return *_objServer; }

		Object::ObjectFactory& GetObjectFactory() const { return *_objFactory; }

	private:
		std::unique_ptr<GlassHeart::Object::ObjectServer> _objServer;  //!< オブジェクトサーバーのユニークポインタ
		std::unique_ptr<GlassHeart::Object::ObjectFactory> _objFactory;	 //!< オブジェクトファクトリーのユニークポインタ
	};
}