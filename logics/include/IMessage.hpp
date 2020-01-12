#pragma once

#include <memory>
#include <vector>

// clang-format off

namespace ARCreatorLogic 
{

struct IMessage {
    IMessage() = default;
    virtual ~IMessage() = default;

    virtual void send() const = 0; 
};

using MessagePtr = std::shared_ptr<IMessage>;
using MessageBox = std::vector<MessagePtr>;

} // namespace ARCreatorLogic

// clang-format on

