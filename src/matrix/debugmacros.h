#ifndef RM_DEBUGMACROS_H
#define RM_DEBUGMACROS_H
// [[$Id: debugmacros.nw,v 1.1 2005/08/10 13:03:27 kaiip Exp $]]


#define newline   ""
#define blankline '\n'
#define Test1(Text,                                                 ??/
              Expression1, ExpectedValue1)                          ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
    TestEnd()                                                       ??/
}
#define Test2(Text,                                                 ??/
              Expression1, ExpectedValue1,                          ??/
              Expression2, ExpectedValue2)                          ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
    TestEnd()                                                       ??/
}
#define Test3(Text,                                                 ??/
              Expression1, ExpectedValue1,                          ??/
              Expression2, ExpectedValue2,                          ??/
              Expression3, ExpectedValue3)                          ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
        TestOneExpression(Expression3, ExpectedValue3)              ??/
    TestEnd()                                                       ??/
}
#define Test4(Text,                                                 ??/
              Expression1, ExpectedValue1,                          ??/
              Expression2, ExpectedValue2,                          ??/
              Expression3, ExpectedValue3,                          ??/
              Expression4, ExpectedValue4)                          ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
        TestOneExpression(Expression3, ExpectedValue3)              ??/
        TestOneExpression(Expression4, ExpectedValue4)              ??/
    TestEnd()                                                       ??/
}
#define Test5(Text,                                                 ??/
              Expression1, ExpectedValue1,                          ??/
              Expression2, ExpectedValue2,                          ??/
              Expression3, ExpectedValue3,                          ??/
              Expression4, ExpectedValue4,                          ??/
              Expression5, ExpectedValue5)                          ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
        TestOneExpression(Expression3, ExpectedValue3)              ??/
        TestOneExpression(Expression4, ExpectedValue4)              ??/
        TestOneExpression(Expression5, ExpectedValue5)              ??/
    TestEnd()                                                       ??/
}
#define Test6(Text,                                                 ??/
              Expression1, ExpectedValue1,                          ??/
              Expression2, ExpectedValue2,                          ??/
              Expression3, ExpectedValue3,                          ??/
              Expression4, ExpectedValue4,                          ??/
              Expression5, ExpectedValue5,                          ??/
              Expression6, ExpectedValue6)                          ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
        TestOneExpression(Expression3, ExpectedValue3)              ??/
        TestOneExpression(Expression4, ExpectedValue4)              ??/
        TestOneExpression(Expression5, ExpectedValue5)              ??/
        TestOneExpression(Expression6, ExpectedValue6)              ??/
    TestEnd()                                                       ??/
}
#define Test7(Text,                                                 ??/
              Expression1, ExpectedValue1,                          ??/
              Expression2, ExpectedValue2,                          ??/
              Expression3, ExpectedValue3,                          ??/
              Expression4, ExpectedValue4,                          ??/
              Expression5, ExpectedValue5,                          ??/
              Expression6, ExpectedValue6,                          ??/
              Expression7, ExpectedValue7)                          ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
        TestOneExpression(Expression3, ExpectedValue3)              ??/
        TestOneExpression(Expression4, ExpectedValue4)              ??/
        TestOneExpression(Expression5, ExpectedValue5)              ??/
        TestOneExpression(Expression6, ExpectedValue6)              ??/
        TestOneExpression(Expression7, ExpectedValue7)              ??/
    TestEnd()                                                       ??/
}
#define Test8(Text,                                                 ??/
              Expression1,  ExpectedValue1,                         ??/
              Expression2,  ExpectedValue2,                         ??/
              Expression3,  ExpectedValue3,                         ??/
              Expression4,  ExpectedValue4,                         ??/
              Expression5,  ExpectedValue5,                         ??/
              Expression6,  ExpectedValue6,                         ??/
              Expression7,  ExpectedValue7,                         ??/
              Expression8,  ExpectedValue8)                         ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
        TestOneExpression(Expression3, ExpectedValue3)              ??/
        TestOneExpression(Expression4, ExpectedValue4)              ??/
        TestOneExpression(Expression5, ExpectedValue5)              ??/
        TestOneExpression(Expression6, ExpectedValue6)              ??/
        TestOneExpression(Expression7, ExpectedValue7)              ??/
        TestOneExpression(Expression8, ExpectedValue8)              ??/
    TestEnd()                                                       ??/
}
#define Test9(Text,                                                 ??/
              Expression1,  ExpectedValue1,                         ??/
              Expression2,  ExpectedValue2,                         ??/
              Expression3,  ExpectedValue3,                         ??/
              Expression4,  ExpectedValue4,                         ??/
              Expression5,  ExpectedValue5,                         ??/
              Expression6,  ExpectedValue6,                         ??/
              Expression7,  ExpectedValue7,                         ??/
              Expression8,  ExpectedValue8,                         ??/
              Expression9,  ExpectedValue9)                         ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1, ExpectedValue1)              ??/
        TestOneExpression(Expression2, ExpectedValue2)              ??/
        TestOneExpression(Expression3, ExpectedValue3)              ??/
        TestOneExpression(Expression4, ExpectedValue4)              ??/
        TestOneExpression(Expression5, ExpectedValue5)              ??/
        TestOneExpression(Expression6, ExpectedValue6)              ??/
        TestOneExpression(Expression7, ExpectedValue7)              ??/
        TestOneExpression(Expression8, ExpectedValue8)              ??/
        TestOneExpression(Expression9, ExpectedValue9)              ??/
    TestEnd()                                                       ??/
}
#define Test10(Text,                                                ??/
              Expression1,  ExpectedValue1,                         ??/
              Expression2,  ExpectedValue2,                         ??/
              Expression3,  ExpectedValue3,                         ??/
              Expression4,  ExpectedValue4,                         ??/
              Expression5,  ExpectedValue5,                         ??/
              Expression6,  ExpectedValue6,                         ??/
              Expression7,  ExpectedValue7,                         ??/
              Expression8,  ExpectedValue8,                         ??/
              Expression9,  ExpectedValue9,                         ??/
              Expression10, ExpectedValue10)                        ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        TestOneExpression(Expression1,  ExpectedValue1)             ??/
        TestOneExpression(Expression2,  ExpectedValue2)             ??/
        TestOneExpression(Expression3,  ExpectedValue3)             ??/
        TestOneExpression(Expression4,  ExpectedValue4)             ??/
        TestOneExpression(Expression5,  ExpectedValue5)             ??/
        TestOneExpression(Expression6,  ExpectedValue6)             ??/
        TestOneExpression(Expression7,  ExpectedValue7)             ??/
        TestOneExpression(Expression8,  ExpectedValue8)             ??/
        TestOneExpression(Expression9,  ExpectedValue9)             ??/
        TestOneExpression(Expression10, ExpectedValue10)            ??/
    TestEnd()                                                       ??/
}
#ifndef VISUAL
#define TestHeader(Text)                                            ??/
unsigned int LocalErrors = 0;                                               ??/
debugout << std::endl << "*** Testing "                             ??/
         << Text                                                    ??/
         << " ***" << std::endl << std::endl;
