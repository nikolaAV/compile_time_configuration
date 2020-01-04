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
        using namespace tag;            
        using config_type = typename ANode::config_type;
        using mat_div_factor_type = get_t<config_type, is_mat_div_factor>;
        using mirror_angle_min_type = get_t<config_type, is_mirror_angle_min>;
        using mirror_angle_max_type = get_t<config_type, is_mirror_angle_max>;
        std::cout << "mat_div_factor_type" << (double)mat_div_factor_type{} << std::endl;
        std::cout << "mirror_angle_min_type" << mirror_angle_min_type::value() << std::endl;
        std::cout << "mirror_angle_max_type" << mirror_angle_max_type::value() << std::endl;

        {
            using static_zone_type = get_t<config_type, is_static_zone>;
            using name_type = typename static_zone_type::name_type;
            using width_type = typename static_zone_type::width_type;
            using height_type = typename static_zone_type::height_type;

            std::cout << "--- static_zone_type ---" << std::endl;
            std::cout << "name_type" << name_type::value() << std::endl;
            std::cout << "width_type" << width_type::value() << std::endl;
            std::cout << "height_type" << height_type::value() << std::endl;
        }    


        using ar_zone_type = get_t<config_type, is_ar_zone>;


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

