// Project includes
#include "SgfcProperty.h"

namespace LibSgfcPlusPlus
{
  SgfcProperty::SgfcProperty()
    : propertyType(SgfcPropertyType::Unknown)
  {
  }

  SgfcProperty::SgfcProperty(
    SgfcPropertyType propertyType,
    const std::string& propertyName,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
    : propertyType(propertyType)
    , propertyName(propertyName)
    , propertyValues(propertyValues)
  {
  }

  SgfcProperty::~SgfcProperty()
  {
  }

  SgfcPropertyType SgfcProperty::GetPropertyType() const
  {
    return this->propertyType;
  }

  std::string SgfcProperty::GetPropertyName() const
  {
    return this->propertyName;
  }

  std::vector<std::shared_ptr<ISgfcPropertyValue>> SgfcProperty::GetPropertyValues() const
  {
    return this->propertyValues;
  }
}