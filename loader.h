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

template <typename Configuration>
class LogicLoader {
    const InterfaceAccessorPtr& interfaces;

public:
    LogicLoader(const LCE::InterfaceAccessor::InterfaceAccessorPtr& ptr)
    : interfaces(ptr)
    {}

    template <typename Zone>
    static auto createZoneData() {
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

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("warping_control"),const InterfaceAccessorPtr& p) {
        using config_type = get_config_t<ANode>;
        WarpingControlLogic::Config config{};
            config.static_zone      = createZoneData<get_t<config_type, is_static_zone>>();
            config.ar_zone          = createZoneData<get_t<config_type, is_ar_zone>>();
            config.mat_div_factor   = get_t<config_type, is_mat_div_factor>{}; 
            config.mirror_angle_min = get_t<config_type, is_mirror_angle_min>{}; 
            config.mirror_angle_max = get_t<config_type, is_mirror_angle_max>{}; 
        return std::make_shared<CWarpingControlLogic>(p,config);
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("virtual_camera"),const InterfaceAccessorPtr& p ) {
        using config_type           = get_config_t<ANode>;
        using communication_type    = get_communication_t<ANode>;

        VirtualCamera::MirrorAngles angles{};
            using mirror_angles_type = get_t<config_type, is_mirror_angles>;
            angles.min = get_min_t<mirror_angles_type>{};
            angles.max = get_max_t<mirror_angles_type>{};
        VirtualCamera::Config config{};
        config.scene            = get_t<config_type, is_scene>{};    
        config.mirror_angles    = angles;

        return std::make_shared<CVirtualCameraLogic>(p,config);
    }

    template <typename Nshe>
    static auto createNodeShowHide() {
        FasClusterLogic::ShowHideNode node{};
            node.scene  = get_scene_t<Nshe>{};
            node.node   = get_node_t<Nshe>{};
            node.ar     = get_ar_t<Nshe>{};
        return node;
    }

    template <typename Msg>
    static auto createMessage() {
        using id_type = typename Msg::id_type;
        using data_type = typename Msg::data_type;
        using message_type = message<id_type, data_type>;
        return std::make_shared<message_type>(make_message_data_default<data_type>());
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("fas_cluster_acc"),const InterfaceAccessorPtr& p ) {
        using config_type = get_config_t<ANode>;
        using scene_type = get_t<config_type, is_scene>;
        using node_type = get_t<config_type, is_node>;
        using nodes_show_hide_type = get_t<config_type, is_nodes_show_hide>;
        using communication_type = get_communication_t<ANode>;
        using inputs_type = get_inputs_t<communication_type>;
        using outputs_type = get_outputs_t<communication_type>;


        MessageBox mails{};
            tl::rt::for_each<typename outputs_type::type>([&mails](auto n){
                using msg_type = std::remove_pointer_t<decltype(n)>;
                mails.push_back(createMessage<msg_type>());
            });

        FasClusterLogic::Config config{};
            config.scene = scene_type{};
            config.node = node_type{};
            tl::rt::for_each<typename nodes_show_hide_type::type>([&config](auto n){
                using nshe_type = std::remove_pointer_t<decltype(n)>;
                config.nodes_show_hide.push_back(createNodeShowHide<nshe_type>());
            });
        return std::make_shared<CAccFasClusterLogic>(p,config,std::move(mails));
    }

    BusinessLogics operator()() {
        BusinessLogics logics;
        tl::rt::for_each<Configuration>([&logics, &interfaces = interfaces](auto n){
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

