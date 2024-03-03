
/*

Una compañía de aviación requiere implementar un programa que, basado en un sistema de acumulación de millas, promueva la fidelización de sus clientes.
Cada vez que un cliente vuela a través de la compañía recibe una cantidad de millas acumulables, que posteriormente podrá canjear por vuelos sin costo a diferentes destinos. 
Cuanto mayor sea la cantidad de millas acumuladas, más importante serán los destinos o premios por los cuales las podrá canjear.
La compañía cuenta con los siguientes archivos: CIUDADES.dat, que contiene la descripción de las ciudades a las que vuela, VUELOS.dat, con la información de los vuelos que conectan las diferentes ciudades, y RESERVAS.dat, con las reservas que realizaron los clientes para volar en los diferentes vuelos.
La estructura de cada uno de estos archivos la vemos a continuación.

CIUDADES 
struct Ciudad { 
	int idCiu; 
	char descr[20]; 
	int millas; 
};

VUELOS 
struct Vuelo { 
	int idVue; 
	int cap; 
	int idOri; // idCiu origen 
	int idDes; // idCiu origen 
};

RESERVAS 
struct Reserva { 
	int idCli; 
	int idVue; 
	int cant; 
};

La operatoria es la siguiente: un pasajero que vuela de una ciudad a otra acumula una cantidad de millas equivalente a la diferencia entre las millas esta-blecidas para cada una de esas ciudades, multiplicado por la cantidad de plazas re-servadas. 
Esto será así siempre y cuando su reserva sea aceptada.
Sólo se aceptarán las reservas de aquellos pasajeros que requieran una cantidad de plazas menor o igual a la disponibilidad actual del vuelo en cuestión. 
De lo contrario la reserva completa será rechazada.
Se pide informar:
1. Para cada ciudad, cantidad de grupos (familias) que la eligieron de destino.
2. Por cada vuelo, cantidad de plazas rechazadas, indicando también si el vuelo saldrá completo o incompleto.
3. Para cada cliente, total de millas acumuladas.

*/

#include <iostream>
#include "files.hpp"
#include "List.hpp"
#include "aviacion.hpp"
using namespace std;

int main()
{

   /* -- Leo los archivos de consulta -- */
   List<RCiudad> lstRCiudades = subirCiudades();
   List<RVuelo> lstRVuelos = subirVuelos();
   List<Cliente> lstClientes = list<Cliente>();

   /* -- Leo las novedades -- */
   FILE* f = fopen("RESERVAS.dat", "r+b");
   Reserva res = read<Reserva>(f);

   while (!feof(f)) {

      /* -- Proceso la reserva -- */
      bool reservaAceptada = procesarReserva(res, lstRCiudades, lstRVuelos);

      /* -- Verifico si existen lugares para reservar -- */
      if (reservaAceptada) {

         /* -- Obtengo el cliente -- */
         Cliente* cli = obtenerCliente(res, lstClientes);

         /* -- Calculo las millas -- */
         int cantMillas = calcularMillas(res, lstRCiudades, lstRVuelos);

         /* -- Sumo las millas -- */
         sumarMillas(cli, cantMillas);
      }

      /* -- Leo la siguiente reserva -- */
      res = read<Reserva>(f);
   }

   /* -- Mostrar resultados -- */
   mostrarEleccionDeFamilias(lstRCiudades);
   mostrarDetalleDeVuelos(lstRVuelos);
   mostrarMillasXCliente(lstClientes);

   return 0;
}
