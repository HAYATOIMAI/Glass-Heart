/*****************************************************************//**
 * @file   ResourceServer.cpp
 * @brief  リソースマネージャークラスの処理
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ResourceServer.h"
#include <DxLib.h>

namespace {
  constexpr auto None = -1;
}

namespace AppFrame {
  namespace Resource {
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
      auto allnum = divgraph.xNum * divgraph.yNum;
      std::vector<std::int_fast32_t> handles(allnum);
      // 画像を分割読み込み
      LoadDivGraph(divgraph.fileName.c_str(), allnum,
        divgraph.xNum, divgraph.yNum,
        divgraph.xSize, divgraph.ySize, handles.data());

      _graphs.emplace(key, std::make_pair(divgraph, handles));
    }
    /** 画像の一括読み込み */
    void ResourceServer::LoadGraphics(const GraphMap& graphmap) {
      for (auto&& [key, graph] : graphmap) {
        auto gra = graph;
        // _currentPath(格納フォルダ)＋ファイル名
        gra.fileName = (_currntPath / gra.fileName).generic_string();
        LoadGraphic(key, gra);
      }
    }
    /** カレントディレクトリを設定 */
    void ResourceServer::ChangeCurrentFile(std::string_view path) {
      _currntPath = path;
    }
    /** 画像ハンドルの取得 */
    std::int_fast32_t ResourceServer::GetGraph(std::string_view key, std::int_fast16_t no) {
      // 該当する画像ハンドルがなければ-1を返す
      if (!_graphs.contains(key.data())) {
        return None;
      }
      auto&& [divgraph, handles] = _graphs[key.data()];
      auto handle = handles.at(no);
      return handle;
    }
    /** 画像ハンドルの分割数の取得 */
    std::int_fast32_t ResourceServer::GetGraphCount(std::string_view& key) {
      // 該当する画像ハンドルがなければ-1を返す
      if (!_graphs.contains(key.data())) {
        return None;
      }
      auto&& [divgraph, handles] = _graphs[key.data()];
      auto allnum = static_cast<std::int_fast32_t> (handles.size());
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
    std::int_fast32_t ResourceServer::LoadModel(std::string_view key, 
      const std::string_view filename) {
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
      std::vector<std::int_fast32_t> handles{ handle };
      // アニメーションの数を取得する
      auto animNum = MV1GetAnimNum(handle);
      std::unordered_map<std::string, std::int_fast32_t> animes;
      for (auto i = 0; i < animNum; ++i) {
        auto animName = MV1GetAnimName(handle, i);
        animes.emplace(animName, i);
      }
      // キーとデータを連想配列に登録
      _models.emplace(key, std::make_tuple(filename.data(), handles, animes));
      return handle;
    }
    /** モデルの一括読み込み */
    void ResourceServer::LoadModels(const ModelMap& modelmap) {
      for (auto&& [key, filename] : modelmap) {
        auto path = (_currntPath / filename).generic_string();
        LoadModel(key, path);
      }
    }
    /** モデルのハンドルの取得 */
    std::pair<std::int_fast32_t, std::int_fast32_t> ResourceServer::GetModles(std::string_view key, std::int_fast16_t no) {
      if (!_models.contains(key.data())) {
        // キーが未登録
        return std::make_pair(None, no);
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
    /** モデルのアニメーション番号を取得 */
    std::int_fast32_t ResourceServer::GetModelAnimIndex(std::string_view key, std::string_view animName) {
      if (!_models.contains(key.data())) {
        // キーが未登録
        return None;
      }
      auto& [filename, handles, animes] = _models[key.data()];
      if (!animes.contains(animName.data())) {
        // アニメの名前が未登録
        return None;
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
      auto handle = None;
      if (isLoad) {
        handle = LoadSoundMem(filename.c_str());
      }
      // キーとデータを連想配列に登録
      _sounds.emplace(key, std::make_pair(filename, handle));
    }
    /** 音ファイルの一括読み込み */
    void ResourceServer::LoadSounds(const SoundMap& soundMap) {
      for (auto&& [key, filename_isLoad] : soundMap) {
        auto [filename, isLoad] = filename_isLoad;
        // _currentPath(格納フォルダ)＋ファイル名
        filename = (_currntPath / filename).generic_string();
        LoadSound(key, { filename, isLoad });
      }
    }
    /** 音ファイル情報の取得 */
    std::pair<std::string, std::int_fast32_t> ResourceServer::GetSoundInfo(std::string_view key) {
      if (!_sounds.contains(key.data())) {
        // キーが未登録
        return std::make_pair("", None);
      }
      return _sounds[key.data()];
    }
  }
}