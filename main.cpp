#include <iostream>
#include "meteoPlots.h"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    meteoPlots plots( "../data/20190107.txt" );
    plots.plot();
    plots.savePlots( "test.png" );
    plots.savePlots( "test.root" );
    return 0;
}
