#pragma once

#include <string>
#include <vector>

// clang-format off

namespace ARCreatorLogic {
namespace FasClusterLogic {

///
/// @brief The ShowHideNode contains config information of controlled node on scene graph
///
struct ShowHideNode {
    std::string scene; // scene name
    std::string node;  // node name
    bool ar; // to choose message type to be sent. Should be removed and fixed somehow else
};

///
/// @brief Config Logic configuration
///
struct Config {
    std::string scene; // scene graph name
    std::string node;  // main controlled node name
    // list of other controlled nodes to be hidden in case of Warning/TOR
    std::vector<ShowHideNode> nodes_show_hide;
};

// clang-format on

} // namespace FasClusterLogic
} // namespace ARCreatorLogic

