// Project includes
#include "../include/SgfcPlusPlusFactory.h"
#include "SgfcCommandLine.h"
#include "SgfcDocumentReader.h"

namespace LibSgfcPlusPlus
{
  std::shared_ptr<LibSgfcPlusPlus::ISgfcCommandLine> SgfcPlusPlusFactory::CreateSgfcCommandLine(
    const std::vector<std::string>& arguments)
  {
    std::shared_ptr<ISgfcCommandLine> commandLine = std::shared_ptr<SgfcCommandLine>(new SgfcCommandLine(arguments));
    return commandLine;
  }

  std::shared_ptr<ISgfcCommandLine> SgfcPlusPlusFactory::CreateSgfcCommandLine()
  {
    std::vector<std::string> emptyArgumentList;
    return SgfcPlusPlusFactory::CreateSgfcCommandLine(emptyArgumentList);
  }

  std::shared_ptr<ISgfcDocumentReader> SgfcPlusPlusFactory::CreateDocumentReader()
  {
    std::shared_ptr<ISgfcDocumentReader> reader = std::shared_ptr<ISgfcDocumentReader>(new SgfcDocumentReader());
    return reader;
  }
}
