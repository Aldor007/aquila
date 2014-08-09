#include <iostream>
#include "src/TestDetails.h"
#include "src/TestReporterStdout.h"
#include "src/TestRunner.h"
#include "src/Test.h"


class AquilaTestReporter : public UnitTest::TestReporterStdout
{
    void ReportTestStart(UnitTest::TestDetails const& test)
    {
        std::cout << test.suiteName << "::" << test.testName;
    }

    void ReportTestFinish(UnitTest::TestDetails const& /* test */, float secondsElapsed)
    {
        std::cout << " [";
        if (secondsElapsed < 0.05) {
            std::cout << "\033[92m";
        } else if (secondsElapsed < 0.5) {
            std::cout << "\033[93m";
        } else {
            std::cout << "\033[1m\033[91m";
        }
        std::cout << secondsElapsed * 1000 << "\033[0m ms]" << std::endl;
    }
};


int main()
{
    AquilaTestReporter reporter;
    UnitTest::TestRunner runner(reporter);
    return runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);
}
