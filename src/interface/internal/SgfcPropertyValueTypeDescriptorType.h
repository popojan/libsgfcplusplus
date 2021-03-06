#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcPropertyValueTypeDescriptorType enumerates all types of
  /// ISgfcPropertyValueTypeDescriptor objects.
  enum class SgfcPropertyValueTypeDescriptorType
  {
    DualValueType,
    ElistValueType,
    ListValueType,
    ComposedValueType,
    BasicValueType,
  };
}
