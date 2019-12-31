#include <string>
#include <iostream>
#include "tag_types.h"

/*
    g++ main.cpp -std=c++14 -o exe
*/

// Example of usage

using namespace tag;

using configuration = tl::list<
    node<
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
   ,node<
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
>;

using namespace std;


struct visitor {
    template <typename T>
    void operator()(T*) {
        using node_type = T;
        using name_type = tl::front_t<typename node_type::list_type>;
        using value_type = tl::front_t<typename name_type::list_type>;
        cout << value_type::value() << endl;
    }
};

int main()
{
    tl::rt::for_each<configuration>(visitor{});


    cin.get();
}
