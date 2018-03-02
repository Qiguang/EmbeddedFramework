#include "eventFramework.h"


int main(int argc, char* argv[])
{
    initFramework();
    do {
        run();
    } while (1);
    return 0;
}

