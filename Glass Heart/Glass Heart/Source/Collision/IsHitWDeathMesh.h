/*****************************************************************//**
 * @file   IsHitWDeathMesh.h
 * @brief  死亡判定をとる白いメッシュとの当たり判定クラスの宣言
 * 
 * @author HAYATO IMAI
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }

  namespace Collision {
    class IsHitWDeathMesh {
    public:
      /**
       * @ コンストラクタ
       * 
       * @param[in] owner 親クラスへの参照
       */
      IsHitWDeathMesh(Object::ObjectBase& owner);
      /**
       * @brief 死亡判定をとる白いメッシュとの当たり判定
       *
       * @param[in] pos 位置ベクトル
       * @param[in] forward 移動量ベクトル
       * @return 位置ベクトル
       */
      VECTOR CheckHitWDeathMesh(const VECTOR& pos, const VECTOR& forward);

      inline MV1_COLL_RESULT_POLY_DIM GetWDeathMesh() { return _wDeath; }
    private:
      Object::ObjectBase& _owner;        //!< 親クラスへの参照
      MV1_COLL_RESULT_POLY_DIM _wDeath;  //!< 死亡判定をとる白いメッシュとの当たり判定用変数
    };
  }
}