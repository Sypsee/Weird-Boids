#include "Application.h"

#include <iostream>
#include <exception>

int main()
{
    Application app;

    try
    {
        app.run();
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}