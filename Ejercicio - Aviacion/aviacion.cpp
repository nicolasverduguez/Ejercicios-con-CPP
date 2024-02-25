
#include <iostream>
#include "files.hpp"
#include "List.hpp"
#include "aviacion.hpp"
using namespace std;

int main()
{

   /* -- Leo los archivos de consulta -- */
   List<Ciudad> lstCiudades = subirCiudades();
   List<RVuelo> lstRVuelos = subirVuelos();
   List<Cliente> lstClientes = list<Cliente>();

   /* -- Leo las novedades -- */
   FILE* f = fopen("RESERVAS.dat", "r+b");
   Reserva res = read<Reserva>(f);

   while (!feof(f)) {

      bool reservaAceptada = procesarReserva(res, lstRVuelos);

      if (reservaAceptada) {
         Cliente* cli = obtenerCliente(res, lstClientes);
         int cantMillas = calcularMillas(res, lstCiudades, lstRVuelos);
         sumarMillas(cli, cantMillas);
      }

      res = read<Reserva>(f);
   }

   return 0;
}