#endif
#ifndef VISUAL
#define TestTrailer()                                               ??/
    debugout << std::endl;                                          ??/
    if (LocalErrors == 0)                                           ??/
        debugout << "*** End of Test: All tests succeded *** ";     ??/
    else  {                                                         ??/
        debugout << "*** End of Test: "                             ??/
                 << LocalErrors << " test failed *** ";             ??/
    }                                                               ??/
    TotalErrors += LocalErrors;                                     ??/
    debugout << "Total Errors so far = " << TotalErrors             ??/
             << " ***" << std::endl << std::endl;
#endif
#ifndef VISUAL
#define TestMessage(Text) debugout << "    " << Text << std::endl;
#endif
#ifndef VISUAL
#define TestStreamOut(Text, Object, ExpectedOutput)                 ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        std::ostringstream LocalOutputStream;                       ??/
        LocalOutputStream << Object << std::ends;                   ??/
        if (LocalOutputStream.str() == ExpectedOutput) {            ??/
            if (NoErrorsSoFar) {                                    ??/
                debugout << " NOT OK!" << std::endl;                ??/
                debugout << "        " << __FILE__                  ??/
                         << '(' << __LINE__ << ')' << std::endl;    ??/
            }                                                       ??/
            debugout << "            " << "Object `"                ??/
                     << #Object << "' "  << "outputs: "             ??/
                     << LocalOutputStream.str() << std::endl;       ??/
            debugout << "            " << "Should have output: "    ??/
                     << (ExpectedOutput) << std::endl;              ??/
            NoErrorsSoFar = false;                                  ??/
        }                                                           ??/
        debugout << std::flush;                                      ??/
    TestEnd()                                                       ??/
}
#endif
#ifndef VISUAL
#define TestBegin(Text)                                             ??/
    bool NoErrorsSoFar = true;                                      ??/
    debugout << "    " << Text << ' ';
#endif

#ifndef VISUAL
#define TestEnd()                                                   ??/
    if (NoErrorsSoFar)                                              ??/
        debugout << " OK" << std::endl;                             ??/
    else {                                                          ??/
        ++LocalErrors;                                              ??/
    }
#endif
#ifndef VISUAL
#define TestOneExpression(Expression, ExpectedValue)                ??/
    if (!((Expression) == (ExpectedValue))) {                       ??/
        if (NoErrorsSoFar) {                                        ??/
            debugout << " NOT OK!" << std::endl;                    ??/
            debugout << "        " << __FILE__                      ??/
                     << '(' << __LINE__ << ')' << std::endl;        ??/
        }                                                           ??/
        debugout << "            " << "Member Function `"           ??/
                 << #Expression  << "' returns: " << (Expression)   ??/
                 << std::endl;                                      ??/
        debugout << "            " << "Should have returned: "      ??/
                 << (ExpectedValue) << std::endl;                   ??/
        NoErrorsSoFar = false;                                      ??/
    }                                                               ??/
    debugout << std::flush;
