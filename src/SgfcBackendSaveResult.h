#pragma once

// Project includes
#include "../include/ISgfcMessage.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcBackendSaveResult class provides provides access to the
  /// result of a save operation performed by SgfcBackendController.
  class SgfcBackendSaveResult
  {
  public:
    /// @brief Initializes a newly constructed SgfcBackendSaveResult object
    /// with the specified results.
    SgfcBackendSaveResult(
      std::vector<std::shared_ptr<ISgfcMessage>> saveResult);
    virtual ~SgfcBackendSaveResult();

    /// @brief Returns a collection of ISgfcMessage objects which together form
    /// the result of the save operation. The messages appear in the order in
    /// which they were generated by SGFC.
    std::vector<std::shared_ptr<ISgfcMessage>> GetSaveResult() const;

  private:
    std::vector<std::shared_ptr<ISgfcMessage>> saveResult;
  };
}