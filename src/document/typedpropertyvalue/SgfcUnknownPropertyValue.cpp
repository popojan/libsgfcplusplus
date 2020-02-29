// Project includes
#include "SgfcUnknownPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcUnknownPropertyValue::SgfcUnknownPropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(rawValue)
  {
  }

  SgfcUnknownPropertyValue::~SgfcUnknownPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcUnknownPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Unknown;
  }
}
