#include <iostream>
#include <cstdlib>

#include "parser.h"

// Баранов Константин Павлович, группа 20021.

void printHelp() {
    std::cout << "Usage: cmilan input_file\n";
}

int main(int argc, char** argv) {
    // if(argc < 2) {
    //     printHelp();
    //     return EXIT_FAILURE;
    // }

    std::ifstream input;
    // input.open(argv[1]);
    input.open("/mnt/f/docs/spbpu_hw_labs/2/discrete_math/coursework/cmilan/test/comment.mil");

    if(input) {
        Parser p("/mnt/f/docs/spbpu_hw_labs/2/discrete_math/coursework/cmilan/test/comment.mil", input);
        p.parse();
        return EXIT_SUCCESS;
    } else {
        std::cerr << "File '" << "/mnt/f/docs/spbpu_hw_labs/2/discrete_math/coursework/cmilan/test/comment.mil" << "' not found\n";
        return EXIT_FAILURE;
    }
}
