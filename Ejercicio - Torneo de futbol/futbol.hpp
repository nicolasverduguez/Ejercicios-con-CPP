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

struct Resultado {
   int idEq1;
   int idEq2;
   int codRes;
   char estadio[20];
};

struct Equipo {
   int idEq;
   char nombre;
   int puntos;
};

struct REquipo {
   Equipo equipo;
   int acum;
};

struct REstadio {
   string estadio;
   int partidosJugados;
   int partidosEmpatados;
};

/* -- Funciones de comparacion -- */

int cmpREquipoIdEq(REquipo rEq, int idEq) {
   return rEq.equipo.idEq - idEq;
}

int cmpREquipoREquipo(REquipo rEq1, REquipo rEq2) {
   return rEq1.acum - rEq2.acum;
}

int cmpREstadioString(REstadio rEst, string est) {
   return rEst.estadio<est?-1: rEst.estadio>est?1: 0;
};

/* -- Funciones de conversion -- */

string charToString(char arr[]) {
   string ret = "";
   int i = 0;
   while (arr[i] != '\0') {
      ret += arr[i];
      i++;
   }
   return ret;
}

string rEquipoToString(REquipo* rEq) {
   return "ID: " + to_string(rEq->equipo.idEq) + " Equipo: " + charToString(rEq->equipo.nombre) + " Puntaje: " + to_string(rEq->acum);
}

/* -- Funciones -- */

Resultado resultado(int idEq1, int idEq2, int codRes, char estadio[]) {
   Resultado r;
   r.idEq1 = idEq1;
   r.idEq2 = idEq2;
   r.codRes = codRes;
   strcpy(r.estadio, estadio);
   return r;
}

Equipo equipo(int idEq, char nombre, int puntos) {
   Equipo eq;
   eq.idEq = idEq;
   eq.nombre = nombre;
   eq.puntos = puntos;
   return eq;
}

REquipo rEquipo(Equipo eq, int acum) {
   REquipo rEq;
   rEq.equipo = eq;
   rEq.acum = acum;
   return rEq;
}

REstadio rEstadio(string estadio, int partJug, int partEmp) {
   REstadio rEst;
   rEst.estadio = estadio;
   rEst.partidosJugados = partJug;
   rEst.partidosEmpatados = partEmp;
   return rEst;
}

List<REquipo> leerEquipos() {
   List<REquipo> lstREquipos = list<REquipo>();
   FILE* f = fopen("EQUIPOS.dat", "r+b");
   Equipo eq = read<Equipo>(f);

   while (!feof(f)) {
      listAdd<REquipo>(lstREquipos, rEquipo(eq, 0));
      eq = read<Equipo>(f);
   }

   fclose(f);
   return lstREquipos;
}

void procesarResultado(Resultado res, List<REquipo>& lstREq) {

   REquipo* rEq1 = listFind<REquipo>(lstREq, res.idEq1, cmpREquipoIdEq);
   REquipo* rEq2 = listFind<REquipo>(lstREq, res.idEq2, cmpREquipoIdEq);

   if (res.codRes < 0) {
      rEq1->acum += 3;
   } else {
      if (res.codRes > 0) {
         rEq2->acum += 3;
      } else {
         rEq1->acum++;
         rEq2->acum++;
      }
   }
}

void mostrarTablaDePosiciones(List<REquipo> lstREquipo) {
   listSort<REquipo>(lstREquipo, cmpREquipoREquipo);

   listReset<REquipo>(lstREquipo);
   while (listHasNext<REquipo>(lstREquipo)) {
      REquipo* rEq = listNext<REquipo>(lstREquipo);
      cout << rEquipoToString(rEq) << endl;
   }
}

void listarREstadio(Resultado res, List<REstadio>& lstREst) {

   string estadio = charToString(res.estadio);
   REstadio* rEst = listFind<REstadio>(lstREst, estadio, cmpREstadioString);

   if (rEst == NULL) {

      REstadio nuevoREst;
      if (res.codRes == 0) {
         nuevoREst = rEstadio(res.estadio, 1, 0);
      } else {
         nuevoREst = rEstadio(res.estadio, 1, 1);
      }
      listAdd<REstadio>(lstREst, nuevoREst);
   } else {

      if (res.codRes == 0) {
         rEst->partidosJugados++;
         rEst->partidosEmpatados++;
      } else {
         rEst->partidosJugados++;
      }
   }

}

void mostrarInfoEstadios(List<REstadio> lstREstadio) {
   listReset<REstadio>(lstREstadio);

   while (listHasNext<REstadio>(lstREstadio)) {
      REstadio * rEst = listNext<REstadio>(lstREstadio);
      cout << "Estadio: " + rEst->estadio << " Partidos Jugados: " + to_string(rEst->partidosJugados) << " Partidos Empatados: " + to_string(rEst->partidosEmpatados) << endl;
   }
}

void actualizarPuntajes(List<REquipo> lstREquipo) {

   FILE* f = fopen("EQUIPOS.dat", "w+b");

   while (listHasNext<REquipo> (lstREquipo)) {
      REquipo* rEq = listNext<REquipo>(lstREquipo);
      Equipo eq = equipo(rEq->equipo.idEq, rEq->equipo.nombre, rEq->acum);
      write<Equipo>(f, eq);
   }

   fclose(f);
}

#endif


