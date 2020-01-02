#include "CAccFasClusterLogic.hpp"
#include <iostream>

namespace ARCreatorLogic {

CAccFasClusterLogic::CAccFasClusterLogic(
    const LCE::InterfaceAccessor::InterfaceAccessorPtr& interface_accessor,
    const FasClusterLogic::Config& config)
{
    std::cout << "CAccFasClusterLogic - business logic created!" << std::endl;
}

void CAccFasClusterLogic::initialize()
{
    std::cout << "CAccFasClusterLogic::initialize() primitives created." << std::endl;
}

void CAccFasClusterLogic::start()
{
    std::cout << "CAccFasClusterLogic::start()" << std::endl;
}

void CAccFasClusterLogic::iterate()
{
    std::cout << "CAccFasClusterLogic::iterate()" << std::endl;
}

void CAccFasClusterLogic::stop()
{
    std::cout << "CAccFasClusterLogic::stop()" << std::endl;
}

} // namespace ARCreatorLogic

// Defines plugin interfaces to create declared logic from dynamically loaded shared library
// DEFINE_LCE_PLUGIN(ARCreatorLogic::CAccFasClusterLogic)
