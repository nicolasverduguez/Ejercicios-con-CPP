#ifndef _MAINHPP
#define _MAINHPP
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <cmath>
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/tokens.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/Coll.hpp"
#include "biblioteca/tads/Array.hpp"
#include "biblioteca/tads/Map.hpp"
#include "biblioteca/tads/List.hpp"
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

int cmpCiudadIdCiu(Ciudad ciu, int idCiu) {
   return ciu.idCiu - idCiu;
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

RVuelo rVuelo(Vuelo vue, int cantAsientos) {
   RVuelo rVue;
   rVue.vuelo = vue;
   rVue.cantAsientosReservados = cantAsientos;
   return rVue;
}

Cliente cliente(int idCli, int millasAcum) {
   Cliente c;
   c.idCli = idCli;
   c.millasAcum = millasAcum;
   return c;
}

List<Ciudad> subirCiudades() {
   List<Ciudad> lstCiudad = list<Ciudad>();

   FILE* f = fopen("CIUDADES.dat", "r+b");
   Ciudad ciu = read<Ciudad>(f);

   while (!feof(f)) {
      listAdd<Ciudad>(lstCiudad, ciu);
      ciu = read<Ciudad>(f);
   }

   fclose(f);
   return lstCiudad;
}

List<RVuelo> subirVuelos() {
   List<RVuelo> lstRVuelo = list<RVuelo>();

   FILE * f = fopen("VUELOS.dat", "r+b");
   Vuelo vue = read<Vuelo>(f);

   while (!feof(f)) {
      RVuelo rVue = rVuelo(vue, 0);
      listAdd<RVuelo>(lstRVuelo, rVue);
      vue = read<Vuelo>(f);
   }

   fclose(f);
   return lstRVuelo;
}

bool procesarReserva(Reserva res, List<RVuelo>& lstRVuelo) {
   bool puedeReservar = false;
   RVuelo* rVue = listFind<RVuelo>(lstRVuelo, res.idVue, cmpRVueloIdVue);

   if (rVue->cantAsientosReservados + res.cant < rVue->vuelo.cap) {
      rVue->cantAsientosReservados += res.cant;
      puedeReservar = true;
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

int calcularMillas(Reserva res, List<Ciudad> lstCiudad, List<RVuelo> lstRVuelo) {
   int cantMillas;

   RVuelo* rVue = listFind<RVuelo>(lstRVuelo, res.idVue, cmpRVueloIdVue);
   int idCiuOri = rVue->vuelo.idOri, idCiuDes = rVue->vuelo.idOri;

   Ciudad* ciuOri = listFind<Ciudad>(lstCiudad, idCiuOri, cmpCiudadIdCiu);
   Ciudad* ciuDes = listFind<Ciudad>(lstCiudad, idCiuDes, cmpCiudadIdCiu);

   return abs(ciuOri->millas - ciuDes->millas);
}

void sumarMillas(Cliente* cli, int millasAsig) {
   &(cli->millasAcum) += millasAsig;
}

#endif


