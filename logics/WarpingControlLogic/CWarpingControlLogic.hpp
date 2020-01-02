#pragma once

#include "Config.hpp"
#include "../include/IInterfaceAccessor.hpp"
#include "../include/IBusinessLogic.hpp"

namespace ARCreatorLogic {

///
/// @brief The CWarpingControlLogic class controls applying of warping matrices
///        to different warping areas on HMI
///
class CWarpingControlLogic : public LCE::Logic::IBusinessLogic
{

public: // methods
    ///
    /// @brief CWarpingControlLogic constructor
    /// @param interface_accessor Accessor to external interfaces or internal LCE interfaces
    /// @param config Logic configuration
    ///
    CWarpingControlLogic(
        const LCE::InterfaceAccessor::InterfaceAccessorPtr& interfaces,
        const WarpingControlLogic::Config& config);

    ///
    /// @brief initialize Do nothing
    ///
    void initialize() override;
    ///
    /// @brief start Do nothing
    ///
    void start() override;
    ///
    /// @brief iterate Process warping configuration
    ///        and apply warping metrices to appropriate areas on HMI
    ///
    void iterate() override;
    ///
    /// @brief stop Do nothing
    ///
    void stop() override;
};

} // namespace ARCreatorLogic
