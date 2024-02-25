
/* Se ingresa un conjunto de valores num�ricos enteros que finaliza con la llegada de un 0 (cero), se pide informar:
 *    1. Cu�ntas veces se ingresaron valores consecutivos ascendentes. A esto, en adelante, lo llamaremos seguidilla.
 *    2. Por cada seguidilla, qu� cantidad de elementos la componen.
 *    3. En qu� posici�n relativa aparece la seguidilla m�s larga.
 *
 * Por ejemplo, supongamos que los datos que ingresa el usuario son los siguientes: 5 3 1 4 6 8 3 1 4 5 6 7 9 4 6 8 4 2 1 3 5 6 7 2 0
 *
 * La salida que deber� arrojar el programa ser�:
 *    1. Cantidad de seguidillas: 4.
 *    2. 4 elementos (seguidilla azul), 6 elementos (seguidilla verde), 3 elementos (seguidilla roja), 5 elementos (seguidilla violeta).
 *    3. La seguidilla m�s larga se ingres� en la posici�n relativa: 2.
 * */

#include <iostream>
using namespace std;

void inicArr(int a[100]){
   for(int i = 0; i < 100; i++) {
      a[i] = 0;
   }
}

int main()
{

   int num = 0, pos = 0, cantSeg = 0, cntElm = 2, maxCntElm = 0, maxCntElmAnt = 0, maxPosSeg = 0;
   int elmXSeg[100];
   inicArr(elmXSeg);

   cout << "Ingrese numero: ";
   cin >> num;

   while (num != 0) {

      int numAnt = num;

      cout << "Ingrese numero: ";
      cin >> num;

      /* -- Primer seguidilla -- */
      if (num > numAnt) {

         cantSeg++;
         pos++;
         numAnt = num;
         cout << "Ingrese numero: ";
         cin >> num;

         /* -- Extension Seguidilla -- */
         while (num > numAnt) {
            cntElm++;
            numAnt = num;
            cout << "Seguidilla: ";
            cin >> num;
         }

         elmXSeg[pos] = cntElm;
      }

      maxCntElmAnt = cntElm;
      if (maxCntElmAnt > maxCntElm) {
         maxPosSeg = pos;
         maxCntElm = maxCntElmAnt;
      }

      numAnt = 0, cntElm = 2;

   }

   cout << "\nCantidad de seguidillas: " << cantSeg << endl;

   cout << "\nCantidad de elementos en las seguidillas" << endl;
   for (int i = 1; i < 100; i++) {
      if (elmXSeg[i] != 0) {
         cout << elmXSeg[i] << " elementos" << endl;

      }
   }

   cout << "\nLa seguidilla m�s larga se incrusto en la posici�n relativa: " << maxPosSeg;

   return 0;
}
