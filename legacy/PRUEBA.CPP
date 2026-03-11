#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include "neurona.hpp"

int main(int argc, char *argv[])
{ char entrada[NR_CADENA];
  char cabeza[11];
  char temporal[11];

  strcpy(cabeza,"memoria.nrn");
  clssNeurona x(cabeza);
  do
  { for(int i=0;i<11;i++)
      temporal[i]=(char)" ";
    cout << "? ";cin >>temporal;
    for(int i=0;i<11;i++)
      entrada[i]=temporal[i];
    x.estimular(entrada,-1);
    cout << "!! "<< x.sinapsis << " Es " << x.respuesta <<endl;
  } while (strcmp(entrada,".")>0);
  return 0;
}


