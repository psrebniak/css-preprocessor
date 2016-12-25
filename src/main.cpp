#include "lib/main/Main.hpp"

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
