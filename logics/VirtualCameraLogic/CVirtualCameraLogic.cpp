#include "CVirtualCameraLogic.hpp"
#include <iostream>


namespace ARCreatorLogic {

CVirtualCameraLogic::CVirtualCameraLogic(
    const LCE::InterfaceAccessor::InterfaceAccessorPtr& interface_accessor,
    const VirtualCamera::Config& config)
{
    std::cout << "CVirtualCameraLogic - business logic created!" << std::endl;
}

void CVirtualCameraLogic::initialize()
{
    std::cout << "CVirtualCameraLogic::initialize()" << std::endl;
}

void CVirtualCameraLogic::start()
{
    std::cout << "CVirtualCameraLogic::start()" << std::endl;
}

void CVirtualCameraLogic::iterate()
{
    std::cout << "CVirtualCameraLogic::iterate()" << std::endl;
}

void CVirtualCameraLogic::stop()
{
    std::cout << "CVirtualCameraLogic::stop()" << std::endl;
}


} // namespace ARCreatorLogic

// Defines plugin interfaces to create declared logic from dynamically loaded shared library
//DEFINE_LCE_PLUGIN(ARCreatorLogic::CVirtualCameraLogic)
