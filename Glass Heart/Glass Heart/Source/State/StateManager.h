
/*****************************************************************//**
 * @file   StateManager.h
 * @brief  ステートマネージャークラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <AppFrame.h>

namespace AppFrame {
    class InputManager;
}

namespace GlassHeart {

    namespace Object {
        class ObjectBase;
    }

    namespace State {

        class StateBaseRoot {
        public:
            StateBaseRoot() {};
            virtual void Enter() {};
            virtual void Input(AppFrame::InputManager& input) {};
            virtual void Update() {};
            virtual void Draw() {};
        };
        /**
         * @class StateManager
         * @brief オブジェクトの状態を管理する
         */
        class StateManager {
        public:
            /// コンストラクタ
            /// @param[in] key   最初のシーンに関連付ける任意の文字列
            /// @param[in] scene 最初のシーンの
            StateManager(std::string_view key, std::shared_ptr<StateBaseRoot> state);
            /// コンストラクタ
            /// @param[in] key   最初のシーンに関連付ける任意の文字列
            /// @param[in] scene 最初のシーンの
            void Register(std::string_view key, std::shared_ptr<StateBaseRoot> state);
            /// 状態のプッシュバック
            /// リストの一番後ろ(最前面)にシーンをプッシュ追加する
            /// Modeの入口処理Enterを実行する
            /// @param[in] key 登録済みのシーンに関連付けた文字列
            void PushBack(std::string_view key);
            /// 状態のポップバック
            /// リストの一番後ろ(最前面)のシーンをポップ除外する
            /// Sceneの出口処理Exitを実行する
            void PopBack();
            /// 状態の遷移
            /// PopBackしてPushBackする
            /// @param[in] key 登録済みのシーンに関連付けた文字列
            void GoToState(std::string_view key);
            /// 入力
            /// リストの一番後ろ(最前面)のシーンだけ処理する
            /// @param[in] input インプットコンポーネントの参照
            void Input(AppFrame::InputManager& input);
            /// 更新
            /// リストの一番後ろ(最前面)のシーンだけ処理する
            void Update();
            /// 描画
            /// リストの全シーンを処理する
            void Draw() const;
        private:
            std::unordered_map<std::string, std::shared_ptr<StateBaseRoot>>	_registry;  //!< 状態のレジストリ
            std::list<std::shared_ptr<StateBaseRoot>> _states;  //!< 状態のリスト
        };
    } // State
} // GlassHeart