#include <iostream>
#include "SessionManager.h"

int main()
{
    std::cout << "Casino App Starting...\n";

    SessionManager session;
    session.run();

    return 0;
}