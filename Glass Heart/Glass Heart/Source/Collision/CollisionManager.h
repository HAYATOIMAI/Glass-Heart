/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  コリジョンマネージャークラスの宣言
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include "IsHitFloor.h"
#include "IsHitJumpStand.h"
#include "IsHitSideAndBottom.h"
#include "IsHitWDeathMesh.h"
#include "IsHitBDeathMesh.h"
#include "IsHitCircleToCircle.h"
 /**
  * @namespace GlassHeart
  * @brief プロジェクト名
  */
namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }
  /**
   * @namespace Collision
   * @brief 衝突判定
   */
  namespace Collision {
    /**
     * @class CollisionManager
     * @brief 衝突判定管理用クラス
     */
    class CollisionManager {
    public:
      /**
       * @brief　コンストラクタ
       *
       * @param[in] owner　オブジェクトベースクラスへの参照
       */
      CollisionManager(GlassHeart::Object::ObjectBase& owner);
      /**
       * @ 床との当たり判定のゲッター
       * 
       * @return 床との当たり判定の参照
       */
      inline IsHitFloor& GetIsHitFloor() { return _isHitFloor; }
      /**
       * @ ジャンプした際の床との当たり判定のゲッター
       * 
       * @return ジャンプした際の床との当たり判定の参照
       */
      inline IsHitJumpStand& GetIsHitJumpStand() { return _isHitJumpStand; }
      /**
       * @ 空中に存在している足場の底面と側面の当たり判定のゲッター
       * 
       * @return 底面と側面の当たり判定の参照
       */
      inline IsHitSideAndBottom& GetIsHitSideBottom() { return _isHitSideBottom; }
      /**
       * @ 死亡判定をとる白いメッシュのゲッター
       * 
       * @return 死亡判定をとる白いメッシュの参照
       */
      inline IsHitWDeathMesh& GetIsHitWDeathMesh() { return _isHitWDeathMesh; }
      /**
       * @ 死亡判定をとる黒いメッシュのゲッター
       * 
       * @return 死亡判定をとる黒いメッシュのの参照
       */
      inline IsHitBDeathMesh& GetIsHitBDeathMesh() { return _isHitBDeathMesh; }
      /**
       * @ 円と円の衝突判定クラスのゲッター
       * 
       * @return 円と円の衝突判定 の参照
       */
      inline IsHitCircleToCircle& GetIsHitCircle() { return _isHitCircle; }
    private:
      Object::ObjectBase&  _owner;            //!< 親クラスへの参照
      IsHitFloor           _isHitFloor;       //!< 床との当たり判定クラスの参照
      IsHitJumpStand       _isHitJumpStand;   //!< ジャンプした際の床との当たり判定の参照
      IsHitSideAndBottom   _isHitSideBottom;  //!< 空中に存在している足場の底面と側面の当たり判定の参照
      IsHitWDeathMesh      _isHitWDeathMesh;  //!< 死亡判定をとる白いメッシュの参照
      IsHitBDeathMesh      _isHitBDeathMesh;  //!< 死亡判定をとる黒いメッシュの参照
      IsHitCircleToCircle  _isHitCircle;      //!< 円状の当たり判定クラスの参照
    };
  } // namespce Collision
} // namespace GlassHeart