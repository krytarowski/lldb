//===-- MIUtilParse.cpp ----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
 
// Third party headers:
#include <memory>

// In-house headers:
#include "MIUtilParse.h"
 
//++ ------------------------------------------------------------------------------------
// Details: CRegexParser constructor.
// Type:    Method.
// Args:    regexStr - Pointer to the regular expression to compile.
// Return:  None.
// Throws:  None.
//--
MIUtilParse::CRegexParser::CRegexParser(const char *regexStr)
{
    m_emma = llvm::Regex(regexStr, REG_EXTENDED);
    std::string dummy;
    m_isValid = m_emma.isValid(dummy);
}
 
//++ ------------------------------------------------------------------------------------
// Details: CRegexParser destructor.
// Type:    Method.
// Args:    None.
// Return:  None.
// Throws:  None.
//--
MIUtilParse::CRegexParser::~CRegexParser()
{
}
 
//++ ------------------------------------------------------------------------------------
// Details: CRegexParser regex executer.
//          Match the input against the regular expression.  Return an error
//          if the number of matches is less than minMatches.  If the default
//          minMatches value of 0 is passed, an error will be returned if
//          the number of matches is less than the maxMatches value used to
//          initialize Match.
// Type:    Method.
// Args:    input (R) - Pointer to UTF8 text data to be parsed.
//          match (RW) - Reference to Match class.
//          minMatches (R) - Minimum number of regex matches expected.
// Return:  bool - True = minimum matches were met,
//                 false = minimum matches were not met or regex failed.
// Throws:  None.
//--
bool
MIUtilParse::CRegexParser::Execute(const char *input, Match& match, size_t minMatches)
{
    if (!m_isValid)
        return false;

    SmallVector<StringRef, 1> Matches;
    Matches.resize(m_emma.getNumMatches());
    if (!m_emma.match(StringRef(input), &matches))
        return false;
 
    size_t i;
    for (i = 0; i < match.m_maxMatches && matches[i].rm_so >= 0; i++)
    {
        match.m_matchStrs[i].assign(matches[i]);
    }
    return i >= minMatches;
}
