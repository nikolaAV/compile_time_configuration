#pragma once

#include <iostream>
#include <string>
#include <utility>

#include "IMessage.hpp"

// clang-format off

namespace ARCreatorLogic 
{

struct EyeBoxSettingsChanged {
    explicit EyeBoxSettingsChanged() = default;
}; 

inline std::ostream& operator<<(std::ostream& out, const EyeBoxSettingsChanged& data) {
    return out << "{}";
}

struct OnOff {
    bool on_off;
    explicit OnOff(bool v) : on_off(v) {} 
}; 

inline std::ostream& operator<<(std::ostream& out, const OnOff& data) {
    return out << std::boolalpha<< "{on_off:" << data.on_off << "}";
}

struct HiddenShown {
    std::string node_name;
    bool hide_show;
    explicit HiddenShown(const char* name, bool flag) : node_name(name), hide_show(flag) {}
};

inline std::ostream& operator<<(std::ostream& out, const HiddenShown& data) {
    return out << std::boolalpha<< "{node_name:" << data.node_name << ",hide_show:" << data.hide_show << "}";
}

struct HiddenShownEvent {
    bool hidden_shown;
    explicit HiddenShownEvent(bool v) : hidden_shown(v) {}
}; 

inline std::ostream& operator<<(std::ostream& out, const HiddenShownEvent& data) {
    return out << std::boolalpha<< "{hidden_shown:" << data.hidden_shown << "}";
}

template <typename T, typename... Args>
auto make_data(Args&&... args) {
    return T{std::forward<Args>(args)...};
}

template <typename Id, typename Data>
struct message : IMessage {
    std::string id {Id::value()};
    Data data;
    explicit message(Data&& d) : data(std::move(d)) {} 

    void send() const override {
        std::cout << "\t" << id << " ---> " << data << std::endl;
    } 
};

} // namespace ARCreatorLogic

// clang-format on

