/*****************************************************************//**
 * @file   ResourceServer.h
 * @brief  ���\�[�X�}�l�[�W���[�N���X�̐錾
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
#include <cstdint>
 /**
  * @namespace AppFrame
  * @brief     �A�v���P�[�V�����t���[��
  */
namespace AppFrame {
  class GameBase;
  /**
   * @namespace Resource
   * @brief     ���\�[�X�֌W
   */
  namespace Resource {
    /**
     * @struct DivGraph
     * @brief  �摜�t�@�C���p�\����
     */
    struct DivGraph {
      std::string fileName;    //!< �t�@�C����
      std::int_fast16_t xNum;  //!< �摜�̏c���̕�����
      std::int_fast16_t yNum;  //!< �摜�̉����̕�����
      std::int_fast16_t xSize; //!< �摜�̏c��
      std::int_fast16_t ySize; //!< �摜�̉���
    };
    /**
     * @class ResourceServer
     * @brief ���\�[�X�}�l�[�W���[�N���X�̐錾
     */
    class ResourceServer {
    public:
      /**
       * @brief                     �C�ӂ̕�������L�[�Ƃ���DivGraph���Ǘ�
       */
      using GraphMap = std::unordered_map<std::string, DivGraph>;
      /**
       * @brief                     �C�ӂ̕�������L�[�ɂ��ĉ��t�@�C�����Ǝ��O�ǂݍ��݂̗L�����Ǘ�
       */
      using SoundMap = std::unordered_map<std::string, std::pair<std::string, bool>>;
      /**
       * @brief                     �C�ӂ̕�������L�[�ɂ��ă��f���t�@�C�������Ǘ�
       */
      using ModelMap = std::unordered_map<std::string, std::string>;
      /**
       * @brief                     �R���X�g���N�^
       *                            
       * @param[in] game            �Q�[���x�[�X�N���X�ւ̎Q��
       */
      ResourceServer(GameBase& game);
      /**
       * @brief                     �f�X�g���N�^
       */
      virtual ~ResourceServer() = default;
      /**
       * @brief                     ����������
       */
      virtual void Initialize();
      /**
       * @brief                     �S���\�[�X�폜
       *                            �摜�A���f���A���̑S�Ă��폜����
       */
      virtual void AllClear();
      /**
       * @brief                     �摜�̓ǂݍ���
       *                            
       * @param[in] key             �L�[�ƂȂ�C�ӂ̕�����
       * @param[in] divgraph        �摜�t�@�C���p�\���̂ւ̎Q��
       */
      virtual void LoadGraphic(std::string_view key, const DivGraph& divgraph);
      /**
       * @brief                     �摜�̈ꊇ�ǂݍ���
       *                            
       * @param[in] graphmap        �摜�̃e�[�u��
       */
      virtual void LoadGraphics(const GraphMap& graphmap);
      /**
       * @brief                     �ǂݍ��ݎ��̃J�����g�t�H���_�̕ύX
       *                            �J�����g�t�H���_�����̃t�@�C����ǂݍ���
       *                            
       * @param[in] path            �J�����g�t�H���_
       */
      virtual void ChangeCurrentFile(std::string_view path);
      /**
       * @brief                     �摜�n���h���̎擾
       *                            
       * @param[in] key             �o�^�ς݂̃L�[
       * @param[in] no              �������̔ԍ�
       * @return                    �摜�̃n���h��
       */
      virtual std::int_fast32_t GetGraph(std::string_view key, std::int_fast16_t no = 0);
      /**
       * @brief                     �摜�n���h���̕������̎擾
       *                            
       * @param[in] key             �o�^�ς݂̃L�[
       * @return                    ��������
       */
      virtual std::int_fast32_t GetGraphCount(std::string_view& key);
      /**
       * @brief                     �摜���̎擾
       *                            
       * @param[in] key             �o�^�ς݂̃L�[
       * @return DivGraph           �摜���
       */
      virtual DivGraph GetGraphInfo(std::string_view& key);
      /**
       * @brief                     �摜�̍폜
       * @param[in] key             �o�^�ς݂̃L�[
       */
      virtual void ClearGraphs();
      /**
       * @brief                     ���f���̓ǂݍ���
       *                            
       * @param[in] key             �L�[�ƂȂ�C�ӂ̕�����
       * @param[in] filename        mv1�t�@�C����
       * @return                    ���f���̃n���h��
       */
      virtual std::int_fast32_t LoadModel(std::string_view key, const std::string_view filename);
      /**
       * @brief                     ���f���̈ꊇ�ǂݍ���
       *                            
       * @param[in] modelmap        ���f���̃e�[�u��
       */
      virtual void LoadModels(const ModelMap& modelmap);
      /**
       * @brief                     ���f���̃n���h���̎擾
       *                            ���ǂ̏ꍇ�͕�������
       *
       * @param[in] key             �o�^�ς݂̃L�[
       * @param[in] no              ���ꃂ�f���̒ʂ��ԍ�
       * @return                    ���f���̃n���h���Ǝ��{�̓o�^�ԍ�
       */
      virtual std::pair<std::int_fast32_t, std::int_fast32_t> GetModles(std::string_view key, std::int_fast16_t no = 0);
      /**
       * @brief                     �S�Ẵ��f�����폜����
       */
      virtual void ClearModels();
      /**
       * @brief                     ���f���̃A�j���[�V�����ԍ����擾
       *                            
       * @param[in] key             �L�[�ƂȂ�C�ӂ̕�����
       * @param[in] animName        �A�j���[�V�����ԍ�
       * @return                    �A�j���[�V�����ԍ�
       */
      virtual std::int_fast32_t GetModelAnimIndex(std::string_view key, std::string_view animName);
      /**
       * @brief                     �����������f�������폜����
       */
      virtual void DeleteDuplicateModels();
      /**
       * @brief                     ���t�@�C���̓ǂݍ���
       *
       * @param[in] key             �L�[�ƂȂ�C�ӂ̕�����
       * @param[in] filename_isLoad �t�@�C�����Ǝ��O�ǂݍ��ݗL���̃y�A
       */
      virtual void LoadSound(std::string_view key, std::pair<std::string, bool> filename_isLoad);
      /**
       * @brief                     ���t�@�C���̈ꊇ�ǂݍ���
       *
       * @param[in] soundMap        ���t�@�C���̃e�[�u��
       */
      virtual void LoadSounds(const SoundMap& soundMap);
      /**
       * @brief                     ���t�@�C�����̎擾
       *
       * @param[in] key             �o�^�ς݂̃L�[
       * @return                    ���t�@�C����, �n���h��
       */
      virtual std::pair<std::string, std::int_fast32_t> GetSoundInfo(std::string_view key);
    private:
      GameBase& _game;                    //!< �Q�[���x�[�X�N���X�ւ̎Q��
      std::filesystem::path _currntPath;  //!< �i�[�t�H���_�ւ̃p�X
      /** �C�ӂ̕�������L�[�ɂ���DivGraph�Ɖ摜�n���h���̃y�A���Ǘ� */
      std::unordered_map<std::string, std::pair<DivGraph, std::vector<std::int_fast32_t>>> _graphs;
      /** �C�ӂ̕�������L�[�ɂ��ĉ��t�@�C�����ƃn���h���̃y�A���Ǘ� */
      std::unordered_map<std::string, std::pair<std::string, std::int_fast32_t>> _sounds;
      /**�C�ӂ̕�������L�[�ɂ��ă��f���t�@�C�����ƃn���h���̃y�A���Ǘ�  */
      std::unordered_map<std::string, std::tuple<std::string, std::vector<std::int_fast32_t>, 
        std::unordered_map<std::string, std::int_fast32_t>>> _models;
    };
  } // namespace Resource
} // namespace AppFrame