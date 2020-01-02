#pragma once

#include <memory>

namespace LCE {
namespace Logic {

///
/// @brief Interface for business logic that responsible for implementation of customer requirements
///
class IBusinessLogic
{
public:
    virtual ~IBusinessLogic() = default;

    ///
    /// @brief Will be called once during initialization step of LCE
    ///
    virtual void initialize() = 0;

    ///
    /// @brief Will be called once on the beggining of run step of LCE
    ///
    virtual void start() = 0;

    ///
    /// @brief Will be called on each LCE iteration
    ///
    virtual void iterate() = 0;

    ///
    /// @brief Will be called once during deinitialization step of LCE
    ///
    virtual void stop() = 0;
};

using BusinessLogicPtr = std::shared_ptr<IBusinessLogic>;

} // namespace Logic
} // namespace LCE
