/*****************************************************************//**
 * @file   ObjectBase.h
 * @brief  オブジェクトの基底クラス
 *
 * @author Hayato Imai, Yoshihiro Takahashi
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <memory>
#include <numbers>

namespace {
  constexpr VECTOR Position = { 0.0f, 0.0f, 0.0f };
  constexpr VECTOR Rotation = { 0.0f, 0.0f, 0.0f };
  constexpr VECTOR Scale = { 1.0f, 1.0f, 1.0f };

}
/**
 * @namespace AppFrame
 * @brief     フレームワーク
 */
namespace AppFrame {
  namespace Resource {
    class ResourceServer;
  }
  namespace Input {
    class InputManager;
  } // namespace
}
/**
 * @namespace GlassHeart
 * @brief プロジェクト名
 */
namespace GlassHeart {
  namespace Application {
    class GameMain;
  }
  namespace Collision {
    class CollisionManager;
  }
  namespace Model {
    class ModelAnimeManager;
  }
  namespace Camera {
    class CameraManager;
  }
  namespace State {
    class StateManager;
  }
  namespace UI {
    class UI;
  } // namespace
  /**
   * @namespace Object
   * @brief     オブジェクト関係
   */
  namespace Object {
    class ObjectServer;
    class ObjectFactory;
    /**
     * @class ObjectBase
     * @brief オブジェクトの基底クラス
     */
    class ObjectBase {
    public:
      /**
      * @brief　オブジェクトの種類
      */
      enum class ObjectType {
        Object = 0,
        Player,
        Girl,
        Camera,
        Stage,
        CheckPoint,
        GoalPoint
      };
      /**
       * @brief オブジェクトの状態
       */
      enum class ObjectState {
        Active,              //!< 生存
        Pause,               //!< 停止
        Dead                 //!< 死亡
      };
      /**
       * @brief              コンストラクタ
       *                     
       * @param[in] game     ゲームメインクラスへの参照
       */
      ObjectBase(Application::GameMain& game);
      /**
       * @brief              デストラクタ
       *
       */
      virtual ~ObjectBase();
      /**
       * @brief              初期化処理
       */
      virtual	void Init() {};
      /**
       * @brief              入力処理
       *                     
       * @param[in] input    インプットマネージャークラスの参照
       */
      virtual	void Input(AppFrame::Input::InputManager& input) {};
      /**
       * @brief              更新処理
       */
      virtual	void Process() {};
      /**
       * @brief              描画処理
       */
      virtual	void Render() {};
      /**
       * @brief　            オブジェクトの種類を取得
       *                     
       * @return             オブジェクトの種類
       */
      virtual ObjectType GetObjectType() const = 0;
      /**
       * @brief              死亡状態になっているか
       *                     
       * @return             オブジェクトの状態
       */
      inline bool IsDead() const { return (_objectState == ObjectState::Dead); }
      /**
       * @brief              生存状態になっているか
       *                     
       * @return             オブジェクトの状態
       */
      inline bool IsActive() const { return (_objectState == ObjectState::Active); }
      /**
       * @brief              ワールド座標変換
       */
      virtual void ComputeWorldTransform();
      /**
       * @brief              カメラから見て右方向の向きを取得
       *                     
       * @return             右方向の向き
       */
      inline float RightRotation() const { return 90.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @brief              カメラから見て左方向の向きを取得
       *                     
       * @return             左方向の向き
       */
      inline float LeftRotation() const { return 270.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @brief              ゲームメインクラスを取得する
       *                     
       * @return             ゲームメインクラスの参照
       */
      inline Application::GameMain& GetGame() const { return _game; }
      /**
       * @brief              ワールド座標を取得する
       *                     
       * @return             オブジェクトのワールド座標
       */
      inline const MATRIX& GetWorldTransform() const { return _worldTransform; }
      /**
       * @brief              前方ベクトルを取得する
       *                     
       * @return             オブジェクトの前方ベクトル
       */
      inline VECTOR GetForward() const { return VTransform({ 0.0f, 0.0f, 1.0f }, MGetRotY(_rotation.y)); }
      /**
       * @brief              オブジェクトの位置座標をセットする
       *                     
       * @param[in] position セットする位置座標
       */
      inline void SetPosition(const VECTOR& position) { _position = position; }
      /**
       * @brief              オブジェクトの位置座標のを取得する
       *                     
       * @return             取得したオブジェクトの位置座標
       */
      inline VECTOR GetPosition() const { return _position; }
      /**
       * @brief              オブジェクトの角度をセットする
       *                     
       * @param[in] rotation セットするオブジェクトの角度
       */
      inline void SetRotation(const VECTOR& rotation) { _rotation = rotation; }
      /**
       * @brief              オブジェクトの角度を取得する
       *                     
       * @return             取得したオブジェクトの角度
       */
      inline VECTOR GetRotation() const { return _rotation; }
      /**
       * @brief              オブジェクトの拡大率をセットする
       *                      
       * @param[in] scale    セットするオブジェクトの拡大率
       */
      inline void SetScale(const VECTOR& scale) { _scale = scale; }
      /**
       * @brief              オブジェクトの拡大率を取得する
       *                     
       * @return             取得したオブジェクトの拡大率
       */
      inline VECTOR GetScale() const { return _scale; }
      /**
       * @brief              円と円の当たり判定用半径をセットする
       *                     
       * @param[in] radius   セットする半径の大きさ
       */                                               
      inline void SetRadius(const float radius) { _radius = radius; }
      /**
       * @brief              円と円の当たり判定用半径を取得する
       *                     
       * @return             取得した半径を返す
       */
      inline float GetRadius() const { return _radius; }
      /**
       * @brief              死亡判定をとるメッシュに当たったかのフラグをセットする
       *                     
       * @param[in] hitFlag  セットするフラグ
       */
      inline void SetHitFlag(const bool hitFlag) { _hitFlag = hitFlag; }
      /**
       * @brief              死亡判定をとるメッシュに当たったかのフラグを取得する
       *                     
       * @return             当たったかのフラグを返す
       */
      inline bool GetHitFlag() const { return _hitFlag; }
      /**
       * @brief              死亡したのかのフラグを取得する
       *                     
       * @return             死亡したのかのフラグを返す
       */
      inline bool GetDeadFlag() const { return _deadFlag; }
      /**
       * @brief              ステートマネージャーを取得する
       *                     
       * @return             ステートマネージャーの参照
       */
      inline State::StateManager& GetStateManage() const { return *_stateManage; }
      /**
       * @brief              コリジョンマネージャーを取得する
       *                     
       * @return             コリジョンマネージャーの参照
       */
      inline Collision::CollisionManager& GetCollision() const { return *_collsionManage; }
      /**
       * @brief              カメラマネージャーを取得する
       *                     
       * @return             カメラマネージャーの参照
       */
      inline Camera::CameraManager& GetCamera() const { return *_cameraManage; }
      /**
       * @brief              モデルアニメマネージャーを取得する
       *                     
       * @return             モデルアニメマネージャーの参照
       */
      inline Model::ModelAnimeManager& GetModelAnime() const { return *_modelAnimeManage; }
      /**
       * @brief              ステートマネージャーをセットする
       *                     
       * @param[in] state    ステートマネージャーのユニークポインタ
       */
      void SetStateManage(std::unique_ptr<State::StateManager> state);
      /**
       * @brief              モデルアニメマネージャーをセットする
       *                     
       * @param[in] model    モデルアニメマネージャーのユニークポインタ
       */
      void SetModelManage(std::unique_ptr<Model::ModelAnimeManager> model);
      /**
       * @brief              カメラマネージャーをセットする
       *                     
       * @param[in] camera   カメラマネージャーのシェアードポインタ
       */
      void SetCameraManage(std::shared_ptr<Camera::CameraManager> camera);
      /**
       * @brief              オブジェクト管理するマネージャーを取得する
       *
       * @return             オブジェクトサーバーの参照
       */
      ObjectServer& GetObjectServer();
    protected:
      /**
       * @brief              オブジェクトのステートを取得する
       *                     
       * @return             オブジェクトのステート
       */
      inline ObjectState GetObjectState() const { return _objectState; }
      /**
       * @brief              オブジェクトのステートをセットする
       *                     
       * @param[in] objstate オブジェクトのステート
       */
      inline void SetObjectState(const ObjectState objstate) { _objectState = objstate; }
      /** ステートマネージャーのユニークポインタ */
      std::unique_ptr<State::StateManager> _stateManage{ nullptr };
      /** コリジョンマネージャーのシェアードポインタ */
      std::shared_ptr<Collision::CollisionManager> _collsionManage{ nullptr };
      /** カメラマネージャーのシェアードポインタ */
      std::shared_ptr<Camera::CameraManager> _cameraManage{ nullptr };
      /** モデルアニメマネージャーのユニークポインタ */
      std::unique_ptr<Model::ModelAnimeManager> _modelAnimeManage{ nullptr };
      Application::GameMain& _game;                     //!< ゲームメインクラスの参照
      bool _deadFlag{ false };                          //!< 死亡したかのフラグ
      bool _hitFlag{ false };                           //!< コリジョン用フラグ
      float _radius{ 0.0f };                            //!< コリジョン用半径
      MATRIX _worldTransform{ MGetIdent() };            //!< ワールド座標変換
      VECTOR _position{ Position };                     //!< 位置情報
      VECTOR _rotation{ Rotation };                     //!< 角度
      VECTOR _scale{ Scale };                           //!< 拡大率
      ObjectState _objectState{ ObjectState::Active };  //!< オブジェクトのステート
    };
  } // namespace Object
} // namespace GlassHeart