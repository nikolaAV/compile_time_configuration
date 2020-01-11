#pragma once

#include <string>
#include <utility>

// clang-format off

namespace ARCreatorLogic 
{

struct EyeBoxSettingsChanged {
    explicit EyeBoxSettingsChanged() = default;
}; 

struct OnOff {
    bool on_off;
    explicit OnOff(bool v) : on_off(v) {} 
}; 

struct HiddenShown {
    std::string node_name;
    bool hide_show;
    explicit HiddenShown(const char* name, bool flag) : node_name(name), hide_show(flag) {}
};

struct HiddenShownEvent {
    bool hidden_shown;
    explicit HiddenShownEvent(bool v) : hidden_shown(v) {}
}; 

template <typename T, typename... Args>
auto make_data(Args&&... args) {
    return T{std::forward<Args>(args)...};
}

template <typename Id, typename Data>
struct message {
    std::string id {Id::value()};
    Data data;
    explicit message(Data&& d) : data(std::move(d)) {} 
};

template <typename Id, typename T, typename... Args>
auto make_message(Args&&... args) {
    return message<Id,T>{make_data<T>(std::forward<Args>(args)...)};
}

} // namespace ARCreatorLogic

// clang-format on

