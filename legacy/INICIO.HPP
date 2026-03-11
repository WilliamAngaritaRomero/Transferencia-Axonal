#define NR_CADENA 16
#define NR_ANCHO 20

typedef struct vneurona {
       vneurona *axion[28];
       unsigned long direccion;
};

typedef struct st_saber{
       unsigned long registro;
       char cadena[NR_CADENA];
       char concepto[NR_ANCHO];
       unsigned long imagen;
       unsigned long sonido;
};

