#ifndef RasterMan_TRACEINFO_H
#define RasterMan_TRACEINFO_H
// [[$Id: trace.nw,v 1.1 2005/08/10 13:05:34 kaiip Exp $]]

#include <iostream>
#include <iomanip>
#include <string>


#undef TRACE

class TraceInfo {
public:
    TraceInfo(const std::string& ClassName, const std::string& MemberName,
              const std::string& FileName,  const unsigned int LineNumber = 0);
    virtual ~TraceInfo();
    const std::string& Prefix();
private:
    const std::string  classname;
    const std::string  membername; 
    const std::string  filename;
    const unsigned int         linenumber;
    std::string        prefix;
    static unsigned int              indentlevel;
    static const std::string enter;
    static const std::string leave;
    static const std::string indentspace;
};

#ifndef TRACE
#define Trace(ClassName, MemberName)
#else
#define Trace(ClassName, MemberName)                                     ??/
TraceInfo TRACEINFO(std::string(ClassName), std::string(MemberName),     ??/
                    std::string(__FILE__),__LINE__);
#endif
#ifndef TRACE
#define TraceMessage(Statement)
#else
#define TraceMessage(Statement)                                         ??/
    std::cout << TRACEINFO.Prefix()                                     ??/
              << " -- " << __FILE__ << '(' << __LINE__ << "): "         ??/
              << Statement;
#endif
#ifndef TRACE
#define CondTraceMessage(Condition, TrueStatement, FalseStatement)
#else
#define CondTraceMessage(Condition, TrueStatement, FalseStatement)      ??/
    if (Condition) {                                                    ??/
        std::cout << TRACEINFO.Prefix()                                 ??/
                  << " -- " << __FILE__ << '(' << __LINE__ << "): "     ??/
                  << TrueStatement;                                     ??/
    }                                                                   ??/
    else {                                                              ??/
        std::cout << TRACEINFO.Prefix()                                 ??/
             << " -- " << __FILE__ << '(' << __LINE__ << "): "          ??/
             << FalseStatement;                                         ??/
    }
#endif

#endif
