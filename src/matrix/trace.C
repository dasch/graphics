char TraceInfoVersion[] = 
    "$Id: trace.nw,v 1.1 2005/08/10 13:05:34 kaiip Exp $";

#define TRACE
#include <matrix/trace.h>

TraceInfo::TraceInfo(const std::string& ClassName,
                     const std::string& MemberName,
                     const std::string& FileName,
                     const unsigned int         LineNumber)
         : classname(ClassName), membername(MemberName),
           filename(FileName),   linenumber(LineNumber),
           prefix(ClassName + "::" + MemberName)
{
    for (unsigned int i = 1; i <= indentlevel; ++i) std::cout << indentspace;
    std::cout << enter  << this->classname << "::" << this->membername
              << " -- " << this->filename  << '('  << this->linenumber << ')'
              << std::endl << std::flush;
    ++indentlevel;
    for (unsigned int j = 1; j <= indentlevel; ++j) prefix = indentspace + prefix;
}
TraceInfo::~TraceInfo()
{
    --indentlevel;
    for (unsigned int i = 1; i <= indentlevel; ++i) std::cout << indentspace;
    std::cout << leave << this->classname << "::" << this->membername
              << " -- " << this->filename << '('  << this->linenumber << ')'
              << std::endl << std::flush;
}
const std::string& TraceInfo::Prefix()
{
    return prefix;
}
unsigned int              TraceInfo::indentlevel = 0;
const std::string TraceInfo::enter       = "-->";
const std::string TraceInfo::leave       = "<--";
const std::string TraceInfo::indentspace = "   ";
