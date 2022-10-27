/*****************************************************************//**
 * @file   Stage.h
 * @brief  ステージクラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include "../Object/ObjectBase.h"
#include <memory>
 /**
  * @namespace GlassHeart
  * @brief プロジェクト名
  */
namespace GlassHeart {
  namespace Model {
    class ModelManager;
  }
  namespace Application {
    class GameMain;
  }
  /**
   * @namespace Stage
   * @brief     ステージ関係
   */
  namespace Stage {
    /**
     * @class Stage
     * @brief ステージクラス
     */
    class Stage : public Object::ObjectBase {
    public:
      /**
       * @brief          コンストラクタ
       *
       * @param[in] game ゲームメインクラスへの参照
       */
      Stage(Application::GameMain& game);
      /**
       * @brief          更新処理
       */
      virtual void Process() override;
      /**
       * @brief          描画処理
       */
      void Render() override;
      /**
       * @brief          オブジェクトの種類を取得する
       * 
       * @return         オブジェクトの種類
       */
      inline ObjectType GetObjectType() const override { return ObjectType::Stage; }
    private:
      /** スカイスフィア用ユニークポインタ */
      std::unique_ptr<Model::ModelManager> _backGround{ nullptr }; 
      /** ステージ用ユニークポインタ */
      std::unique_ptr<Model::ModelManager> _stage{ nullptr };
    };
  } // namespace Stage
} // namespace GlassHeart