#pragma once

enum class EventResult
{
    Ignored,
    Handled, //  NOTE: event was handled, but can continue propagation
    Consumed //  NOTE: event was handled and should stop propagation
};
