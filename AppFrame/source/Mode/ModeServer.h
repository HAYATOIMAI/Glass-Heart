/*****************************************************************//**
 * @file   ModeServer.h
 * @brief  モードサーバークラスの宣言
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <memory>
#include <unordered_map>
#include <string_view>
#include <list>

namespace AppFrame {
    class ModeBase;
    class InputManager;
    class GameBase;
    /**
     * @class ModeServer
     * @brief モードサーバークラスの宣言
     *        モードクラスを管理する
     */
    class ModeServer {
    public:
        /**
         * @brief      コンストラクタ
         *
         * @param[in] key  最初のモードに関連付ける任意の文字列
         * @param[in] mode 最初のモードの
         */
        ModeServer(std::string_view key, std::shared_ptr<ModeBase> mode);
        /**
         * @brief      モードの登録
         *
         * @param[in] key  モードに関連付ける任意の文字列
         * @param[in] mode モードのインスタンス
         */
        void Register(std::string_view key, std::shared_ptr<ModeBase> mode);
        /**
         * @brief      モードのプッシュバック
         *             リストの一番後ろ(最前面)にモードをプッシュ追加する
         *             ModeBaseの入口処理Enterを実行する
         *
         * @param[in] key  登録済みのモードに関連付けた文字列
         */
        void PushBack(std::string_view key);
        /**
         * @brief モードのポップバック
         *        リストの一番後ろ(最前面)のモードをポップ除外する
         *        ModeBaseの出口処理Exitを実行する
         *
         */
        void PopBack();
        /**
         * @brief      モードの遷移
         *             keyで指定されたモードへ移行する
         *
         * @param[in] key  登録済みのモードに関連付けた文字列
         */
        void GoToMode(std::string_view key);
        /**
         * @brief      リストの一番後ろ(最前面)のモードの真下に挿入する
         *             ModeBaseの入口処理Enterを実行する
         *
         * @param[in] key  登録済みのモードに関連付けた文字列
         */
        void InsertBelowBack(std::string_view key);
        /**
         * @brief       入力処理
         *
         * @param[in] input インプットマネージャークラスへの参照
         */
        void Input(InputManager& input);
        /**
         * @brief  更新処理
         *
         */
        void Process();
        /**
         * @brief 描画処理
         *
         */
        void Render() const;
    private:
        std::unordered_map<std::string, std::shared_ptr<ModeBase>> _registry;   //!< モードのレジストリ
        std::list<std::shared_ptr<ModeBase>> _mode;  //!< モードのリスト
    };
} // namespace AppFrame