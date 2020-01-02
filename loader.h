#pragma once

// clang-format off

#include "tag_types.h"
#include "logics/include/IBusinessLogic.hpp"
#include "logics/include/IInterfaceAccessor.hpp"
#include <vector>

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
        using lib_type = typename ANode::lib_type;
        std::cout << lib_type::value() << std::endl;
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

