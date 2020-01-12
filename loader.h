#pragma once

// clang-format off

#include <vector>
#include "tag_types.h"
#include "logics/AccFasClusterLogic/CAccFasClusterLogic.hpp"
#include "logics/VirtualCameraLogic/CVirtualCameraLogic.hpp"
#include "logics/WarpingControlLogic/CWarpingControlLogic.hpp"

using BusinessLogicPtr = LCE::Logic::BusinessLogicPtr;
using BusinessLogics = std::vector<BusinessLogicPtr>;
using InterfaceAccessorPtr = LCE::InterfaceAccessor::InterfaceAccessorPtr; 
using namespace tag; 
using namespace ARCreatorLogic;           

template <typename T> T make_message_data_default();

template <>
inline
EyeBoxSettingsChanged make_message_data_default<EyeBoxSettingsChanged>() {
    return make_data<EyeBoxSettingsChanged>();
}

template <>
inline
OnOff make_message_data_default<OnOff>() {
    return make_data<OnOff>(false);
}

template <>
inline
HiddenShown make_message_data_default<HiddenShown>() {
    return make_data<HiddenShown>("some text", true);
}

template <>
inline
HiddenShownEvent make_message_data_default<HiddenShownEvent>() {
    return make_data<HiddenShownEvent>(true);
}

template <typename Zone>
auto make_zone_data() {
    static_assert(is_static_zone<Zone>::value || is_ar_zone<Zone>::value, "[make_zone_data<Zone>] Zone is invalid type");

    WarpingControlLogic::ZoneData zone{};
        zone.name   = get_name_t<Zone>{};
        zone.width  = get_width_t<Zone>{};
        zone.height = get_height_t<Zone>{}; 

        using mirror_pos_type = get_mirror_pos_t<Zone>;
        zone.mirror_pos = { 
                get_low_t<mirror_pos_type>{}
            ,get_mid_t<mirror_pos_type>{}
            ,get_high_t<mirror_pos_type>{} 
    };
    return zone;
}

template <typename Nshe>
auto make_node_show_hide() {
    static_assert(is_nshe<Nshe>::value, "[make_node_show_hide<Nshe>] Nshe is invalid type");

    FasClusterLogic::ShowHideNode node{};
        node.scene  = get_scene_t<Nshe>{};
        node.node   = get_node_t<Nshe>{};
        node.ar     = get_ar_t<Nshe>{};
    return node;
}

template <typename Msg>
auto make_message() {
    static_assert(is_msg<Msg>::value, "[make_message<Msg>] Msg is invalid type");
    using data_type = get_data_t<Msg>;
    using message_type = message<get_id_t<Msg>, data_type>;
    return std::make_shared<message_type>(make_message_data_default<data_type>());
}

template <typename Configuration>
class LogicLoader {
    const InterfaceAccessorPtr& interfaces;

public:
    LogicLoader(const LCE::InterfaceAccessor::InterfaceAccessorPtr& ptr)
    : interfaces(ptr)
    {}

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("warping_control"),const InterfaceAccessorPtr& p) {
        using config_type = get_config_t<ANode>;
        WarpingControlLogic::Config config{};
            config.static_zone      = make_zone_data<get_t<config_type, is_static_zone>>();
            config.ar_zone          = make_zone_data<get_t<config_type, is_ar_zone>>();
            config.mat_div_factor   = get_t<config_type, is_mat_div_factor>{}; 
            config.mirror_angle_min = get_t<config_type, is_mirror_angle_min>{}; 
            config.mirror_angle_max = get_t<config_type, is_mirror_angle_max>{}; 
        return std::make_shared<CWarpingControlLogic>(p,config);
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("virtual_camera"),const InterfaceAccessorPtr& p ) {
        using config_type           = get_config_t<ANode>;
        using communication_type    = get_communication_t<ANode>;

        MessageBox mails{};
            for_each<get_outputs_t<communication_type>>([&mails](auto n){
                using msg_type = std::remove_pointer_t<decltype(n)>;
                mails.push_back(make_message<msg_type>());
            });

        VirtualCamera::MirrorAngles angles{};
            using mirror_angles_type = get_t<config_type, is_mirror_angles>;
            angles.min = get_min_t<mirror_angles_type>{};
            angles.max = get_max_t<mirror_angles_type>{};
        VirtualCamera::Config config{};
        config.scene            = get_t<config_type, is_scene>{};    
        config.mirror_angles    = angles;

        return std::make_shared<CVirtualCameraLogic>(p,config,std::move(mails));
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("fas_cluster_acc"),const InterfaceAccessorPtr& p ) {
        using config_type           = get_config_t<ANode>;
        using communication_type    = get_communication_t<ANode>;

        MessageBox mails{};
            for_each<get_outputs_t<communication_type>>([&mails](auto n){
                using msg_type = std::remove_pointer_t<decltype(n)>;
                mails.push_back(make_message<msg_type>());
            });

        FasClusterLogic::Config config{};
            config.scene    = get_t<config_type, is_scene>{};
            config.node     = get_t<config_type, is_node>{};
            for_each<get_t<config_type, is_nodes_show_hide>>([&config](auto n){
                using nshe_type = std::remove_pointer_t<decltype(n)>;
                config.nodes_show_hide.push_back(make_node_show_hide<nshe_type>());
            });
        return std::make_shared<CAccFasClusterLogic>(p,config,std::move(mails));
    }

    BusinessLogics operator()() {
        BusinessLogics logics;
        for_each<Configuration>([&logics, &interfaces = interfaces](auto n){
            using node_type = std::remove_pointer_t<decltype(n)>;
            std::cout << get_lib_t<node_type>::value() << std::endl;
            logics.push_back(
                createLogic<node_type>(get_name_t<node_type>{}, interfaces)
            );    
        });
        return logics;
    }
};


// clang-format on

