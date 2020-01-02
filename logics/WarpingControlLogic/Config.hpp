#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

// clang-format off

namespace ARCreatorLogic {
namespace WarpingControlLogic {
//using MirrorData = std::array<double, 3>; // low, mid, high
using MirrorData = std::vector<double>; // TODO: someone, please, make std::array serializable

///
/// @brief ZoneData helper structure for warping configuration of separate zone
///
struct ZoneData {
    std::string  name; // warping zone name
    uint32_t  width;   // the number of columns of warping matrix
    uint32_t height;  // the number of rows of warping matrix
    // HUD mirror positions applicable for low/mid/high matrices
    MirrorData  mirror_pos;
};

///
/// @brief Config Logic configuration
///
struct Config {
    ZoneData static_zone; // configuration of static HUD area
    ZoneData ar_zone;     // configuration of AR HUD area
    double  mat_div_factor;   // factor to convert matrix data from bytes blob to Float
    double  mirror_angle_min; // lower HUD mirror position
    double  mirror_angle_max; // upper HUD mirror position
};

} // namespace WarpingControlLogic
} // namespace ARCreatorLogic

// clang-format on
