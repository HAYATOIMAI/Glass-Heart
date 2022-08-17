#pragma once
#include "Singleton.h"
#include <nlohmann/json.hpp>

namespace AppFrame {

  namespace Utility {

    class WriteJson : public Singleton<WriteJson> {
    private:
      WriteJson() {};
      ~WriteJson()override {};
    public:
      friend class Singleton<WriteJson>;
    };
  }
}


