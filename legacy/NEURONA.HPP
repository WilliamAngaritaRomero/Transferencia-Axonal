#include <fstream.h>
#include <iostream.h>
#include "inicio.hpp"

class clssNeurona{
      char memoria[11];
	public:
      vneurona *alfa;
      char sinapsis[NR_CADENA];
      char respuesta[NR_ANCHO];
      clssNeurona (char nombre[11]);
      ~clssNeurona(){delete alfa;}
      void estimular(char sinapsis[NR_CADENA],long lugar);      
      long aprender();
      void despertar();
      void recordar(unsigned long r);
      void leer();
      unsigned long tamano();
};

clssNeurona::clssNeurona(char nombre[11]) 
{  strcpy(memoria,nombre);
   alfa=new vneurona;
   for (int k=0;k<=27;k++)
     alfa->axion[k]=0;
   alfa->direccion=0;  
   despertar();
}  

void clssNeurona::despertar()
{ st_saber Snocion;
  fstream in(memoria,ios::in);
  if (in)                                    
  { int r=0;
    while (!in.eof())
    { in.seekg(r*sizeof(Snocion));
      in.read(&Snocion,sizeof(Snocion));
      if (!in.eof())
        estimular(Snocion.cadena,Snocion.registro);
      r++;
    }
    in.close();
  }   
  return ;
} 

void clssNeurona::estimular(char bcadena[NR_CADENA],long lugar)
{  strcpy(sinapsis,bcadena);
   if (bcadena!=NULL)
   { unsigned int z;
     z = ((int) bcadena[0])-96;
     if (z>=1 && z<=26)
     {  vneurona *proxima;
        if (alfa->axion[z] == NULL) 
           {  proxima = new vneurona;
              for (int k=0;k<=28;k++)
                  proxima->axion[k]=0;
              proxima->direccion=0;  
              alfa->axion[z] = proxima;
           }
        else   
           proxima = alfa->axion[z];
        unsigned int y;
        for (int i=1;i<strlen(bcadena);i++)
        {  y= ((int) bcadena[i]) - 96;
           if (proxima->axion[y] == NULL) 
             { vneurona *siguiente;
               siguiente = new vneurona;
               for (int k=0;k<=28;k++)
                  siguiente->axion[k]=0;
               siguiente->direccion=0;  
               proxima->axion[y] = siguiente;
               proxima = siguiente;
             }
           else
             proxima = proxima->axion[y];
        }
        if (lugar>0)
           proxima->direccion=lugar;
        else 
        {  if (proxima->direccion>0)
             recordar(proxima->direccion);
           else
           { leer();
             proxima->direccion=aprender();
           }  
        }  
     }
   }
   return;
}

void clssNeurona::recordar(unsigned long r)
{ st_saber Snocion;
  fstream in(memoria,ios::in);
  if (in)                                    
  { r--;
    in.seekg(r*sizeof(Snocion));
    in.read(&Snocion,sizeof(Snocion));
    strcpy(respuesta,Snocion.concepto);
    in.close();
  } 
  return ;
} 

void clssNeurona::leer()
{  for(int i=0;i<NR_ANCHO;i++)
      respuesta[i]=(char)" ";
   cout << "Que es " << sinapsis << " ? " ;cin >> respuesta;
   return;
}

long clssNeurona::aprender()
{ st_saber Snocion;
  for(int i=0;i<NR_CADENA;i++)
  {  Snocion.cadena[i]=(char)" ";
     Snocion.cadena[i]=sinapsis[i];
  }
  for(int i=0;i<NR_ANCHO;i++)
  {  Snocion.concepto[i]=(char)" ";
     Snocion.concepto[i]=respuesta[i];
  }
  Snocion.registro=tamano()/sizeof(Snocion);
  Snocion.imagen=0;
  Snocion.sonido=0;
  fstream out(memoria,ios::in|ios::out);
  if (out)                                    
  { out.seekp(0,ios::end);
    out.write(&Snocion,sizeof(Snocion));
    out.close();
  }   
  return Snocion.registro;
}

unsigned long clssNeurona::tamano()
{ int r=0;
  unsigned long xtama;
  
  fstream in(memoria,ios::in|ios::out);
  if (in)                                    
  { st_saber c; 
    while (!in.eof())
    { in.seekg(r*sizeof(c));
      in.read(&c,sizeof(c));
      r++;
    }
    in.close();
    (r==0)?xtama=0:xtama = r * sizeof(c) ;
  }   
  return xtama;
}
