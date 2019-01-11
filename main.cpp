#include "iostream"
#include "include/commandParser.h"

using namespace std;

int main(int argc, char *argv[]) {
    CommandParser commandParser;

    cout << "Cash started" << std::endl;

    commandParser.execute();

    return 0;
}
