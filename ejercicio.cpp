

#include "SystemManager.h"
#include <csignal>
using namespace std;

bool sesionIniciada = false;

void terminationHandler(SystemManager *m, int signum) {
    m->cargarListaClientes();
    exit(signum);
}
int main()
{
    {
    SystemManager *manager = new SystemManager();
    manager->cargarListaClientes();
    manager->menu();
    delete(manager);
    }
    return 0;
}

