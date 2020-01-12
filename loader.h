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

template <typename Configuration>
class LogicLoader {
    const InterfaceAccessorPtr& interfaces;

public:
    LogicLoader(const LCE::InterfaceAccessor::InterfaceAccessorPtr& ptr)
    : interfaces(ptr)
    {}

    template <typename Zone>
    static auto createZoneData() {
        ARCreatorLogic::WarpingControlLogic::ZoneData zone{};
            zone.name = get_name_t<Zone>{};
            zone.width = get_width_t<Zone>{};
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
        std::cout << get_lib_t<ANode>::value() << std::endl;

        using config_type = get_config_t<ANode>;
        ARCreatorLogic::WarpingControlLogic::Config config{};
            config.static_zone = createZoneData<get_t<config_type, is_static_zone>>();
            config.ar_zone = createZoneData<get_t<config_type, is_ar_zone>>();
            config.mat_div_factor = get_t<config_type, is_mat_div_factor>{}; 
            config.mirror_angle_min = get_t<config_type, is_mirror_angle_min>{}; 
            config.mirror_angle_max = get_t<config_type, is_mirror_angle_max>{}; 

        return std::make_shared<ARCreatorLogic::CWarpingControlLogic>(p,config);
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("virtual_camera"),const InterfaceAccessorPtr& p ) {
        std::cout << get_lib_t<ANode>::value() << std::endl;

        using config_type = get_config_t<ANode>;
        using communication_type = get_communication_t<ANode>;

        ARCreatorLogic::VirtualCamera::MirrorAngles angles{};
            using mirror_angles_type = get_t<config_type, is_mirror_angles>;
            angles.min = get_min_t<mirror_angles_type>{};
            angles.max = get_max_t<mirror_angles_type>{};
        ARCreatorLogic::VirtualCamera::Config config{};
        config.scene = get_t<config_type, is_scene>{};    
        config.mirror_angles = angles;

        return std::make_shared<ARCreatorLogic::CVirtualCameraLogic>(p,config);
    }

    template <typename Nshe>
    static auto createNodeShowHide() {
        ARCreatorLogic::FasClusterLogic::ShowHideNode node{};
            node.scene = get_scene_t<Nshe>{};
            node.node = get_node_t<Nshe>{};
            node.ar = get_ar_t<Nshe>{};
        return node;
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("fas_cluster_acc"),const InterfaceAccessorPtr& p ) {
        std::cout << get_lib_t<ANode>::value() << std::endl;

        using config_type = get_config_t<ANode>;
        using scene_type = get_t<config_type, is_scene>;
        using node_type = get_t<config_type, is_node>;
        using nodes_show_hide_type = get_t<config_type, is_nodes_show_hide>;
        using communication_type = get_communication_t<ANode>;
        using inputs_type = get_inputs_t<communication_type>;
        using outputs_type = get_outputs_t<communication_type>;

        using on_off_type = tl::nth_element_t<typename outputs_type::type,0>;
        ARCreatorLogic::make_message<typename on_off_type::id_type, typename on_off_type::data_type>(true);
        using hide_show_ar_type = tl::nth_element_t<typename outputs_type::type,2>;
        ARCreatorLogic::make_message<typename hide_show_ar_type::id_type, typename hide_show_ar_type::data_type>("some text", false);
        using pea_hidden_shown_type = tl::nth_element_t<typename outputs_type::type,3>;
        ARCreatorLogic::make_message<typename pea_hidden_shown_type::id_type, typename pea_hidden_shown_type::data_type>(false);

        ARCreatorLogic::FasClusterLogic::Config config{};
            config.scene = scene_type{};
            config.node = node_type{};
            tl::rt::for_each<typename nodes_show_hide_type::type>([&config](auto n){
                using nshe_type = std::remove_pointer_t<decltype(n)>;
                config.nodes_show_hide.push_back(createNodeShowHide<nshe_type>());
            });
        return std::make_shared<ARCreatorLogic::CAccFasClusterLogic>(p,config);;
    }

    BusinessLogics operator()() {
        BusinessLogics logics;
        tl::rt::for_each<Configuration>([&logics, &interfaces = interfaces](auto n){
            using node_type = std::remove_pointer_t<decltype(n)>;
            logics.push_back(
                createLogic<node_type>(get_name_t<node_type>{}, interfaces)
            );    
        });
        return logics;
    }
};


// clang-format on

