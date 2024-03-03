
/*

Se requiere un programa que informe sobre la posición actual de cada uno de los equipos que participan de un torneo de fútbol.
Contamos con archivos: RESULTADOS.dat, con los resultados de los partidos que se jugaron durante la última fecha, y EQUIPOS.dat que contiene la información de los e-quipos que participan del torneo.
La estructura de cada uno de estos archivos la vemos a continuación.

RESULTADOS
   struct Resultado {
      int idEq1;
      int idEq2;
      int codRes;
      char estadio[20];
   };

EQUIPOS
   struct Equipo {
      int idEq;
      char nombre[20];
      int puntos;
   };

El valor del campo codRes (código de resultado) indica qué equipo ganó el partido. Si codRes < 0 significa que ganó el equipo identificado con idEq1. Si codRes > 0 el ganador fue el equipo identificado con idEq2. Finalmente, si codRes es 0 (cero) el partido resultó en empate.
El equipo ganador acumula 3 puntos. Si empataron le corresponde 1 punto cada uno. El perdedor no recibe puntos.
Se pide:
   1. Informar la tabla de posiciones actualizada al día del proceso.
   2. Informar, para cada estadio, cuántos partidos se jugaron y cuántos de estos partidos resultaron empatados.
   3. Actualizar las puntuaciones en el archivo EQUIPOS.dat.

*/

#include <iostream>
#include "files.hpp"
#include "List.hpp"
#include "futbol.hpp"
using namespace std;

int main()
{
   List<REquipo> lstREq = leerEquipos();
   List<REstadio> lstEst = list<REstadio>();

   FILE* f = fopen("RESULTADOS.bat", "r+b");
   Resultado res = read<Resultado>(f);

   while (!feof(f)) {
      procesarResultado(res, lstREq);
      listarREstadio(res, lstEst);
      res = read<Resultado>(f);
   }

   /* -- Imprimo los resultados -- */

   mostrarTablaDePosiciones(lstREq);
   mostrarInfoEstadios(lstEst);

   /* -- Actualizo los registros -- */

   actualizarPuntajes(lstREq);

   return 0;
}
