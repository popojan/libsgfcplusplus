#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcRealPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Real.
  ///
  /// ISgfcRealPropertyValue is immutable, i.e. once the
  /// ISgfcRealPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcRealPropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcRealPropertyValue object.
    ISgfcRealPropertyValue();

    /// @brief Destroys and cleans up the ISgfcRealPropertyValue object.
    virtual ~ISgfcRealPropertyValue();

    /// @brief Returns the property value interpreted as a signed floating point
    /// number.
    ///
    /// @exception std::logic_error Is thrown if HasTypedValue() returns false.
    virtual SgfcReal GetRealValue() const = 0;
  };
}
