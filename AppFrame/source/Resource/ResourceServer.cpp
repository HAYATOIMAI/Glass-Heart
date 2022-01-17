
/*****************************************************************//**
 * @file   ResourceServer.cpp
 * @brief  ���\�[�X�T�[�o�[
 *
 * @author Hayato Imai
 * @date   December 2021
 *********************************************************************/
#include "ResourceServer.h"
#include <DxLib.h>

namespace AppFrame {
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
        auto allnum = divgraph._xNum * divgraph._yNum;
        std::vector<int> handles(allnum);
        LoadDivGraph(divgraph._fileName.c_str(), allnum,
            divgraph._xNum, divgraph._yNum,
            divgraph._xSize, divgraph._ySize, handles.data());

        _graphs.emplace(key, std::make_pair(divgraph, handles));
    }
    /** �摜�̈ꊇ�ǂݍ��� */
    void ResourceServer::LoadGraphics(const GraphMap& graphmap) {
        for (auto&& [key, graph] : graphmap) {
            auto gra = graph;
            // _currentPath(�i�[�t�H���_)�{�t�@�C����
            gra._fileName = (_currrntPath / gra._fileName).generic_string();
            LoadGraphic(key, gra);
        }
    }
    void ResourceServer::ChangeCurrentFile(std::string_view path) {
        _currrntPath = path;
    }
    /** �摜�n���h���̎擾 */
    int ResourceServer::GetGraph(std::string_view key, int no) {
        if (!_graphs.contains(key.data())) {
            return -1;
        }
        auto&& [divgraph, handles] = _graphs[key.data()];
        auto handle = handles.at(no);
        return handle;
    }
    /** �摜�n���h���̕������̎擾 */
    int ResourceServer::GetGraphCount(std::string_view& key) {
        if (!_graphs.contains(key.data())) {
            return -1;
        }
        auto&& [divgraph, handles] = _graphs[key.data()];
        int allnum = static_cast<int> (handles.size());
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
    int ResourceServer::LoadModel(std::string_view key, const std::string_view filename) {
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
    /** ���f���̈ꊇ�ǂݍ��� */
    void ResourceServer::LoadModels(const ModelMap& modelmap) {
        for (auto&& [key, filename] : modelmap) {
            auto path = (_currrntPath / filename).generic_string();
            LoadModel(key, path);
        }
    }
    /** ���f���̃n���h���̎擾 */
    std::pair<int, int> ResourceServer::GetModles(std::string_view key, int no) {
        if (!_models.contains(key.data())) {
            // �L�[�����o�^
            return std::make_pair(-1, no);
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
    int ResourceServer::GetModelAnimIndex(std::string_view key, std::string_view animName) {
        if (!_models.contains(key.data())) {
            // �L�[�����o�^
            return -1;
        }
        auto& [filename, handles, animes] = _models[key.data()];
        if (!animes.contains(animName.data())) {
            // �A�j���̖��O�����o�^
            return -1;
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
        auto handle = -1;
        if (isLoad) {
            handle = LoadSoundMem(filename.c_str());
        }
        // �L�[�ƃf�[�^��map�ɓo�^
        _sounds.emplace(key, std::make_pair(filename, handle));
    }
    /** ���t�@�C���̈ꊇ�ǂݍ��� */
    void ResourceServer::LoadSounds(const SoundMap& soundMap) {
        for (auto&& [key, filename_isLoad] : soundMap) {
            auto [filename, isLoad] = filename_isLoad;
            // _currentPath(�i�[�t�H���_)�{�t�@�C����
            filename = (_currrntPath / filename).generic_string();
            LoadSound(key, { filename, isLoad });
        }
    }
    /** ���t�@�C�����̎擾 */
    std::pair<std::string, int> ResourceServer::GetSoundInfo(std::string_view key) {
        if (!_sounds.contains(key.data())) {
            // �L�[�����o�^
            return std::make_pair("", -1);
        }
        return _sounds[key.data()];
    }
}

