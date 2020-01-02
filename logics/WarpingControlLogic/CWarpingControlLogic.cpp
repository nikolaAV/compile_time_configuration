#include <iostream>
#include "CWarpingControlLogic.hpp"

namespace ARCreatorLogic {

using namespace WarpingControlLogic;

CWarpingControlLogic::CWarpingControlLogic(
    const LCE::InterfaceAccessor::InterfaceAccessorPtr& interfaces,
    const Config& config)
{
    std::cout << "[WarpingControlLogic] - business logic created!" << std::endl;
}

void CWarpingControlLogic::initialize()
{
    std::cout << "[WarpingControlLogic]::initialize()" << std::endl;
}

void CWarpingControlLogic::start()
{
    std::cout << "[WarpingControlLogic]::start()" << std::endl;
}

void CWarpingControlLogic::iterate()
{
    std::cout << "[WarpingControlLogic]::iterate()" << std::endl;
}

void CWarpingControlLogic::stop()
{
    std::cout << "[WarpingControlLogic]::stop()" << std::endl;
}

} // namespace ARCreatorLogic

// Defines plugin interfaces to create declared logic from dynamically loaded shared library
// DEFINE_LCE_PLUGIN(ARCreatorLogic::CWarpingControlLogic)
