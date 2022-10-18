/*****************************************************************//**
 * @file   ObjectFactory.h
 * @brief  オブジェクトファクトリークラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <DxLib.h>
 /**
  * @namespace GlassHeart
  * @brief プロジェクト名
  */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  /**
   * @namespace Object
   * @briefオブジェクト関係
   */
  namespace Object {
    class CreateBase;
    class ObjectBase;
    /**
     * @class ObjectFactory
     * @brief オブジェクトの生成を一元管理する
     *        生成したいオブジェクト用のクリエイターを登録して使用する
     */
    class ObjectFactory {
    public:
      /**
       * @brief コンストラクタ
       *
       * @param[in] game  ゲームメインクラスへの参照
       */
      ObjectFactory(Application::GameMain& game);
      /**
       * @brief クリエイターの登録
       *
       * @param[in] type     文字列キー
       * @param[in] creator  登録するクリエイターのインスタンス
       * @return  登録の成否
       */
      bool Register(std::string_view type, std::unique_ptr<CreateBase> creator);
      /**
       * @brief オブジェクトの生成
       *
       * @param[in] type 文字列キー
       * @return      生成したインスタンスのポインタ
       */
      std::unique_ptr<ObjectBase> Create(std::string_view type);
      /**
       * @brief 全オブジェクト消去
       *
       */
      void Clear();
    private:
      //!< ゲームメインクラスへの参照
      Application::GameMain& _game; 
      //!< 生成したいオブジェクト用のクリエイターマップ
      std::unordered_map<std::string, std::unique_ptr<CreateBase>> _creatorMap;
    };
    class CreateBase {
    public:
      virtual ~CreateBase() = default;
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game) = 0;
    protected:
    };
    /**
     * @class PlayerCreate
     * @brief プレイヤー用のクリエイター
     */
    class PlayerCreate : public CreateBase {
    public:
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game);
    };
    /**
   * @class GirlCreate
   * @brief ガール用のクリエイター
   */
    class GirlCreate : public CreateBase {
    public:
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game);
    };
    /**
     * @class StageCreate
     * @brief ステージ用のクリエイター
     */
    class StageCreate : public CreateBase {
    public:
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game);
    };
    /**
   * @class FollowCameraCreate
   * @brief フォローカメラ用のクリエイター
   */
    class FollowCameraCreate : public CreateBase {
    public:
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game);
    };

    /**
    * @class CheckPointCreate
    * @brief チェックポイント用のクリエイター
    */
    class CheckPointCreate : public CreateBase {
    public:
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game);
    };
    /**
   * @class GoalPointCreate
   * @brief ゴールポイント用のクリエイター
   */
    class GoalPointCreate : public CreateBase {
    public:
      virtual std::unique_ptr<ObjectBase> Create(Application::GameMain& game);
    };
  } // namespace Object
} // namespace GlassHeart