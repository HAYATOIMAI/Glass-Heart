#pragma once
#include "../Object/ObjectBase.h"
#include <memory>

namespace GlassHeart {

    namespace Model {
        class ModelManager;
    }
    class GameMain;

    namespace Stage {

        class Stage : public  Object::ObjectBase {
        public:
            Stage(GameMain& game);
            virtual void Process() override;
            void Render() override;
            ObjectType GetObjectType() const override { return ObjectType::Stage; }
        private:
            std::unique_ptr<Model::ModelManager> _skySphere;
            std::unique_ptr<Model::ModelManager> _ground;
        };
    }
}


