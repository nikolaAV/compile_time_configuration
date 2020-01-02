#pragma once

#include "Config.hpp"
#include "../include/IInterfaceAccessor.hpp"
#include "../include/IBusinessLogic.hpp"

namespace ARCreatorLogic {

/*
// Declarations of logic communications
// output message for logic on/off notifications
ILC_DEFINE_IO_TYPE(ILCAccFasClusterOnOff, AccFasClusterLogic::OnOff, "acc_fas_cluster_on_off")

// output message for scene nodes Hidden/Shown on Status Line scene
ILC_DEFINE_IO_TYPE(
    ILCAccFasClusterHiddenShownSL,
    AccFasClusterLogic::HiddenShown,
    "acc_fas_cluster_hide_show_sl")

// output message for scene nodes Hidden/Shown on AR-area scene
ILC_DEFINE_IO_TYPE(
    ILCAccFasClusterHiddenShownAR,
    AccFasClusterLogic::HiddenShown,
    "acc_fas_cluster_hide_show_ar")

// output message for scene nodes Hidden/Shown on AR-area scene
ILC_DEFINE_IO_TYPE(
    ILCAccFasClusterPACCHiddenShown,
    AccFasClusterLogic::HiddenShownEvent,
    "acc_fas_cluster_pea_hidden_shown")

// output message for scene nodes Hidden/Shown on AR-area scene
ILC_DEFINE_IO_TYPE(
    ILCAccFasClusterRadarWavesHiddenShown,
    AccFasClusterLogic::HiddenShownEvent,
    "acc_fas_cluster_pea_radar_waves_hidden_shown")
*/

///
/// @brief The CAccFasClusterLogic class controls ACC/ACA/pACA features
///
class CAccFasClusterLogic : public LCE::Logic::IBusinessLogic
{
public: // methods
    ///
    /// @brief CAccFasClusterLogic constructor
    /// @param interface_accessor Accessor to external interfaces or internal LCE interfaces
    /// @param config Logic configuration
    ///
    CAccFasClusterLogic(
        const LCE::InterfaceAccessor::InterfaceAccessorPtr& interface_accessor,
        const FasClusterLogic::Config& config);

    ///
    /// @brief initialize Fetch controlled scene nodes
    ///
    void initialize() override;
    ///
    /// @brief start Do nothing
    ///
    void start() override;
    ///
    /// @brief iterate Process ACC signals.
    ///        Update objects properties on Scene Graph(HMI).
    ///        Send output messages
    ///
    void iterate() override;
    ///
    /// @brief stop Release controlled scene nodes
    ///
    void stop() override;
};

} // namespace ARCreatorLogic
