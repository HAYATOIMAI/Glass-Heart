
/*********************************************************************
 * @file   Player.h
 * @brief  プレイヤークラスの宣言
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once

#include "../Object/ObjectBase.h"
#include <string>
#include <AppFrame.h>

namespace AppFrame {
    class InputManager;
    class SoundManager;
}

namespace GlassHeart {

    class GameMain;

    namespace Camera {
        class CameraManager;
    }
    namespace Model {
        class ModelAnimeManager;
    }

    namespace Player {
        /**
         * @class Player
         * @brief プレイヤー
         */
        class Player : public  Object::ObjectBase {
        public:
            /**
             * @brief 色状態
             */
            enum class ColourState {
                White,
                Black,
            };
            /**
             * @brief コンストラクタ
             *
             * @param game ゲームメインクラスへの参照
             */
            Player(GameMain& game);
            /**
             * @brief デストラクタ
             *
             */
            virtual~Player() = default;
            /**
             * @brief 入力処理
             *
             * @param[in] input  インプットマネージャークラスの参照
             */
            virtual void Input(AppFrame::InputManager& input) override;
            /**
             * @brief 更新処理
             *
             */
            virtual void Process() override;
            /**
             * @brief 描画処理
             *
             */
            void Render() override;
            /**
             * @brief オブラートタイプ
             */
            ObjectType GetObjectType() const  override { return ObjectType::Player; };
            /**
             * @brief ワールド座標変換
             *
             */
            void ComputeWorldTransform() override;
            /**
             * @brief 移動処理
             *
             * @param[in] forward
             */
            virtual void Move(const VECTOR& forward);
            /**
             * @brief 色判定処理
             * 
             */
            void ColorCollisionDetectionSystem();
            void SetWhite();
            void SetBlack();
            /**
             * @brief リスポーンシステム
             * 
             */
            void ResetPos();

            inline float GetForwardSpeed() { return _forwardSpeed; }
            inline void SetForwardSpeed(float forwardSpeed) { _forwardSpeed = forwardSpeed; }
            
            inline std::string& GetCrName() { return _stateName; }
            
            inline ColourState& GetColourState() { return _crState; }
            
            inline VECTOR GetJumpVelocity() { return _jumpVelocity; }
            inline void SetJumpVelocity(VECTOR jump) { _jumpVelocity = jump; }

            inline bool GetCheckPointFlag() { return _checkPointFlag; }
            inline void SetCheckPointFlag(bool flag) { _checkPointFlag = flag; }
        protected:
            ColourState _crState{ ColourState::White }; //!< 色状態を管理する変数
            float _forwardSpeed{ 0.0f };                //!< 前進スピード
            std::string _stateName{ "White" };          //!< デバッグ用状態名変数
            int _recastCount{ 0 };                      //!< 色変更クールタイム用カウンター
            int _deathCoolCount{ 0 };                   //!<死亡した時の復活クールタイム
            bool _checkPointFlag{ false };              //!< チェックポイントフラグ
            VECTOR _jumpVelocity{ 0.f, 0.f, 0.f };      //!< ジャンプ速度
        };
    } // Player
} // GlassHeart 