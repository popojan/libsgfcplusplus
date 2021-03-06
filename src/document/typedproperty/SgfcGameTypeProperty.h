#pragma once

// Project includes
#include "../../../include/ISgfcGameTypeProperty.h"
#include "../SgfcProperty.h"

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcNumberPropertyValue;

  /// @brief The SgfcGameTypeProperty class provides an implementation of
  /// the ISgfcGameTypeProperty interface. See the interface header file
  /// for documentation.
  class SgfcGameTypeProperty : public SgfcProperty, public ISgfcGameTypeProperty
  {
  public:
    /// @brief Initializes a newly constructed SgfcGameTypeProperty object. The
    /// property has no value.
    SgfcGameTypeProperty();

    /// @brief Initializes a newly constructed SgfcGameTypeProperty object. The
    /// property has the specified property value @a propertyValue.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// null or if the @a propertyValue object's method HasTypedValue() returns
    /// false.
    SgfcGameTypeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue);

    /// @brief Destroys and cleans up the SgfcGameTypeProperty object.
    virtual ~SgfcGameTypeProperty();

    virtual const ISgfcGameTypeProperty* ToGameTypeProperty() const;

    virtual SgfcGameType GetGameType() const;
    virtual SgfcNumber GetGameTypeAsNumber() const;
  };
}
