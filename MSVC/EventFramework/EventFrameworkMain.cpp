// EventFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" {
#include "EventFramework.h"
}


int _tmain(int argc, _TCHAR* argv[])
{
    initFramework();
    do {
        run();
    } while (1);
    return 0;
}

