/*****************************************************************//**
 * @file   IsHitBDeathMesh.h
 * @brief  死亡判定をとる黒いメッシュとの当たり判定クラスの宣言
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
 /**
  * @namespace GlassHeart
  * @brief     プロジェクト名
  */
namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }
  /**
   * @namespace Collision
   * @brif      衝突判定関係
   */
  namespace Collision {
    /**
     * @class IsHitBDeathMesh
     * @brief 死亡判定をとる黒いメッシュとの当たり判定クラス
     */
    class IsHitBDeathMesh {
    public:
      /**
       * @                コンストラクタ
       *
       * @param[in] owner 親クラスへの参照
       */
      IsHitBDeathMesh(Object::ObjectBase& owner);
      /**
       * @brief             死亡判定をとる黒いメッシュとの当たり判定
       *
       * @param[in] pos     位置ベクトル
       * @param[in] forward 移動量ベクトル
       * @return            位置ベクトル
       */
      VECTOR CheckHitBDeathMesh(const VECTOR& pos, const VECTOR& forward);

      inline MV1_COLL_RESULT_POLY_DIM GetBDeathMesh() const { return _bDeath; }
    private:
      Object::ObjectBase& _owner;        //!< 親クラスへの参照
      MV1_COLL_RESULT_POLY_DIM _bDeath;  //!< 黒いデスメッシュとの当たり判定用変数
    };
  }
}