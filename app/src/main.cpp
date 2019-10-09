#include <iostream>

extern "C"
{
#include "apcop2.h"
}

int main()
{
    std::cout << "Hello AMBE!\n";

    ENCSTATE_T es;

    ambe_init_enc(&es, APCO_HR_MODE, 1);
}
