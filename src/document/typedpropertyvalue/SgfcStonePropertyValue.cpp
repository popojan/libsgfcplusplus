// Project includes
#include "SgfcStonePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcStonePropertyValue::SgfcStonePropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(rawValue, true)
  {
  }

  SgfcStonePropertyValue::~SgfcStonePropertyValue()
  {
  }

  SgfcPropertyValueType SgfcStonePropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Stone;
  }

  std::string SgfcStonePropertyValue::GetRawStoneValue() const
  {
    return SgfcSinglePropertyValue::GetRawValue();
  }

  const ISgfcStonePropertyValue* SgfcStonePropertyValue::ToStoneValue() const
  {
    return this;
  }

  const ISgfcGoStonePropertyValue* SgfcStonePropertyValue::ToGoStoneValue() const
  {
    return nullptr;
  }
}
