#include "util.h"

int porta_valida(int porta)
{
    return porta >= 1024 && porta <= 65535;
}
