#ifndef _MAINHPP
#define _MAINHPP
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <cmath>
#include "files.hpp"
#include "List.hpp"
using namespace std;

/* -- Estructuras -- */

struct Ciudad {
   int idCiu;
   char descr[20];
   int millas;
};

struct Vuelo {
   int idVue;
   int cap;
   int idOri; // idCiu origen
   int idDes; // idCiu origen
};

struct Reserva {
   int idCli;
   int idVue;
   int cant;
};

struct RVuelo {
   Vuelo vuelo;
   int cantAsientosReservados;
   bool vueloLleno;
};

struct RCiudad {
   Ciudad ciudad;
   int cont;
};

struct Cliente {
   int idCli;
   int millasAcum;
};

/* -- Funciones de comparación */

int cmpRVueloIdVue(RVuelo rVue, int idVue) {
   return rVue.vuelo.idDes - idVue;
}

int cmpClienteIdCli(Cliente cli, int idCli) {
   return cli.idCli - idCli;
}

int cmpRCiudadIdCiu(RCiudad rCiu, int idCiu) {
   return rCiu.ciudad.idCiu - idCiu;
}

/* -- Funciones -- */

Ciudad ciudad(int idCiu, char descr[], int millas) {
   Ciudad c;
   c.idCiu = idCiu;
   strcpy(c.descr, descr);
   c.millas = millas;
   return c;
}

Vuelo vuelo(int idVue, int cap, int idOri, int idDes) {
   Vuelo v;
   v.idVue = idVue;
   v.cap = cap;
   v.idOri = idOri;
   v.idDes = idDes;
   return v;
}

Reserva reserva(int idCli, int idVue, int cant) {
   Reserva r;
   r.idCli = idCli;
   r.idVue = idVue;
   r.cant = cant;
   return r;
}

RCiudad rCiudad(Ciudad ciu, int cont) {
   RCiudad rCiu;
   rCiu.ciudad = ciu;
   rCiu.cont = cont;
   return rCiu;
}

RVuelo rVuelo(Vuelo vue, int cantAsientos, bool estVuelo) {
   RVuelo rVue;
   rVue.vuelo = vue;
   rVue.cantAsientosReservados = cantAsientos;
   rVue.vueloLleno = estVuelo;
   return rVue;
}

Cliente cliente(int idCli, int millasAcum) {
   Cliente c;
   c.idCli = idCli;
   c.millasAcum = millasAcum;
   return c;
}

string charToString(char cadena[], int longitud) {
   string str = "";

   for (int i = 0; i < longitud; i++) {
      str += cadena[i];
   }

   return str;
}

string rVueloToString(RVuelo* rVue) {
   int cantPlazasRechazadas = rVue->vuelo.cap - rVue->cantAsientosReservados;
   string vueloSale = "Incompleto";
   if (rVue->vueloLleno) {
      vueloSale = "Completo";
   }

   return "Plazas rechazadas: " + to_string(cantPlazasRechazadas) + " | El vuelo sale: " + vueloSale + "\n";
}

List<RCiudad> subirCiudades() {
   List<RCiudad> lstRCiudad = list<RCiudad>();

   FILE* f = fopen("CIUDADES.dat", "r+b");
   Ciudad ciu = read<Ciudad>(f);

   while (!feof(f)) {
      listAdd<RCiudad>(lstRCiudad, rCiudad(ciu, 0));
      ciu = read<Ciudad>(f);
   }

   fclose(f);
   return lstRCiudad;
}

List<RVuelo> subirVuelos() {
   List<RVuelo> lstRVuelo = list<RVuelo>();

   FILE * f = fopen("VUELOS.dat", "r+b");
   Vuelo vue = read<Vuelo>(f);

   while (!feof(f)) {
      listAdd<RVuelo>(lstRVuelo, rVuelo(vue, 0, false));
      vue = read<Vuelo>(f);
   }

   fclose(f);
   return lstRVuelo;
}

bool procesarReserva(Reserva res, List<RCiudad>& lstRCiudad, List<RVuelo>& lstRVuelo) {
   bool puedeReservar = false;
   RVuelo* rVue = listFind<RVuelo>(lstRVuelo, res.idVue, cmpRVueloIdVue);

   if (rVue->cantAsientosReservados + res.cant <= rVue->vuelo.cap) {
      puedeReservar = true;
      rVue->cantAsientosReservados += res.cant;
      rVue->vueloLleno = (rVue->cantAsientosReservados == rVue->vuelo.cap);

      RCiudad* rCiu = listFind<RCiudad>(lstRCiudad, rVue->vuelo.idDes, cmpRCiudadIdCiu);
      rCiu->cont++;
   }

   return puedeReservar;
}

Cliente* obtenerCliente(Reserva res, List<Cliente> lstCliente) {
   Cliente* cli = listFind<Cliente>(lstCliente, res.idCli, cmpClienteIdCli);

   if (cli != NULL) {
      Cliente auxCli = cliente(res.idCli, 0);
      cli = listAdd<Cliente>(lstCliente, auxCli);
   }

   return cli;
}

int calcularMillas(Reserva res, List<RCiudad> lstRCiudad, List<RVuelo> lstRVuelo) {
   RVuelo* rVue = listFind<RVuelo>(lstRVuelo, res.idVue, cmpRVueloIdVue);
   int idCiuOri = rVue->vuelo.idOri, idCiuDes = rVue->vuelo.idOri;

   RCiudad* ciuOri = listFind<RCiudad>(lstRCiudad, idCiuOri, cmpRCiudadIdCiu);
   RCiudad* ciuDes = listFind<RCiudad>(lstRCiudad, idCiuDes, cmpRCiudadIdCiu);

   return abs(ciuOri->ciudad.millas - ciuDes->ciudad.millas);
}

void sumarMillas(Cliente* cli, int millasAsig) {
   cli->millasAcum += millasAsig;
}

void mostrarEleccionDeFamilias(List<RCiudad> lstRCiudad) {

   while (listHasNext<RCiudad>(lstRCiudad)) {
      RCiudad* rCiu = listNext<RCiudad>(lstRCiudad);
      cout << "Ciudad: " << charToString(rCiu->ciudad.descr, 20) << " | Cantidad de familias que la eligieron como Destino: " << to_string(rCiu->cont) << "\n" << endl;
   }
}

void mostrarDetalleDeVuelos(List<RVuelo> lstRVuelo) {

   while (listHasNext<RVuelo>(lstRVuelo)) {
      RVuelo* rVue = listNext<RVuelo>(lstRVuelo);

      int cantPlazasRechazadas = rVue->vuelo.cap - rVue->cantAsientosReservados;
      string vueloSale = "Incompleto";
      if (rVue->vueloLleno) {
         vueloSale = "Completo";
      }

      cout << "Plazas rechazadas: " << to_string(cantPlazasRechazadas) << " | El vuelo sale: " << vueloSale << "\n" << endl;
   }
};

void mostrarMillasXCliente(List<Cliente> lstClientes) {

   while (listHasNext<Cliente>(lstClientes)) {
      Cliente* cli = listNext<Cliente>(lstClientes);
      cout << "Cliente: " << cli->idCli + " | Millas acumuladas: " << to_string(cli->millasAcum) << "\n" << endl;
   }
};

#endif



