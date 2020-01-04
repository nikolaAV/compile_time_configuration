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

template <typename Configuration>
class LogicLoader {
    const InterfaceAccessorPtr& interfaces;

public:
    LogicLoader(const LCE::InterfaceAccessor::InterfaceAccessorPtr& ptr)
    : interfaces(ptr)
    {}


    template <typename Zone>
    static auto createZoneData() {
        using name_type = typename Zone::name_type;
        using width_type = typename Zone::width_type;
        using height_type = typename Zone::height_type;

        ARCreatorLogic::WarpingControlLogic::ZoneData zone{};
        zone.name = name_type{};
        zone.width = width_type{};
        zone.height = height_type{}; 
        zone.mirror_pos = {}; // not implemented yet 
        return zone;
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("warping_control"),const InterfaceAccessorPtr& p) {
        using namespace tag;            
        using config_type = typename ANode::config_type;
        using mat_div_factor_type = get_t<config_type, is_mat_div_factor>;
        using mirror_angle_min_type = get_t<config_type, is_mirror_angle_min>;
        using mirror_angle_max_type = get_t<config_type, is_mirror_angle_max>;

        ARCreatorLogic::WarpingControlLogic::Config config{};
        config.static_zone = createZoneData<get_t<config_type, is_static_zone>>();
        config.ar_zone = createZoneData<get_t<config_type, is_ar_zone>>();
        config.mat_div_factor = mat_div_factor_type{}; 
        config.mirror_angle_min = mirror_angle_min_type{}; 
        config.mirror_angle_max = mirror_angle_max_type{}; 

        return std::make_shared<ARCreatorLogic::CWarpingControlLogic>(p,config);
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("virtual_camera"),const InterfaceAccessorPtr& p ) {
        using lib_type = typename ANode::lib_type;
        std::cout << lib_type::value() << std::endl;
        return {};
    }

    template <typename ANode>
    static BusinessLogicPtr createLogic(SL("fas_cluster_acc"),const InterfaceAccessorPtr& p ) {
        using lib_type = typename ANode::lib_type;
        std::cout << lib_type::value() << std::endl;
       return {};
    }

    BusinessLogics operator()() {
        BusinessLogics logics;
        tl::rt::for_each<Configuration>([&logics, &interfaces = interfaces](auto n){
            using node_type = std::remove_pointer_t<decltype(n)>;
            logics.push_back(
                createLogic<node_type>(typename node_type::name_type{}, interfaces)
            );    
        });
        return logics;
    }
};


// clang-format on

