// Project includes
#include "SgfcNumberPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcNumberPropertyValue::SgfcNumberPropertyValue(const std::string& rawValue, long numberValue)
    : SgfcSinglePropertyValue(rawValue)
    , numberValue(numberValue)
  {
  }

  SgfcNumberPropertyValue::SgfcNumberPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage)
    : SgfcSinglePropertyValue(rawValue, typeConversionErrorMessage)
    , numberValue(0)
  {
  }

  SgfcNumberPropertyValue::~SgfcNumberPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcNumberPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Number;
  }

  long SgfcNumberPropertyValue::GetNumberValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->numberValue;
  }

  const ISgfcNumberPropertyValue* SgfcNumberPropertyValue::ToNumberValue() const
  {
    return this;
  }
}
