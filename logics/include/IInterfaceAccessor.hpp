#pragma once

#include <memory>

namespace LCE {
namespace InterfaceAccessor {


///
/// @brief Interface to access LCE interface available for business logics
///
class IInterfaceAccessor
{
public: // methods
    virtual ~IInterfaceAccessor() = default;
};

using InterfaceAccessorPtr = std::shared_ptr<IInterfaceAccessor>;
using InterfaceAccessorWeakPtr = std::weak_ptr<IInterfaceAccessor>;

} // namespace InterfaceAccessor
} // namespace LCE
