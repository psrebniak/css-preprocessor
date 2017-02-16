#include "lib/main/Main.hpp"

/*! \mainpage CSS preprocessor
 *
 * @author Piotr Srebniak, <br/>
 * Wydział Podstawowych Problemów Techniki, <br/>
 * Politechnika Wrocławska
 *
 */

/**
 * Create application instance
 * @param argc number of arguments
 * @param argv array of arguments
 * @return code
 */
int main(int argc, char *argv[]) {
    CSSP::Main app(argc, argv);
    return app.run();
}
