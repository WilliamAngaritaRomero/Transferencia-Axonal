#include <fstream.h>
#include <iostream.h>
#include "neurona.cpp"

class clssNeurona{
	public:
      char nombre[];
      char palabra[NR_CADENA];
      char respuesta[NR_ANCHO];
      void buscar(char palabra[],long lugar);      
      clssNeurona ();
      ~clssNeurona(){return ;}

      char Archivo[];
      vneurona alfa;
      long aprender(char *Acadena,char *Aconcepto);
      void despertar();
      void recordar(long r,char t[]);
      void leer();
      long tamano();
};

clssNeurona::clssNeurona() 
  {  strcpy(Archivo,nombre);
     despertar();
  }  

void clssNeurona::buscar(char bcadena[],long lugar)
{if (bcadena!=NULL)
 {  char inicio=bcadena[0];
     unsigned int z;
     z = inicio-96;
     if (z>=1 && z<=27)
     {  if (alfa.axion[z] == NULL) 
        {  vneurona *temporal;
           temporal = new vneurona;
           alfa.axion[z] = temporal;
        }   
        vneurona *proxima;
        proxima = alfa.axion[z];
        unsigned int y;
        for (int i=1;i<strlen(bcadena);i++)
        {  y= bcadena[i] - 96;
           if (proxima->axion[y] == NULL) 
             {  vneurona *siguiente;
               siguiente = new vneurona;
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
             recordar(proxima->direccion,respuesta);
           else
           { leer();
             proxima->direccion=aprender(bcadena,respuesta);
           }  
        }  
     }
 }
 return;
}
void clssNeurona::leer()
{  char xcadena[NR_ANCHO];
   cout << "Que es " << palabra << " ? " ;cin >> xcadena;
   strcpy(respuesta,xcadena);
   return;
}
long clssNeurona::aprender(char Acadena[],char Aconcepto[])
{ st_saber Snocion;
  strcpy(Snocion.cadena,Acadena);
  strcpy(Snocion.concepto,Aconcepto);
  Snocion.registro=tamano()/sizeof(Snocion)+1;
  fstream out(Archivo,ios::in|ios::out);
  if (out)                                    
  { out.seekp(0,ios::end);
    out.write((unsigned char *)&Snocion,sizeof(Snocion));
    out.close();
  }   
  return Snocion.registro;
}

void clssNeurona::despertar()
{ st_saber Snocion;
  fstream in(Archivo,ios::in);
  if (in)                                    
  { int r=0;
    while (!in.eof())
    { in.seekg(r++*sizeof(Snocion));
      in.read((unsigned char *)&Snocion,sizeof(Snocion));
      if (!in.eof())
        buscar(Snocion.cadena,Snocion.registro);
    }
    in.close();
  }   
  return ;
} 

long clssNeurona::tamano()
{ int r=0;
  fstream in(Archivo,ios::in);
  if (in)                                    
  { st_saber c; 
    while (!in.eof())
    { in.seekg(r++*sizeof(c));
      in.read((unsigned char *)&c,sizeof(c));
    }
    in.close();
    r = (r-1) * sizeof(c) ;
  }   
  return r;
} 

void clssNeurona::recordar(long r,char t[])
{ st_saber Snocion;
  fstream in(Archivo,ios::in);
  if (in)                                    
  { in.seekg(--r*sizeof(Snocion));
    in.read((unsigned char *)&Snocion,sizeof(Snocion));
    in.close();
  }   
  strcpy(t,Snocion.concepto);
  return ;
} 


