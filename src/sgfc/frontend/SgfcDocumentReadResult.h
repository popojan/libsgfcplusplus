#pragma once

// Project includes
#include "../../../include/ISgfcDocumentReadResult.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocumentReadResult class provides an implementation of the
  /// ISgfcDocumentReadResult interface. See the interface header file for
  /// documentation.
  class SgfcDocumentReadResult : public ISgfcDocumentReadResult
  {
  public:
    SgfcDocumentReadResult();
    SgfcDocumentReadResult(
      std::vector<std::shared_ptr<ISgfcMessage>> parseResult,
      std::shared_ptr<ISgfcDocument> document);
    virtual ~SgfcDocumentReadResult();

    virtual SgfcExitCode GetExitCode() const;
    virtual bool IsSgfDataValid() const;
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const;
    virtual std::shared_ptr<ISgfcDocument> GetDocument() const;

  private:
    SgfcExitCode exitCode;
    bool isSgfDataValid;
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult;
    std::shared_ptr<ISgfcDocument> document;
  };
}
