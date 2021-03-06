#pragma once

// Project includes
#include "ISgfcGoStone.h"
#include "ISgfcStonePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoStonePropertyValue interface makes the property value
  /// data of a property of type SgfcPropertyValueType::Stone available as
  /// an ISgfcGoStone object.
  class SGFCPLUSPLUS_EXPORT ISgfcGoStonePropertyValue : virtual public ISgfcStonePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoStonePropertyValue object.
    ISgfcGoStonePropertyValue();

    /// @brief Destroys and cleans up the ISgfcGoStonePropertyValue object.
    virtual ~ISgfcGoStonePropertyValue();

    /// @brief Returns an ISgfcGoStone object that contains the property value
    /// data.
    virtual std::shared_ptr<ISgfcGoStone> GetGoStone() const = 0;
  };
}
