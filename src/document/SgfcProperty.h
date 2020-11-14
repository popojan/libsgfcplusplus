// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

#pragma once

// Project includes
#include "../../include/ISgfcProperty.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcProperty class provides an implementation of the
  /// ISgfcProperty interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup property
  class SgfcProperty : virtual public ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed SgfcProperty object. The property
    /// has the specified type @a propertyType and name @a propertyName. The
    /// property has no values.
    SgfcProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName);

    /// @brief Initializes a newly constructed SgfcProperty object. The property
    /// has the specified type @a propertyType, name @a propertyName and
    /// property values @a propertyValues.
    SgfcProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Destroys and cleans up the SgfcProperty object.
    virtual ~SgfcProperty();

    virtual SgfcPropertyType GetPropertyType() const;
    virtual std::string GetPropertyName() const;

    virtual bool HasPropertyValues() const;
    virtual std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const;
    virtual void SetPropertyValues(const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);
    virtual void AppendPropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue);
    virtual void RemovePropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue);
    virtual void RemoveAllPropertyValues();
    virtual std::shared_ptr<ISgfcPropertyValue> GetPropertyValue() const;

    virtual const ISgfcGameTypeProperty* ToGameTypeProperty() const;
    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const;

  private:
    SgfcPropertyType propertyType;
    std::string propertyName;
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;
  };
}
