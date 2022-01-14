
/*****************************************************************//**
 * @file   ResourceServer.cpp
 * @brief  リソースサーバー
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ResourceServer.h"
#include <DxLib.h>

namespace AppFrame {
    /** コンストラクタ */
    ResourceServer::ResourceServer(GameBase& game) : _game{ game } {
        Initialize();
    }
    /** 初期化処理 */
    void ResourceServer::Initialize() {
        AllClear();
    }
    /** 解放処理 */
    void ResourceServer::AllClear() {
        ClearGraphs();
        ClearModels();
        _sounds.clear();
    }
    /** 画像の読み込み */
    void ResourceServer::LoadGraphic(std::string_view key, const DivGraph& divgraph) {
        // 登録済みの場合は画像を削除
        if (_graphs.contains(key.data())) {
            auto&& [graph, handles] = _graphs[key.data()];
            for (auto&& handle : handles) {
                DeleteGraph(handle);
            }
            handles.clear();
            _graphs.erase(key.data());
        }
        auto allnum = divgraph._xNum * divgraph._yNum;
        std::vector<int> handles(allnum);
        LoadDivGraph(divgraph._fileName.c_str(), allnum,
            divgraph._xNum, divgraph._yNum,
            divgraph._xSize, divgraph._ySize, handles.data());

        _graphs.emplace(key, std::make_pair(divgraph, handles));
    }
    /** 画像の一括読み込み */
    void ResourceServer::LoadGraphics(const GraphMap& graphmap) {
        for (auto&& [key, graph] : graphmap) {
            auto gra = graph;
            // _currentPath(格納フォルダ)＋ファイル名
            gra._fileName = (_currrntPath / gra._fileName).generic_string();
            LoadGraphic(key, gra);
        }
    }
    void ResourceServer::ChangeCurrentFile(std::string_view path) {
        _currrntPath = path;
    }
    /** 画像ハンドルの取得 */
    int ResourceServer::GetGraph(std::string_view key, int no) {
        if (!_graphs.contains(key.data())) {
            return -1;
        }
        auto&& [divgraph, handles] = _graphs[key.data()];
        auto handle = handles.at(no);
        return handle;
    }
    /** 画像ハンドルの分割数の取得 */
    int ResourceServer::GetGraphCount(std::string_view& key) {
        if (!_graphs.contains(key.data())) {
            return -1;
        }
        auto&& [divgraph, handles] = _graphs[key.data()];
        int allnum = static_cast<int> (handles.size());
        return allnum;
    }
    /**  画像情報の取得 */
    DivGraph ResourceServer::GetGraphInfo(std::string_view& key) {
        if (!_graphs.contains(key.data())) {
            return DivGraph();
        }
        auto&& [divgraph, handles] = _graphs[key.data()];

        return divgraph;
    }
    /** 画像の消去 */
    void ResourceServer::ClearGraphs() {
        for (auto&& [key, divgtgraph_handles] : _graphs) {
            auto&& [divgraph, handles] = divgtgraph_handles;
            for (auto handle : handles) {
                DeleteGraph(handle);
            }
            handles.clear();
        }
        _graphs.clear();
    }
    /** モデルの読み込み */
    int ResourceServer::LoadModel(std::string_view key, const std::string_view filename) {
        if (_models.contains(key.data())) {
            auto& [filename, handles, animes] = _models[key.data()];
            // 登録済みの場合はモデルを削除
            for (auto handle : handles) {
                MV1DeleteModel(handle);
            }
            handles.clear();
            animes.clear();
            _models.erase(key.data());
        }
        auto handle = MV1LoadModel(filename.data());
        std::vector<int> handles{ handle };

        auto animNum = MV1GetAnimNum(handle);
        std::unordered_map<std::string, int> animes;
        for (auto i = 0; i < animNum; ++i) {
            auto animName = MV1GetAnimName(handle, i);
            animes.emplace(animName, i);
        }

        _models.emplace(key, std::make_tuple(filename.data(), handles, animes));
        return handle;
    }
    /** モデルの一括読み込み */
    void ResourceServer::LoadModels(const ModelMap& modelmap) {
        for (auto&& [key, filename] : modelmap) {
            auto path = (_currrntPath / filename).generic_string();
            LoadModel(key, path);
        }
    }
    /** モデルのハンドルの取得 */
    std::pair<int, int> ResourceServer::GetModles(std::string_view key, int no) {
        if (!_models.contains(key.data())) {
            // キーが未登録
            return std::make_pair(-1, no);
        }
        auto& [filename, handles, animes] = _models[key.data()];
        if (no < handles.size()) {
            return std::make_pair(handles[no], no); // 既存noの場合
        }
        // 新規noの場合は複製する
        auto handle = MV1DuplicateModel(handles[0]);  /// handles[0]がオリジナル
        handles.push_back(handle);
        return std::make_pair(handle, static_cast<int>(handles.size()) - 1);
    }
    /** モデルを消去 */
    void ResourceServer::ClearModels() {
        for (auto&& [key, model] : _models) {
            auto&& [filename, handles, animes] = model;
            for (auto handle : handles) {
                MV1DeleteModel(handle);
            }
            handles.clear();
            animes.clear();
        }
        _models.clear();
    }
    int ResourceServer::GetModelAnimIndex(std::string_view key, std::string_view animName) {
        if (!_models.contains(key.data())) {
            // キーが未登録
            return -1;
        }
        auto& [filename, handles, animes] = _models[key.data()];
        if (!animes.contains(animName.data())) {
            // アニメの名前が未登録
            return -1;
        }
        return animes[animName.data()];
        return 0;
    }
    /** Duplicateしたモデルだけ削除してクリアする */
    void ResourceServer::DeleteDuplicateModels() {
        for (auto&& [key, model] : _models) {
            auto&& [filename, handles, animes] = model;
            auto original = handles[0];
            erase_if(handles, [original](auto handle) {
                if (original != handle) {
                    MV1DeleteModel(handle);
                    return true;
                }
                return false;
                });
        }
    }
    /** 音ファイルの読み込み */
    void ResourceServer::LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad) {
        if (_sounds.contains(key.data())) {
            // キーがあった登録済み
            return;
        }
        // キーが無かった
        auto&& [filename, isLoad] = filename_isLoad;
        auto handle = -1;
        if (isLoad) {
            handle = LoadSoundMem(filename.c_str());
        }
        // キーとデータをmapに登録
        _sounds.emplace(key, std::make_pair(filename, handle));
    }
    /** 音ファイルの一括読み込み */
    void ResourceServer::LoadSounds(const SoundMap& soundMap) {
        for (auto&& [key, filename_isLoad] : soundMap) {
            auto [filename, isLoad] = filename_isLoad;
            // _currentPath(格納フォルダ)＋ファイル名
            filename = (_currrntPath / filename).generic_string();
            LoadSound(key, { filename, isLoad });
        }
    }
    /** 音ファイル情報の取得 */
    std::pair<std::string, int> ResourceServer::GetSoundInfo(std::string_view key) {
        if (!_sounds.contains(key.data())) {
            // キーが未登録
            return std::make_pair("", -1);
        }
        return _sounds[key.data()];
    }
}

