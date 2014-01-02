#include <iostream>

#include <tut/tut.hpp>
#include <tut/tut_console_reporter.hpp>

#include "AshTesting.hpp"

int main(int argc, char** argv) {
    tut::console_reporter reporter;

    tut::runner.get().set_callback(&reporter);
    tut::runner.get().run_tests();

    return !reporter.all_ok();
}
