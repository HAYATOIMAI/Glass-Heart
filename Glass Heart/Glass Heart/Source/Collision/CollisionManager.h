/*****************************************************************//**
 * @file   CollisionManager.h
 * @brief  コリジョンマネージャークラスの宣言
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <DxLib.h>
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
       * @return 
       */
      inline IsHitFloor& GetIsHitFloor() { return _isHitFloor; }
      /**
       * @ ジャンプした際の床との当たり判定のゲッター
       * 
       * @return 
       */
      inline IsHitJumpStand& GetIsHitJumpStand()      { return _isHitJumpStand; }
      /**
       * @ 空中に存在している足場の底面と側面の当たり判定のゲッター
       * 
       * @return 
       */
      inline IsHitSideAndBottom& GetIsHitSideBottom() { return _isHitSideBottom; }
      /**
       * @ 死亡判定をとる白いメッシュのゲッター
       * 
       * @return 
       */
      inline IsHitWDeathMesh& GetIsHitWDeathMesh()    { return _isHitWDeathMesh; }
      /**
       * @ 死亡判定をとる黒いメッシュのゲッター
       * 
       * @return 
       */
      inline IsHitBDeathMesh& GetIsHitBDeathMesh()    { return _isHitBDeathMesh; }
      /**
       * @ 円状の当たり判定クラスの参照
       * 
       * @return 
       */
      inline IsHitCircleToCircle& GetIsHitCircle()    { return _isHitCircle; }
    private:
      Object::ObjectBase&  _owner;            //!< 親クラスへの参照
      IsHitFloor           _isHitFloor;       //!< 床との当たり判定クラスの参照
      IsHitJumpStand       _isHitJumpStand;   //!< 
      IsHitSideAndBottom   _isHitSideBottom;  //!<
      IsHitWDeathMesh      _isHitWDeathMesh;  //!<
      IsHitBDeathMesh      _isHitBDeathMesh;  //!<
      IsHitCircleToCircle  _isHitCircle;      //!< 円状の当たり判定クラスの参照
    };
  } // namespce Collision
} // namespace GlassHeart