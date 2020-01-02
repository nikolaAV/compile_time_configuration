#pragma once

#include <string>

// clang-format off

namespace ARCreatorLogic
{
namespace VirtualCamera
{

///
/// @brief helper structure for logic configurations.
///        represents HUD mirror position borders
///
struct MirrorAngles {
    double min; // lower mirror position in radians
    double max; // upper mirror position in radians
};

///
/// @brief VirtualCameraConfig Logic configuration
///
struct Config {
    std::string scene;          // controlled scene graph name
    MirrorAngles mirror_angles; //  HUD mirror position borders
};

} // namespace VirtualCamera
} // namespace ARCreatorLogic

// clang-format on
