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

    template <typename ANode>
    static BusinessLogicPtr process(SL("warping_control"),const InterfaceAccessorPtr& p) {
        using config_type = typename ANode::config_type;
        using static_zone_type = tl::nth_element_t<config_type,0>;
        using ar_zone_type = tl::nth_element_t<config_type,1>;
        using mat_div_factor_type = typename tl::nth_element_t<config_type,2>::type;
        using mirror_angle_min_type = typename tl::nth_element_t<config_type,3>::type;
        using mirror_angle_max_type = typename tl::nth_element_t<config_type,4>::type;

        using sz_name_type = typename static_zone_type::name_type;
        return {};
    }

    template <typename ANode>
    static BusinessLogicPtr process(SL("virtual_camera"),const InterfaceAccessorPtr& p ) {
        using lib_type = typename ANode::lib_type;
        std::cout << lib_type::value() << std::endl;
        return {};
    }

    template <typename ANode>
    static BusinessLogicPtr process(SL("fas_cluster_acc"),const InterfaceAccessorPtr& p ) {
        using lib_type = typename ANode::lib_type;
        std::cout << lib_type::value() << std::endl;
       return {};
    }

    BusinessLogics operator()() {
        BusinessLogics logics;
        tl::rt::for_each<Configuration>([&logics, &interfaces = interfaces](auto n){
            using node_type = std::remove_pointer_t<decltype(n)>;
            logics.push_back(
                process<node_type>(typename node_type::name_type{}, interfaces)
            );    
        });
        return logics;
    }
};


// clang-format on

