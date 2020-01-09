#include <iostream>
#include <cassert>
#include "CWarpingControlLogic.hpp"

namespace ARCreatorLogic {

using namespace WarpingControlLogic;
using namespace std;

ostream& operator<<(ostream& out, const MirrorData& data)
{
    assert(data.size()==3);
    return out  
        << "{" 
        << data[0] << ","
        << data[1] << ","
        << data[2] << ""
        << "}";
}

ostream& operator<<(ostream& out, const ZoneData& data)
{
    return out
        << "\tname : " << data.name << endl 
        << "\twidth : " << data.width << endl
        << "\theight : " << data.height << endl
        << "\tMirrorData : " << data.mirror_pos;
}

ostream& operator<<(ostream& out, const Config& data)
{
    return out  
        << "\tmat_div_factor : " << data.mat_div_factor << endl
        << "\tmirror_angle_min : " << data.mirror_angle_min << endl
        << "\tmirror_angle_max : " << data.mirror_angle_max << endl
        << "\t--- static_zone ---" << endl
        << data.static_zone  << endl
        << "\t--- ar_zone ---" << endl
        << data.ar_zone  << endl;
}

CWarpingControlLogic::CWarpingControlLogic(
    const LCE::InterfaceAccessor::InterfaceAccessorPtr& interfaces,
    const Config& config)
{
    cout << "WarpingControlLogic - business logic created!" << endl;
    cout << config << endl;
}

void CWarpingControlLogic::initialize()
{
    cout << "WarpingControlLogic::initialize()" << endl;
}

void CWarpingControlLogic::start()
{
    cout << "WarpingControlLogic::start()" << endl;
}

void CWarpingControlLogic::iterate()
{
    cout << "WarpingControlLogic::iterate()" << endl;
}

void CWarpingControlLogic::stop()
{
    cout << "WarpingControlLogic::stop()" << endl;
}

} // namespace ARCreatorLogic

// Defines plugin interfaces to create declared logic from dynamically loaded shared library
// DEFINE_LCE_PLUGIN(ARCreatorLogic::CWarpingControlLogic)
