#pragma once

#include "document.h"
#include <vector>

namespace svge {

class SVGE
{
    public:
        SVGE();
        ~SVGE();

    private:
        std::vector<Document> docs_;
};

}
