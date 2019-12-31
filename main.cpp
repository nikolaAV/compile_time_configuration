#include <string>
#include <iostream>
#include "tag_types.h"

/*
    g++ main.cpp -std=c++14 -o exe
*/

// Example of usage

using namespace tag;

using configuration = tl::list<
    anode<
         name<SL("warping_control")>
        ,lib <SL("libwarping_control_logic.so")>
        ,config<
            static_zone<
                name<SL("StatusZone_Warping")>
                ,width<DL("21")>
                ,height<DL("21")>
                ,mirror_pos<FL("-0.035"),FL("0.0"),FL("0.035")>
            >
            ,ar_zone<
                name<SL("ARZone_Warping")>
                ,width<DL("21")>
                ,height<DL("21")>
                ,mirror_pos<FL("-0.035"),FL("0.0"),FL("0.035")>
            >
            ,mat_div_factor<FL("16.0")>
            ,mirror_angle_min<FL("-0.035")>
            ,mirror_angle_max<FL("0.035")>
        >
        ,communication<
            inputs<>
            ,outputs<>
        >
    >
   ,anode<
         name<SL("virtual_camera")>
        ,lib <SL("libvirtual_camera_logic.so")>
        ,config<
             scene<SL("ArScene")>
            ,mirror_angles<
                 min<FL("-0.035")>
                ,max<FL("0.035")>
            >
        >
        ,communication<
            inputs<>
            ,outputs<SL("eye_box_settings_changed_out")>
        >
   >
   ,anode<
         name<SL("fas_cluster_acc")>
        ,lib <SL("libfas_cluster_acc_logic.so")>
        ,config<
             scene<SL("StaticScene")>
            ,node<SL("fasc")>
            ,nodes_show_hide<
                 nshe<scene<SL("StaticScene")>,node<SL("warn_acc_tor_sl")>,ar<BL("false")>>
                ,nshe<scene<SL("ArScene")>,node<SL("warn_acc_tor_ar1")>,ar<BL("true")>>
                ,nshe<scene<SL("ArScene")>,node<SL("warn_acc_tor_ar2")>,ar<BL("true")>>
            >
        >
        ,communication<
             inputs<>
            ,outputs<SL("acc_fas_cluster_on_off"),SL("acc_fas_cluster_hide_show_sl"),SL("acc_fas_cluster_hide_show_ar"), SL("acc_fas_cluster_pea_hidden_shown"), SL("acc_fas_cluster_pea_radar_waves_hidden_shown")>
        >
   >
>;

using namespace std;


struct visitor {
    template <typename T>
    void operator()(T*) {
        using node_type = T;
        using name_type = typename node_type::name_type;
        using lib_type = typename node_type::lib_type;
        using config_type = typename node_type::config_type;
        using communication_type = typename node_type::communication_type;

        cout << name_type::value() << ", " << lib_type::value() << endl;
    }
};

int main()
{
    tl::rt::for_each<configuration>(visitor{});


    cin.get();
}
