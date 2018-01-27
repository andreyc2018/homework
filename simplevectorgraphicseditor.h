#pragma once
/** @file simplevectorgraphicseditor.h
    @brief The editor main controller

    Details.
*/

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
