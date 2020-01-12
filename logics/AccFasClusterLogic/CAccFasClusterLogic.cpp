#include "CAccFasClusterLogic.hpp"
#include <iostream>

namespace ARCreatorLogic {

using namespace FasClusterLogic;
using namespace std;

ostream& operator<<(ostream& out, const ShowHideNode& data)
{
    return out << "\t{" 
        << data.scene << ", " 
        << data.node << ", " 
        << boolalpha << data.ar <<
   "}";
}

ostream& operator<<(ostream& out, const vector<ShowHideNode>& data)
{
    for(const auto& n:data)
        out << n << endl;
    return out;
}

ostream& operator<<(ostream& out, const Config& data)
{
    return out  
        << "\tscene : " << data.scene << endl
        << "\tnode : " << data.node << endl
        << "\t--- nodes_show_hide ---" << endl
        << data.nodes_show_hide  << endl;
}

CAccFasClusterLogic::CAccFasClusterLogic(
    const LCE::InterfaceAccessor::InterfaceAccessorPtr& interface_accessor,
    const FasClusterLogic::Config& config,
    MessageBox&& message_box)
    : message_box_(std::move(message_box))
{
    cout << "CAccFasClusterLogic - business logic created!" << endl;
    cout << config << endl;
}


void CAccFasClusterLogic::initialize()
{
    cout << "CAccFasClusterLogic::initialize() primitives created." << endl;
}

void CAccFasClusterLogic::start()
{
    cout << "CAccFasClusterLogic::start()" << endl;
}

void CAccFasClusterLogic::iterate()
{
    cout << "CAccFasClusterLogic::iterate()" << endl;
    for(const auto& m : message_box_)
        m->send();
}

void CAccFasClusterLogic::stop()
{
    cout << "CAccFasClusterLogic::stop()" << endl;
}

} // namespace ARCreatorLogic

// Defines plugin interfaces to create declared logic from dynamically loaded shared library
// DEFINE_LCE_PLUGIN(ARCreatorLogic::CAccFasClusterLogic)
