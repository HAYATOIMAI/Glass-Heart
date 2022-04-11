
/*****************************************************************//**
 * @file   ResourceServer.h
 * @brief  リソースサーバー
 * 
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

namespace AppFrame {

    class GameBase;
    /**
     * @struct DivGraph
     * @brief 画像ファイル用構造体
     */
    struct DivGraph {
        std::string fileName{ "" };
        int xNum{ 0 };
        int yNum{ 0 };
        int xSize{ 0 };
        int ySize{ 0 };
    };
    /**
     * @class ResourceServer
     * @brief リソース管理マネージャー
     */
    class ResourceServer {
    public:
        /**
         * @brief 任意の文字列をキーとしてDivGraphを管理
         */
        using GraphMap = std::unordered_map<std::string, DivGraph>;
        /**
         * @brief 任意の文字列をキーにして音ファイル名と事前読み込みの有無を管理
         */
        using SoundMap = std::unordered_map <std::string, std::pair<std::string, bool>>;
        /**
         * @brief 任意の文字列をキーにしてモデルファイル名を管理
         */
        using ModelMap = std::unordered_map<std::string, std::string>;
        /**
         * @brief コンストラクタ
         *
         * @param[in] game ゲームベースクラスへの参照
         */
        ResourceServer(GameBase& game);
        /**
         * @brief デストラクタ
         *
         */
        virtual ~ResourceServer() = default;
        /**
         * @brief 初期化処理
         *
         */
        virtual void Initialize();
        /**
         * @brief 全リソース削除
         *        画像、モデル、音の全てを削除する
         *
         */
        virtual void AllClear();
        /**
         * @brief 画像の読み込み
         *
         * @param[in] key      キーとなる任意の文字列
         * @param[in] divgraph 画像ファイル用構造体への参照
         */
        virtual void LoadGraphic(std::string_view key, const DivGraph& divgraph);
        /**
         * @brief 画像の一括読み込み
         *
         * @param[in] graphmap 画像のテーブル
         */
        virtual void LoadGraphics(const GraphMap& graphmap);
        /**
         * @brief 読み込み時のカレントフォルダの変更
         *        カレントフォルダ直下のファイルを読み込む
         *
         * @param[in] path カレントフォルダ
         */
        virtual void ChangeCurrentFile(std::string_view path);
        /**
         * @brief 画像ハンドルの取得
         *
         * @param[in] key 登録済みのキー
         * @param[in] no  分割時の番号
         * @return 画像のハンドル
         */
        virtual int  GetGraph(std::string_view key, int no = 0);
        /**
         * @brief 画像ハンドルの分割数の取得
         *
         * @param[in] key 登録済みのキー
         * @return 分割総数
         */
        virtual int GetGraphCount(std::string_view& key);
        /**
         * @brief 画像情報の取得
         *
         * @param[in] key   登録済みのキー
         * @return DivGraph 画像情報
         */
        virtual DivGraph GetGraphInfo(std::string_view& key);
        /**
         * @brief 画像の削除
         * @param[in] key 登録済みのキー
         */
        virtual void ClearGraphs();
        /**
         * @brief モデルの読み込み
         *
         * @param key          キーとなる任意の文字列
         * @param[in] filename filename mv1ファイル名
         * @return モデルのハンドル
         */
        virtual int  LoadModel(std::string_view key, const std::string_view filename);
        /**
         * @brief モデルの一括読み込み
         *
         * @param[in] modelmap モデルのテーブル
         */
        virtual void LoadModels(const ModelMap& modelmap);
        /**
         * @brief モデルのハンドルの取得
         *        既読の場合は複製する
         *
         * @param[in] key 登録済みのキー
         * @param[in] no  同一モデルの通し番号
         * @return モデルのハンドルと実施の登録番号
         */
        virtual std::pair<int, int> GetModles(std::string_view key, int no = 0);
        /**
         * @brief 全てのモデルを削除する
         *
         */
        virtual void ClearModels();
        /**
         * @brief モデルのアニメーション番号を取得
         * 
         * @param[in] key      キーとなる任意の文字列
         * @param[in] animName アニメーション番号
         * @return アニメーション番号
         */
        virtual int GetModelAnimIndex(std::string_view key, std::string_view animName);
        /**
         * @brief Duplicateしたモデルだけ削除する
         *
         */
        virtual void DeleteDuplicateModels();
        /**
         * @brief 音ファイルの読み込み
         *
         * @param[in] key             キーとなる任意の文字列
         * @param[in] filename_isLoad ファイル名と事前読み込み有無のペア
         */
        virtual void LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad);
        /**
         * @brief 音ファイルの一括読み込み
         *
         * @param[in] soundMap 音ファイルのテーブル
         */
        virtual void LoadSounds(const SoundMap& soundMap);
        /**
         * @brief 音ファイル情報の取得
         *
         * @param[in] key        登録済みのキー
         * @return 音ファイル名, ハンドル
         */
        virtual std::pair<std::string, int> GetSoundInfo(std::string_view key);

    private:
        GameBase& _game;  //!< ゲームベースクラスへの参照
        std::filesystem::path _currntPath;  //!< 格納フォルダへのパス
        //!< 任意の文字列をキーにしてDivGraphと画像ハンドルのペアを管理
        std::unordered_map<std::string, std::pair<DivGraph, std::vector<int>>>	_graphs;
         //!< 任意の文字列をキーにして音ファイル名とハンドルのペアを管理
        std::unordered_map<std::string, std::pair<std::string, int>> _sounds;
         //!< 任意の文字列をキーにしてモデルファイル名とハンドルのペアを管理
        std::unordered_map<std::string, std::tuple<std::string, std::vector<int>, std::unordered_map<std::string, int>>> _models;
    };
} // namespace AppFrame