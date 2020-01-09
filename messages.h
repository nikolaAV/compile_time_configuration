#pragma once

// clang-format off

namespace ARCreatorLogic 
{

struct EyeBoxSettingsChanged {
}; 

struct OnOff {
    bool on_off;
}; 

struct HiddenShown {
    std::string node_name;
    bool hide_show;
};

struct HiddenShownEvent {
    bool hidden_shown;
}; 

} // namespace ARCreatorLogic

// clang-format on

