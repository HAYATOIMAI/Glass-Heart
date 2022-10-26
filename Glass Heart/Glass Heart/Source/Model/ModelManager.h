/*****************************************************************//**
 * @file   ModelManager.h
 * @brief  モデルマネージャークラスの宣言
 *
 * @author Hayato Imai, Haruki Ikeda
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <string_view>
#include <cstdint>
 /**
  * @namespace GlassHeart
  * @brief プロジェクト名
  */
namespace GlassHeart {
  namespace Object {
    class ObjectBase;
  }
  /**
   * @namespace Model
   * @brief     モデル関係
   */
  namespace Model {
    /**
     * @class ModelManager
     * @brief モデルマネージャークラスの宣言
     */
    class ModelManager {
    public:
      /**
       * @brief              コンストラクタ
       *
       * @param[in] owner    オブジェクトベースクラスへの参照
       */
      ModelManager(GlassHeart::Object::ObjectBase& owner);
      /**
       * @brief              デストラクタ
       */
      virtual ~ModelManager();
      /**
       * @brief              初期化
       */
      virtual void Init();
      /**
       * @brief              更新処理
       */
      virtual void Update();
      /**
       * @brief              描画処理
       */
      virtual void Draw();
      /**
       * @brief              モデルの取得
       *                                 
       * @param[in] key      ResourceServerに登録済みのキー
       * @param[in] no       同一モデルの通し番号
       * @return             モデルの情報
       */
      virtual std::int_fast32_t handle(std::string_view key, int no = 0);
      /**
       * @brief              モデルの設定
       *                                
       * @param[in] key      ResourceServerに登録済みのキー
       * @param[in] no       同一モデルの通し番号
       * @return             実際に登録した通し番号
       */
      virtual std::int_fast32_t SetModel(std::string_view key, int no = 0);
      /**
       * @brief              座標の設定
       *                               
       * @param[in] position 座標x,y,z
       */
      virtual void SetPosition(VECTOR position);
      /**
       * .@brief             回転角度の設定
       *                     
       * @param[in] rotation 回転角度x,y,z
       */
      virtual void SetRotation(VECTOR rotation);
      /**
       * @brief              拡大率の設定
       *                     
       * @param[in] scale    拡大率
       */                    
      virtual void SetScale(VECTOR scale);
      /**
       * @brief              ワールド行列の設定
       *                     
       * @param[in] world    ワールド座標
       */
      virtual void SetMatrix(MATRIX& world);
      /**
       * @brief              グラフィックハンドルをセットする
       * 
       * @param[in] handle   セットするグラフィックハンドル
       */
      inline void SetHandle(const std::int_fast32_t handle) { _handle = handle; }
      /**
       * @brief              グラフィックハンドルを取得する
       * 
       * @return             グラフィックハンドル
       */
      inline std::int_fast32_t GetHandle() const { return _handle; }
      /**
       * @brief              モデルのカラーをセットする
       * 
       * @param[in] index    通し番号
       * @param[in] r        赤色のカラー値
       * @param[in] g        緑色のカラー値
       * @param[in] b        青色のカラー値
       */
      void SetColor(std::int_fast32_t index, float r, float g, float b);
    protected:
      Object::ObjectBase& _owner;       //!< オブジェクトベースクラスへの参照
      std::int_fast32_t _handle{ -1 };  //!< モデル用ハンドル
      std::string _key{ "" };           //!< 文字列
      bool _isLighting{ true };         //!< ライティング処理をするかのフラグ
    };
  } //  namespace Model
} // namespace GlassHeart