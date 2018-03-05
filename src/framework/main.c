#include "framework.h"

int main(int argc, char* argv[])
{
    TaskEngine_init();
    do {
        TaskEngine_run();
    } while (1);
    return 0;
}

