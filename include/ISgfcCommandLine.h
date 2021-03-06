#pragma once

// Project includes
#include "ISgfcMessage.h"
#include "SgfcExitCode.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcCommandLine interface is used to operate the SGFC backend
  /// in command line mode. Use SgfcPlusPlusFactory to construct new
  /// ISgfcCommandLine objects.
  ///
  /// The ISgfcCommandLine interface is designed to give clients control over
  /// when they want to execute load and save operations, and how they want the
  /// operations to behave. Clients specify SGFC command line arguments when
  /// they construct the ISgfcCommandLine object. The SGFC command line
  /// arguments cannot be changed after construction.
  ///
  /// A client typically uses the ISgfcCommandLine interface by following this
  /// sequence, which corresponds to invoking SGFC on the command line with an
  /// input file path and an output file path.
  /// - Use SgfcPlusPlusFactory to construct the object.
  /// - Verify that SGFC command line arguments are valid.
  /// - If SGFC command line arguments are valid: Load SGF content.
  /// - Access parse results.
  /// - If SGF content is valid: Save SGF content.
  ///
  /// A client may deviate from this sequence e.g. by repeatedly loading SGF
  /// content without saving (syntax checking), or by repeatedly saving the
  /// same SGF content to different locations.
  ///
  /// A client that deviates from the sequence must still follow a certain
  /// common-sense protocol in using the interface:
  /// - It may not load SGF content if the SGFC command line arguments are not
  ///   valid. Use IsCommandLineValid() to check this.
  /// - It may not save SGF content that was found to be invalid during loading,
  ///   or save SGF content without prior loading any content. Use
  ///   IsSgfContentValid() to check this.
  class SGFCPLUSPLUS_EXPORT ISgfcCommandLine
  {
  public:
    /// @brief Initializes a newly constructed ISgfcCommandLine object.
    ISgfcCommandLine();

    /// @brief Destroys and cleans up the ISgfcCommandLine object.
    virtual ~ISgfcCommandLine();

    /// @brief Returns the SGFC command line arguments that were used to
    /// construct the ISgfcCommandLine object.
    virtual std::vector<std::string> GetArguments() const = 0;

    /// @brief Returns true if the SGFC command line arguments that
    /// GetArguments() returns are valid. Returns false if they are not valid.
    ///
    /// Some command line arguments are not allowed because they do not make
    /// sense when using SGFC in a library context, or in the particular context
    /// of SgfcCommandLine. The following arguments are not allowed:
    /// -h, --help, --version, -i, -c, -g, any non-option arguments (e.g. for
    /// the input or output file).
    ///
    /// @todo Specify other arguments that are not allowed.
    virtual bool IsCommandLineValid() const = 0;

    /// @brief Returns an ISgfcMessage object with message type
    /// #SgfcMessageType::FatalError that describes why the SGFC command
    /// line arguments that GetArguments() returns are not valid. This method
    /// may only be invoked if IsCommandLineValid() returns false.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// true.
    virtual std::shared_ptr<ISgfcMessage> GetInvalidCommandLineReason() const = 0;

    /// @brief Loads a single .sgf file from the specified path and puts it
    /// through the SGFC parser. This method may only be invoked if
    /// IsCommandLineValid() returns true.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual SgfcExitCode LoadSgfFile(const std::string& sgfFilePath) = 0;

    /// @brief Loads the specified SGF content and puts it through the SGFC
    /// parser. This method may only be invoked if IsCommandLineValid() returns
    /// true.
    ///
    /// The implementation of this method saves the specified SGF content to a
    /// temporary file and then instructs SGFC to load that file. After the
    /// load operation the implementation deletes the temporary file.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual SgfcExitCode LoadSgfContent(const std::string& sgfContent) = 0;

    /// @brief Returns true if the SGF content that was loaded and parsed by the
    /// most recent invocation of either LoadSgfFile() or LoadSgfContent() is
    /// valid. Returns false if the SGF content is not valid, or if none of the
    /// methods have been invoked yet.
    ///
    /// The SGF content is considered valid if LoadSgfFile() or LoadSgfContent()
    /// have been invoked at least once, and if their invocation did not
    /// generate a fatal error. A fatal error shows up in the collection of
    /// ISgfcMessage objects that GetParseResult() returns, as an ISgfcMessage
    /// object with message type #SgfcMessageType::FatalError.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual bool IsSgfContentValid() const = 0;

    /// @brief Returns a collection of ISgfcMessage objects which together form
    /// the parse result from the most recent invocation of either LoadSgfFile()
    /// or LoadSgfContent().
    ///
    /// The collection is empty if none of the methods have been invoked yet.
    ///
    /// If the collection is not empty, the messages appear in the order in
    /// which they were generated by SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const = 0;

    /// @brief Saves the SGF content generated by SGFC after the most recent
    /// invocation of either LoadSgfFile() or LoadSgfContent() to the .sgf
    /// file at the specified path. This method may only be invoked if
    /// IsSgfContentValid() returns true.
    ///
    /// If a file already exists at the specified path it is overwritten.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsSgfContentValid() returns
    /// false.
    virtual SgfcExitCode SaveSgfFile(const std::string& sgfFilePath) = 0;
  
    /// @brief Saves the SGF content generated by SGFC after the most recent
    /// invocation of either LoadSgfFile() or LoadSgfContent() into the
    /// specified string object. This method may only be invoked if
    /// IsSgfContentValid() returns true.
    ///
    /// The implementation of this method saves the generated SGF content to a
    /// temporary file and then loads the content of that file into the
    /// specified string object. After the load operation the implementation
    /// deletes the temporary file.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsSgfContentValid() returns
    /// false.
    virtual SgfcExitCode SaveSgfContent(std::string& sgfContent) = 0;

    /// @brief Returns a collection of ISgfcMessage objects which together form
    /// the result from the most recent invocation of either SaveSgfFile()
    /// or SaveSgfContent().
    ///
    /// The collection is empty if none of the methods have been invoked yet.
    ///
    /// If the collection is not empty, the messages appear in the order in
    /// which they were generated by SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetSaveResult() const = 0;
  };
}
