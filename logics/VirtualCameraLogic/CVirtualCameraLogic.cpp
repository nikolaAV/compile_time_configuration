#include "CVirtualCameraLogic.hpp"
#include <iostream>


namespace ARCreatorLogic {

using namespace std;
using namespace VirtualCamera;

ostream& operator<<(ostream& out, const MirrorAngles& data)
{
    return out  
        << "\tmin : " << data.min << endl
        << "\tmax : " << data.max << endl;
}

ostream& operator<<(ostream& out, const Config& data)
{
    return out  
        << "\tscene : " << data.scene << endl
        << "\t--- mirror_angles ---" << endl
        << data.mirror_angles  << endl;
}


CVirtualCameraLogic::CVirtualCameraLogic(
    const LCE::InterfaceAccessor::InterfaceAccessorPtr& interface_accessor,
    const VirtualCamera::Config& config,
    MessageBox&& message_box)
    : message_box_(std::move(message_box))
{
    std::cout << "CVirtualCameraLogic - business logic created!" << std::endl;
    cout << config << endl;
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
    for(const auto& m : message_box_)
        m->send();
}

void CVirtualCameraLogic::stop()
{
    std::cout << "CVirtualCameraLogic::stop()" << std::endl;
}


} // namespace ARCreatorLogic

// Defines plugin interfaces to create declared logic from dynamically loaded shared library
//DEFINE_LCE_PLUGIN(ARCreatorLogic::CVirtualCameraLogic)
