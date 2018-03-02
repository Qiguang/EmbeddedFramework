#include "framework.h"


int main(int argc, char* argv[])
{
    Framework_init();
    do {
        run();
    } while (1);
    return 0;
}

