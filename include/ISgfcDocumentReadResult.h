#pragma once

// Project includes
#include "ISgfcDocument.h"
#include "ISgfcMessage.h"
#include "SgfcExitCode.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcDocumentReadResult interface provides access to the result
  /// of a read operation performed by ISgfcDocumentReader.
  ///
  /// ISgfcDocumentReadResult is immutable, i.e. once the
  /// ISgfcDocumentReadResult object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcDocumentReadResult
  {
  public:
    /// @brief Initializes a newly constructed ISgfcDocumentReadResult object.
    ISgfcDocumentReadResult();

    /// @brief Destroys and cleans up the ISgfcDocumentReadResult object.
    virtual ~ISgfcDocumentReadResult();

    /// @brief Returns an SgfcExitCode value that best fits the result of the
    /// read operation. The numeric value of the SgfcExitCode corresponds to
    /// one of the exit codes of SGFC.
    virtual SgfcExitCode GetExitCode() const = 0;

    /// @brief Returns true if the SGF data that was loaded and parsed by the
    /// read operation is valid. Returns false if the SGF data is not valid.
    ///
    /// The SGF data is considered valid if the read operation did not
    /// generate a fatal error. A fatal error shows up in the collection of
    /// ISgfcMessage objects that GetParseResult() returns, as an ISgfcMessage
    /// object with message type #SgfcMessageType::FatalError.
    ///
    /// @todo The SGF data should probably also be considered invalid if
    /// there were critical errors.
    virtual bool IsSgfDataValid() const = 0;

    /// @brief Returns a collection of ISgfcMessage objects which together form
    /// the parse result of the read operation. The messages appear in the order
    /// in which they were generated by SGFC.
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const = 0;

    /// @brief Returns the document object that provides access to the SGF data
    /// in structured form. If IsSgfDataValid() returns false the document
    /// object that is returned contains no data.
    virtual std::shared_ptr<ISgfcDocument> GetDocument() const = 0;
  };
}