#endif
#ifndef VISUAL
#define debugout std::cout
#endif
#ifdef VISUAL
#define TestHeader(Text)                                            ??/
    static unsigned int LocalErrors = 0;                                    ??/
    static int  linenumber  = 0;                                    ??/
    static bool alreadyexecuted = false;                            ??/
    if (!alreadyexecuted) {                                         ??/
        if (browser->size() == 1) debugout << engrave << std::endl; ??/
        debugout << std::endl;                                      ??/
        linenumber = browser->size() - 2;                           ??/
        debugout << bold << "Testing: " << Text << std::endl;       ??/
    }                                                               ??/
    else {                                                          ??/
        button->clear();                                            ??/
        if (LocalErrors == 0)                                       ??/
            button->selection_color(FL_GREEN);                      ??/
        else {                                                      ??/
            button->selection_color(FL_RED);                        ??/
        }                                                           ??/
        button->set();                                              ??/
        browser->topline(linenumber);                               ??/
        return;                                                     ??/
    }
#endif
#ifdef VISUAL
#define TestTrailer()                                               ??/
    if (!alreadyexecuted) {                                         ??/
        button->clear();                                            ??/
        debugout << bold << "End of Test: ";                        ??/
        if (LocalErrors == 0) {                                     ??/
            button->selection_color(FL_GREEN);                      ??/
            debugout << "All tests succeded";                       ??/
        }                                                           ??/
        else  {                                                     ??/
            button->selection_color(FL_RED);                        ??/
            debugout << LocalErrors;                                ??/
            if (LocalErrors == 1)                                   ??/
                debugout << " test failed";                         ??/
            else {                                                  ??/
                debugout << " tests failed";                        ??/
            }                                                       ??/
        }                                                           ??/
        button->set();                                              ??/
        TotalErrors += LocalErrors;                                 ??/
        debugout << " --- Total Errors so far = " << TotalErrors    ??/
                 << std::endl << std::endl;                         ??/
        debugout << engrave << std::endl;                           ??/
        Fl::check();                                                ??/
                                                                    ??/
        alreadyexecuted = true;                                     ??/
    }
#endif
#ifdef VISUAL
#define TestMessage(Text) debugout << bold << "    " << Text << std::endl
#endif
#ifdef VISUAL
#define TestStreamOut(Text, Object, ExpectedOutput)                 ??/
{                                                                   ??/
    TestBegin(Text)                                                 ??/
        std::ostringstream LocalOutputStream;                       ??/
        LocalOutputStream << Object << std::ends;                   ??/
        if (std::strcmp(LocalOutputStream.str().c_str(),            ??/
                        ExpectedOutput) != 0) {                     ??/
            if (NoErrorsSoFar) {                                    ??/
                debugout << " NOT OK!" << std::endl;                ??/
                debugout << bold << textcolor(FL_RED) << "        " ??/
                         << __FILE__ << '(' << __LINE__ << "):"     ??/
                         << std::endl;                              ??/
            }                                                       ??/
            debugout << textcolor(FL_RED) << "            "         ??/
                     << "Object `" << #Object << "' "               ??/
                     << "outputs: " << LocalOutputStream.str()      ??/
                     << std::endl;                                  ??/
            debugout << textcolor(FL_RED) << "            "         ??/
                     << "Should have output: "                      ??/
                     << (ExpectedOutput) << std::endl;              ??/
            NoErrorsSoFar = false;                                  ??/
        }                                                           ??/
        debugout << std::flush;                                     ??/
    TestEnd()                                                       ??/
}
#endif
#ifdef VISUAL
#define TestBegin(Text)                                             ??/
    bool NoErrorsSoFar = true;                                      ??/
    debugout << "    " << Text << ' ';
#endif
#ifdef VISUAL
#define TestEnd()                                                   ??/
    if (NoErrorsSoFar) {                                            ??/
        debugout << " OK" << std::endl;                             ??/
    }                                                               ??/
    else {                                                          ??/
        ++LocalErrors;                                              ??/
    }
#endif
#ifdef VISUAL
#define TestOneExpression(Expression, ExpectedValue)                ??/
    if (!((Expression) == (ExpectedValue))) {                       ??/
        if (NoErrorsSoFar) {                                        ??/
            debugout << " NOT OK!" << std::endl;                    ??/
            debugout << bold << textcolor(FL_RED) << "        "     ??/
                     << __FILE__ << '(' << __LINE__ << "):" << std::endl; ??/
        }                                                           ??/
        debugout << textcolor(FL_RED) << "            "             ??/
                 << "Member Function `" << #Expression              ??/
                 << "' returns: " << (Expression) << std::endl;     ??/
        debugout << textcolor(FL_RED) << "            "             ??/
                 << "Should have returned: "                        ??/
                 << (ExpectedValue) << std::endl;                   ??/
        NoErrorsSoFar = false;                                      ??/
    }
#endif
#ifdef VISUAL
#define debugout (*browser)
#endif
#ifndef VISUAL
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <matrix/performtest.h>
#endif
#ifdef VISUAL
#include <sstream>
#include <string>
#include <FL/Fl.H>
//#include <matrix/browser.h>
//#include <matrix/browsermanip.h>
#include <matrix/performtest.h>
#endif

#endif
