/*
 * Teste elementar das funcionalidades da biblioteca.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "7keys.h"

#include <iostream>

using namespace std;

int main(int, char *[])
{
    try
    {
        SevenKeys keys;
        keys.init("7 Keys", 1366, 768);
        keys.run();
    } catch (Exception ex)
    {
        cerr << ex.message() << endl;
        return -1;
    }

    return 0;
}
