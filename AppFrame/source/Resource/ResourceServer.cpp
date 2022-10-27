/*****************************************************************//**
 * @file   ResourceServer.cpp
 * @brief  ���\�[�X�}�l�[�W���[�N���X�̏���
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
    /** �R���X�g���N�^ */
    ResourceServer::ResourceServer(GameBase& game) : _game{ game } {
      Initialize();
    }
    /** ���������� */
    void ResourceServer::Initialize() {
      AllClear();
    }
    /** ������� */
    void ResourceServer::AllClear() {
      ClearGraphs();
      ClearModels();
      _sounds.clear();
    }
    /** �摜�̓ǂݍ��� */
    void ResourceServer::LoadGraphic(std::string_view key, const DivGraph& divgraph) {
      // �o�^�ς݂̏ꍇ�͉摜���폜
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
      // �摜�𕪊��ǂݍ���
      LoadDivGraph(divgraph.fileName.c_str(), allnum,
        divgraph.xNum, divgraph.yNum,
        divgraph.xSize, divgraph.ySize, handles.data());

      _graphs.emplace(key, std::make_pair(divgraph, handles));
    }
    /** �摜�̈ꊇ�ǂݍ��� */
    void ResourceServer::LoadGraphics(const GraphMap& graphmap) {
      for (auto&& [key, graph] : graphmap) {
        auto gra = graph;
        // _currentPath(�i�[�t�H���_)�{�t�@�C����
        gra.fileName = (_currntPath / gra.fileName).generic_string();
        LoadGraphic(key, gra);
      }
    }
    /** �J�����g�f�B���N�g����ݒ� */
    void ResourceServer::ChangeCurrentFile(std::string_view path) {
      _currntPath = path;
    }
    /** �摜�n���h���̎擾 */
    std::int_fast32_t ResourceServer::GetGraph(std::string_view key, std::int_fast16_t no) {
      // �Y������摜�n���h�����Ȃ����-1��Ԃ�
      if (!_graphs.contains(key.data())) {
        return None;
      }
      auto&& [divgraph, handles] = _graphs[key.data()];
      auto handle = handles.at(no);
      return handle;
    }
    /** �摜�n���h���̕������̎擾 */
    std::int_fast32_t ResourceServer::GetGraphCount(std::string_view& key) {
      // �Y������摜�n���h�����Ȃ����-1��Ԃ�
      if (!_graphs.contains(key.data())) {
        return None;
      }
      auto&& [divgraph, handles] = _graphs[key.data()];
      auto allnum = static_cast<std::int_fast32_t> (handles.size());
      return allnum;
    }
    /**  �摜���̎擾 */
    DivGraph ResourceServer::GetGraphInfo(std::string_view& key) {
      if (!_graphs.contains(key.data())) {
        return DivGraph();
      }
      auto&& [divgraph, handles] = _graphs[key.data()];
      return divgraph;
    }
    /** �摜�̏��� */
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
    /** ���f���̓ǂݍ��� */
    std::int_fast32_t ResourceServer::LoadModel(std::string_view key, 
      const std::string_view filename) {
      if (_models.contains(key.data())) {
        auto& [filename, handles, animes] = _models[key.data()];
        // �o�^�ς݂̏ꍇ�̓��f�����폜
        for (auto handle : handles) {
          MV1DeleteModel(handle);
        }
        handles.clear();
        animes.clear();
        _models.erase(key.data());
      }
      auto handle = MV1LoadModel(filename.data());
      std::vector<std::int_fast32_t> handles{ handle };
      // �A�j���[�V�����̐����擾����
      auto animNum = MV1GetAnimNum(handle);
      std::unordered_map<std::string, std::int_fast32_t> animes;
      for (auto i = 0; i < animNum; ++i) {
        auto animName = MV1GetAnimName(handle, i);
        animes.emplace(animName, i);
      }
      // �L�[�ƃf�[�^��A�z�z��ɓo�^
      _models.emplace(key, std::make_tuple(filename.data(), handles, animes));
      return handle;
    }
    /** ���f���̈ꊇ�ǂݍ��� */
    void ResourceServer::LoadModels(const ModelMap& modelmap) {
      for (auto&& [key, filename] : modelmap) {
        auto path = (_currntPath / filename).generic_string();
        LoadModel(key, path);
      }
    }
    /** ���f���̃n���h���̎擾 */
    std::pair<std::int_fast32_t, std::int_fast32_t> ResourceServer::GetModles(std::string_view key, std::int_fast16_t no) {
      if (!_models.contains(key.data())) {
        // �L�[�����o�^
        return std::make_pair(None, no);
      }
      auto& [filename, handles, animes] = _models[key.data()];
      if (no < handles.size()) {
        return std::make_pair(handles[no], no); // ����no�̏ꍇ
      }
      // �V�Kno�̏ꍇ�͕�������
      auto handle = MV1DuplicateModel(handles[0]);  /// handles[0]���I���W�i��
      handles.push_back(handle);
      return std::make_pair(handle, static_cast<int>(handles.size()) - 1);
    }
    /** ���f�������� */
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
    /** ���f���̃A�j���[�V�����ԍ����擾 */
    std::int_fast32_t ResourceServer::GetModelAnimIndex(std::string_view key, std::string_view animName) {
      if (!_models.contains(key.data())) {
        // �L�[�����o�^
        return None;
      }
      auto& [filename, handles, animes] = _models[key.data()];
      if (!animes.contains(animName.data())) {
        // �A�j���̖��O�����o�^
        return None;
      }
      return animes[animName.data()];
      return 0;
    }
    /** Duplicate�������f�������폜���ăN���A���� */
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
    /** ���t�@�C���̓ǂݍ��� */
    void ResourceServer::LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad) {
      if (_sounds.contains(key.data())) {
        // �L�[���������o�^�ς�
        return;
      }
      // �L�[����������
      auto&& [filename, isLoad] = filename_isLoad;
      auto handle = None;
      if (isLoad) {
        handle = LoadSoundMem(filename.c_str());
      }
      // �L�[�ƃf�[�^��A�z�z��ɓo�^
      _sounds.emplace(key, std::make_pair(filename, handle));
    }
    /** ���t�@�C���̈ꊇ�ǂݍ��� */
    void ResourceServer::LoadSounds(const SoundMap& soundMap) {
      for (auto&& [key, filename_isLoad] : soundMap) {
        auto [filename, isLoad] = filename_isLoad;
        // _currentPath(�i�[�t�H���_)�{�t�@�C����
        filename = (_currntPath / filename).generic_string();
        LoadSound(key, { filename, isLoad });
      }
    }
    /** ���t�@�C�����̎擾 */
    std::pair<std::string, std::int_fast32_t> ResourceServer::GetSoundInfo(std::string_view key) {
      if (!_sounds.contains(key.data())) {
        // �L�[�����o�^
        return std::make_pair("", None);
      }
      return _sounds[key.data()];
    }
  }
}