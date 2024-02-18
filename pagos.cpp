#include <iostream>
#include <string>
#include "main.hpp"
using namespace std;

/* + ----------- +
 * + Estructuras +
 * + ----------- +
 */

struct Fecha {
   int dia;
   int mes;
   int anio;
};

struct Pago {
   int dni;
   Fecha fecha;
   double importe;
};

/* + -------------------- +
 * + Funciónes auxiliares +
 * + -------------------- +
 */


/* + --------- +
 * + Funciones +
 * + --------- +
 */

Fecha fecha(int dia, int mes, int anio) {
   Fecha f;
   f.dia = dia;
   f.mes = mes;
   f.anio = anio;
   return f;
}

Pago pago(int dni, Fecha f, double impo) {
   Pago p;
   p.dni = dni;
   p.fecha = f;
   p.importe = impo;
   return p;
}

void infoPagos(Pago arr[], int cntPagos) {

   int dniAnt, cntPagoXDni = 0;
   double impoTotalXDni;

   int totalPersonas = 0, impoMax = 0, dniMaxImpo;
   double impoTotalGral = 0, promPagos;

   for (int i = 0; i < cntPagos; i++) {

      /* -- Leo un pago -- */
      Pago elm = arr[i];

      /* -- Verifico que el DNI sea el primero o el mismo que el anterior -- */
      if (dniAnt == elm.dni || i == 0) {

         /* -- Acumulo los valores -- */
         dniAnt = elm.dni;
         cntPagoXDni++;
         impoTotalXDni += elm.importe;

      } else {

         /* -- Muestro lo acumulado para ese DNI -- */
         cout << "DNI: " << dniAnt << "\nCantidad de Pagos: " << cntPagoXDni << "\nImporte Total: " << impoTotalXDni << "\nPromedio de Pago: " << (impoTotalXDni / cntPagoXDni) << endl;
         totalPersonas++;
         impoTotalGral += impoTotalXDni;

         if (impoTotalXDni > impoMax) {
            impoMax = impoTotalXDni;
            dniMaxImpo = dniAnt;
         }

         /* -- Reinicio los valores para el proximo DNI -- */
         dniAnt = elm.dni;
         cntPagoXDni = 1;
         impoTotalXDni = elm.importe;
      }

   }

   /* -- Muestro los totales -- */
   cout << "Cant. personas que realizaron al menos un pago: " << totalPersonas << "\nProm. Importes Pagados: " << (impoTotalGral / cntPagos) << "\nPersona que más pago:" << dniMaxImpo;

}

int main()
{

   /* -- Implementar la solucion, las funciones ya estan definidas -- */


   return 0;

}
