// Project includes
#include "../../../include/SgfcConstants.h"
#include "../../../include/ISgfcMessage.h"
#include "../../interface/internal/SgfcMessagePart.h"
#include "../../SgfcPrivateConstants.h"
#include "SgfcMessage.h"
#include "SgfcMessageParser.h"

// C++ Standard Library includes
#include <cassert>
#include <limits>
#include <sstream>

namespace LibSgfcPlusPlus
{
  // Cf. documentation of SgfcMessagePart for a definition of the message
  // format. This may help understanding the implementation.
  std::shared_ptr<ISgfcMessage> SgfcMessageParser::CreateSgfcMessage(const std::string& rawMessageText)
  {
    std::vector<std::string> tokens =
      SgfcMessageParser::TokenizeRawMessageText(rawMessageText);

    int messageID = SgfcConstants::UnknownSgfcMessageID;
    SgfcMessageType messageType = SgfcPrivateConstants::DefaultMessageType;
    int lineNumber = SgfcConstants::InvalidLineNumber;
    int columnNumber = SgfcConstants::InvalidColumnNumber;
    bool isCriticalMessage  = SgfcPrivateConstants::DefaultIsCriticalMessage;
    std::string messageText = SgfcPrivateConstants::DefaultMessageText;

    SgfcMessagePart expectedMessagePart = SgfcMessagePart::LineNumberOrMessageTypeToken;

    while (! tokens.empty())
    {
      std::string token = tokens.front();
      tokens.erase(tokens.begin());

      bool foundExpectedMessagePart = false;

      switch (expectedMessagePart)
      {
        case SgfcMessagePart::LineNumberOrMessageTypeToken:
        {
          if (token.find(SgfcPrivateConstants::LineToken) == 0)
          {
            lineNumber = SgfcMessageParser::GetLineOrColumnNumberFromToken(token, SgfcPrivateConstants::LineToken);
            expectedMessagePart = SgfcMessagePart::ColumnNumber;
            foundExpectedMessagePart = true;
          }
          else if (token.find(SgfcPrivateConstants::FatalToken) == 0)
          {
            messageType = SgfcMessageType::FatalError;
            expectedMessagePart = SgfcMessagePart::ErrorLowerCaseToken;
            foundExpectedMessagePart = true;
          }
          else if (token.find(SgfcPrivateConstants::ErrorUpperCaseToken) == 0)
          {
            messageType = SgfcMessageType::Error;
            expectedMessagePart = SgfcMessagePart::MessageID;
            foundExpectedMessagePart = true;
          }
          else if (token.find(SgfcPrivateConstants::WarningToken) == 0)
          {
            messageType = SgfcMessageType::Warning;
            expectedMessagePart = SgfcMessagePart::MessageID;
            foundExpectedMessagePart = true;
          }
          break;
        }
        case SgfcMessagePart::ColumnNumber:
        {
          if (token.find(SgfcPrivateConstants::ColumnToken) == 0)
          {
            columnNumber = SgfcMessageParser::GetLineOrColumnNumberFromToken(token, SgfcPrivateConstants::ColumnToken);
            expectedMessagePart = SgfcMessagePart::Dash;
            foundExpectedMessagePart = true;
          }
          break;
        }
        case SgfcMessagePart::ErrorLowerCaseToken:
        {
          if (token.find(SgfcPrivateConstants::ErrorLowerCaseToken) == 0)
          {
            // Ignore the word
            expectedMessagePart = SgfcMessagePart::MessageID;
            foundExpectedMessagePart = true;
          }
          break;
        }
        case SgfcMessagePart::Dash:
        {
          if (token.find(SgfcPrivateConstants::DashToken) == 0)
          {
            // Ignore the dash
            expectedMessagePart = SgfcMessagePart::MessageType;
            foundExpectedMessagePart = true;
          }
          break;
        }
        case SgfcMessagePart::MessageType:
        {
          if (token.find(SgfcPrivateConstants::WarningToken) == 0)
          {
            messageType = SgfcMessageType::Warning;
            expectedMessagePart = SgfcMessagePart::MessageID;
            foundExpectedMessagePart = true;
          }
          else if (token.find(SgfcPrivateConstants::ErrorUpperCaseToken) == 0)
          {
            messageType = SgfcMessageType::Error;
            expectedMessagePart = SgfcMessagePart::MessageID;
            foundExpectedMessagePart = true;
          }
          break;
        }
        case SgfcMessagePart::MessageID:
        {
          int messageIDFromToken = SgfcMessageParser::GetMessageIDFromToken(token);
          if (messageIDFromToken != SgfcConstants::InvalidMessageID)
          {
            messageID = messageIDFromToken;
            expectedMessagePart = SgfcMessagePart::CriticalIndicator;
            foundExpectedMessagePart = true;
          }
          break;
        }
        case SgfcMessagePart::CriticalIndicator:
        {
          if (token.find(SgfcPrivateConstants::CriticalToken) == 0)
          {
            isCriticalMessage = true;
            expectedMessagePart = SgfcMessagePart::MessageText;
            foundExpectedMessagePart = true;
          }
          else
          {
            // The CriticalIndicator is optional, so if it doesn't appear
            // it's no disaster
            expectedMessagePart = SgfcMessagePart::MessageText;
          }
          break;
        }
        case SgfcMessagePart::MessageText:
        {
          // Here we're reconstituting the message from the individual tokens.
          // We don't know how many whitespace characters were used in the raw
          // message text to delimit the tokens, nor what kind. Here we're
          // simply using a single space character. This means that the
          // reconstituted message text can differ from the original raw message
          // text in the amount or kind of whitespace used.
          if (messageText.empty())
          {
            // We get here if in the previous iteration we DID find the
            // optional CriticalIndicator
            messageText = token;
          }
          else
          {
            // We get here if in the previous iteration we didn't find the
            // optional CriticalIndicator
            messageText += SgfcPrivateConstants::SpaceCharacter + token;
          }
          foundExpectedMessagePart = true;
          break;
        }
        default:
        {
          break;
        }
      }

      // There are two reasons why we didn't find the expected message part:
      // - We were looking for the optional CriticalIndicator. Since this
      //   is the last message part before the message text, the current token
      //   must therefore be the first word of the message text.
      // - The message has an unexpected format which we don't know how to
      //   parse. Our only option now is to treat the remaining tokens as the
      //   message text, starting with the current token.
      if (! foundExpectedMessagePart)
      {
        expectedMessagePart = SgfcMessagePart::MessageText;
        messageText = token;
      }
    }

    // The SgfcMessage constructor throws an exception if the parameters do not
    // satisfy the specification in the ISgfcMessage interface documentation.
    // The specification was written after studying the SGFC documentation how
    // SGFC messages can look like, but we can't be 100% sure that the SGFC
    // implementation matches their documentation. The following block is a bit
    // of defensive code that manipulates the data we get from parsing the
    // SGFC message to make sure that the SgfcMessage constructor does not
    // throw an exception. We should not affect the library client with an
    // exception that is caused by a relatively trivial interfacing issue - it's
    // much more important that the client can read and write SGF data.
    if (messageType == SgfcMessageType::FatalError)
    {
      if (lineNumber != SgfcConstants::InvalidLineNumber)
      {
        lineNumber = SgfcConstants::InvalidLineNumber;
        assert(false);
      }

      if (columnNumber != SgfcConstants::InvalidColumnNumber)
      {
        columnNumber = SgfcConstants::InvalidColumnNumber;
        assert(false);
      }

      if (isCriticalMessage)
      {
        isCriticalMessage = false;
        assert(false);
      }
    }

    std::shared_ptr<ISgfcMessage> sgfcMessage = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      messageID,
      messageType,
      lineNumber,
      columnNumber,
      isCriticalMessage,
      messageText,
      rawMessageText));

    return sgfcMessage;
  }

  std::vector<std::string> SgfcMessageParser::TokenizeRawMessageText(
    const std::string& rawMessageText)
  {
    std::istringstream iss(rawMessageText);

    // Whitespace is the token delimiter. Consecutive whitespace characters are
    // treated as a single delimiter.
    std::vector<std::string> tokens
    {
      std::istream_iterator<std::string>{iss},
      std::istream_iterator<std::string>{}
    };

    return tokens;
  }

  int SgfcMessageParser::GetLineOrColumnNumberFromToken(
    const std::string& token,
    const std::string& prefixToStrip)
  {
    std::string lineNumberAsString = token.substr(
      prefixToStrip.length(),
      std::string::npos);
    int lineOrColumnNumber = std::stoi(lineNumberAsString);
    return lineOrColumnNumber;
  }

  int SgfcMessageParser::GetMessageIDFromToken(const std::string& token)
  {
    try
    {
      // Sometimes we get only digits, but sometimes we also get digits with
      // a colon suffix (e.g. "42:"). stoi is flexible enough that it reads
      // all digits until the first non-digit character.
      return std::stoi(token);
    }
    catch (std::exception&)
    {
      return SgfcConstants::InvalidMessageID;
    }
  }
}
