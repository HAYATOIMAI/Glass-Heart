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

namespace AppFrame {
  namespace Resource {
    class ResourceServer;
  }
  namespace Input {
    class InputManager;
  }
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
   * @briefオブジェクト関係
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
        Active,
        Pause,
        Dead
      };
      /**
       * @brief コンストラクタ
       *
       * @param[in] game ゲームメインクラスへの参照
       */
      ObjectBase(Application::GameMain& game);
      /**
       * @brief デストラクタ
       *
       */
      virtual ~ObjectBase();
      /**
       * @brief 初期化処理
       */
      virtual	void Init() {};
      /**
       * @brief 入力処理
       *
       * @param[in] input インプットマネージャークラスの参照
       */
      virtual	void Input(AppFrame::Input::InputManager& input) {};
      /**
       * @brief 更新処理
       */
      virtual	void Process() {};
      /**
       * @brief 描画処理
       */
      virtual	void Render() {};
      /**
       * @brief　オブジェクトの種類を取得
       *
       * @return オブジェクトの種類
       */
      virtual ObjectType GetObjectType() const = 0;
      /**
       * @brief 死亡状態になっているか
       *
       * @return オブジェクトの状態
       */
      inline bool IsDead() { return (_objectState == ObjectState::Dead); }
      /**
       * @brief 生存状態になっているか
       *
       * @return  オブジェクトの状態
       */
      inline bool IsActive() { return (_objectState == ObjectState::Active); }
      /**
       * @brief ワールド座標変換
       */
      virtual void ComputeWorldTransform();
      /**
      * @ カメラから見て右方向の向きを取得
      *
      * @return 右方向の向き
      */
      float RightRotation() const { return 90.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @ カメラから見て左方向の向きを取得
       *
       * @return 左方向の向き
       */
      float LeftRotation() const { return 270.0f * (std::numbers::pi_v<float> / 180.0f); }
      /**
       * @ ゲームメインクラスの参照のゲッター
       * 
       * @return ゲームメインクラスの参照
       */
      inline Application::GameMain& GetGame() { return _game; }
      /**
       * @ ワールド座標のゲッター
       * 
       * @return 
       */
      inline const MATRIX& GetWorldTransform() const { return _worldTransform; }
      /**
       * @ 前方ベクトルを取得するゲッター
       * 
       * @return オブジェクトの前方ベクトル
       */
      inline VECTOR GetForward() const { return VTransform({ 0.0f, 0.0f, 1.0f }, MGetRotY(_rotation.y)); }
      /**
       * @ オブジェクトの位置座標をセットする
       * 
       * @param[in] position セットする位置座標
       */
      inline void SetPosition(const VECTOR& position) { _position = position; }
      /**
       * @ オブジェクトの位置座標のゲッター
       * 
       * @return 取得したオブジェクトの位置座標
       */
      inline VECTOR GetPosition() const { return _position; }
      /**
       * @ オブジェクトの角度をセットする
       * 
       * @param[in] rotation セットするオブジェクトの角度
       */
      inline void SetRotation(const VECTOR& rotation) { _rotation = rotation; }
      /**
       * @ オブジェクトの角度のゲッター
       * 
       * @return 取得したオブジェクトの角度
       */
      inline VECTOR GetRotation() const { return _rotation; }
      /**
       * @ オブジェクトの拡大率をセットする
       * 
       * @param[in] scale セットするオブジェクトの拡大率
       */
      inline void SetScale(const VECTOR& scale) { _scale = scale; }
      /**
       * @ オブジェクトの拡大率のゲッター
       * 
       * @return 取得したオブジェクトの拡大率
       */
      inline VECTOR GetScale() const { return _scale; }
      /**
       * @ 円と円の当たり判定用半径をセットする
       * 
       * @param[in] radius セットする半径の大きさ
       */
      inline void SetRadius(const float radius) { _radius = radius; }
      /**
       * @ 円と円の当たり判定用半径を取得する
       * 
       * @return 取得した半径
       */
      inline float GetRadius() const { return _radius; }
      /**
       * @ 死亡判定をとるメッシュに当たったかのフラグをセットする
       * 
       * @param[in] hitFlag セットするフラグ
       */
      inline void SetHitFlag(const bool hitFlag) { _hitFlag = hitFlag; }
      /**
       * @ 死亡判定をとるメッシュに当たったかのフラグのゲッター
       * 
       * @return 取得したフラグ
       */
      inline bool GetHitFlag() const { return _hitFlag; }
      /**
       * @ 死亡したのかのフラグのゲッター
       * 
       * @return 死亡したのかのフラグ
       */
      inline bool GetDeadFlag() { return _deadFlag; }
      /**
       * @ ステートマネージャーのゲッター
       * 
       * @return ステートマネージャーのユニークポインタ
       */
      inline State::StateManager& GetStateManage() { return *_stateManage; }
      /**
       * @ コリジョンマネージャーのゲッター
       * 
       * @return コリジョンマネージャーのシェアードポインタ
       */
      inline Collision::CollisionManager& GetCollision() { return *_collsionManage; }
      /**
       * @ カメラマネージャーのゲッター
       * 
       * @return カメラマネージャーのシェアードポインタ
       */
      inline Camera::CameraManager& GetCamera() { return *_cameraManage; }
      /**
       * @ モデルアニメマネージャーのゲッター
       * 
       * @return モデルアニメマネージャーのユニークポインタ
       */
      inline Model::ModelAnimeManager& GetModelAnime() { return *_modelAnimeManage; }
      /**
       * @ ステートマネージャーのセッター
       * 
       * @param[in] state ステートマネージャーのユニークポインタ
       */
      void SetStateManage(std::unique_ptr<State::StateManager> state);
      /**
       * @ モデルアニメマネージャーのセッター
       * 
       * @param[in] model モデルアニメマネージャーのユニークポインタ
       */
      void SetModelManage(std::unique_ptr<Model::ModelAnimeManager> model);
      /**
       * @  カメラマネージャーのセッター
       * 
       * @param[in] camera カメラマネージャーのシェアードポインタ
       */
      void SetCameraManage(std::shared_ptr<Camera::CameraManager> camera);
      /**
       * @ オブジェクト管理するマネージャーのゲッター
       * 
       * @return オブジェクトサーバーのユニークポインタ
       */
      ObjectServer& GetObjectServer();
    protected:
      /**
       * @ オブジェクトのステートのゲッター
       *
       * @return オブジェクトのステート
       */
      inline ObjectState GetObjectState() const { return _objectState; }
      /**
       * @ オブジェクトのステートのセッター
       *
       * @param[in] objstate オブジェクトのステート
       */
      inline void SetObjectState(ObjectState objstate) { _objectState = objstate; }
      //!< ステートマネージャーのユニークポインタ
      std::unique_ptr<State::StateManager> _stateManage{ nullptr };
      //!< コリジョンのシェアードポインタ
      std::shared_ptr<Collision::CollisionManager> _collsionManage{ nullptr };
      //!< カメラのシェアードポインタ
      std::shared_ptr<Camera::CameraManager> _cameraManage{ nullptr };
      //!< モデルアニメマネージャーのユニークポインタ
      std::unique_ptr<Model::ModelAnimeManager> _modelAnimeManage{ nullptr };
    protected:
      Application::GameMain& _game;                     //!< ゲームメインクラスの参照
      bool _deadFlag{ false };                          //!< 死亡したかのフラグ
      bool _hitFlag{ false };                           //!< コリジョン用フラグ
      float _radius{ 0.0f };                            //!< コリジョン用半径
      MATRIX _worldTransform{ MGetIdent() };            //!< ワールド座標変換
      VECTOR _position{ 0.0f, 0.0f, 0.0f };             //!< 位置情報
      VECTOR _rotation{ 0.0f, 0.0f, 0.0f };             //!< 角度
      VECTOR _scale{ 1.0f, 1.0f, 1.0f };                //!< 拡大率
      ObjectState _objectState{ ObjectState::Active };  //!< オブジェクトのステート
    };
  } // namespace Object
} // namespace GlassHeart