#pragma once

#include "Config.hpp"
#include "../include/IInterfaceAccessor.hpp"
#include "../include/IBusinessLogic.hpp"

namespace ARCreatorLogic {

//ILC_DEFINE_IO_TYPE(
//    ILCEyeBoxSettingsChanged,
//    EyeBoxSettingsChanged,
//    "eye_box_settings_changed_out")

struct EyeBoxSettingsChanged 
{
}; 

///
/// @brief The CVirtualCameraLogic class controls virtual camera pose on AR scene
///
class CVirtualCameraLogic : public LCE::Logic::IBusinessLogic
{
public: // methods
    ///
    /// @brief CVirtualCameraLogic constructor
    /// @param interface_accessor Accessor to external interfaces or internal LCE interfaces
    /// @param config Logic configuration
    ///
    explicit CVirtualCameraLogic(
        const LCE::InterfaceAccessor::InterfaceAccessorPtr& interface_accessor,
        const VirtualCamera::Config& config);

    ///
    /// @brief initialize Fetch controlled scene graph
    ///
    void initialize() override;
    ///
    /// @brief start Set virtual camera to zero position
    ///
    void start() override;
    ///
    /// @brief iterate Process ego pose signals from EnvFusion.
    ///        Process EyeBox and HUD mirror positions from settings.
    ///        Update virtual camera pose.
    ///
    void iterate() override;
    ///
    /// @brief stop Do nothing
    ///
    void stop() override;

};

} // namespace ARCreatorLogic
