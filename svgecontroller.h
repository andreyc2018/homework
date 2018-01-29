#pragma once
/** @file svgecontroller.h
 *  @brief The editor main controller
 */

#include "svge.h"
#include <vector>

namespace svge {

class SvgeController
{
    public:
        SvgeController();
        ~SvgeController();

    private:
        SvgeUPtr editor_;
};

}
