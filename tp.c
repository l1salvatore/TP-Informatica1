#include <stdio.h>
#include <stdlib.h>
#define SECTOR 0
#define CANTIDAD 1

void filtrar(char TipoSensor) {
    int ID,Hora,Minuto;
    char TipoSensor_;
    float CotaInf, CotaSup, Medicion;
    FILE *mediciones = fopen("mediciones.dat","r");
    fscanf(mediciones,"%d %c %f %f %f %d %d",&ID,&TipoSensor_,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto);
    while(feof(mediciones)==0){
            if (TipoSensor_ == TipoSensor) 
                printf("%d\t%c\t%f\t%f\t%f\t%d\t%d\n",ID,TipoSensor_,CotaInf,CotaSup,Medicion,Hora,Minuto);
            fscanf(mediciones,"%d %c %f %f %f %d %d",&ID,&TipoSensor_,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto);
    }
    fclose(mediciones);
}

void generarAlarmas() {
   int ID,Hora,Minuto;
   char TipoSensor;
   float CotaInf, CotaSup, Medicion;
   FILE *alarmas = fopen("alarmas.dat","w");
   FILE *mediciones = fopen("mediciones.dat","r");
   fscanf(mediciones,"%d %c %f %f %f %d %d",&ID,&TipoSensor,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto);
   while(feof(mediciones)==0){
            if (Medicion < CotaInf || Medicion > CotaSup) 
                fprintf(alarmas,"%d\t%c\t%f\t%f\t%f\t%d\t%d\n",ID,TipoSensor,CotaInf,CotaSup,Medicion,Hora,Minuto);
    	    fscanf(mediciones,"%d %c %f %f %f %d %d",&ID,&TipoSensor,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto); 
   }
   fclose(mediciones);
   fclose(alarmas);
}

int cuen_alarm(int num_sect) {
   int ID,Hora,Minuto;
   char TipoSensor;
   float CotaInf, CotaSup, Medicion;
   int cantidadAlarmas = 0;
   FILE *alarmas = fopen("alarmas.dat","r");
   fscanf(alarmas,"%d %c %f %f %f %d %d",&ID,&TipoSensor,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto);
   while(!feof(alarmas)){
            if (ID / 100 == num_sect)
		cantidadAlarmas++;
            fscanf(alarmas,"%d %c %f %f %f %d %d",&ID,&TipoSensor,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto);

    }
   fclose(alarmas);
   return cantidadAlarmas;
}


void contarAlarmas(int (*alarmas)[6]){
   int i;
   for(i=0;i<6;i++){
	alarmas[SECTOR][i] = i+1;
	alarmas[CANTIDAD][i] = cuen_alarm(i+1);
   }
}

void ordenarAlarmas(int (*alarmas)[6]){
   int i,aux,aux1,swap = 1;
   while(swap == 1){
	swap = 0;
	for(i=0;i<5;i++)
	  if (alarmas[CANTIDAD][i] < alarmas[CANTIDAD][i+1]){
		aux = alarmas[SECTOR][i];
		aux1 = alarmas[CANTIDAD][i];
		alarmas[SECTOR][i] = alarmas[SECTOR][i+1];
		alarmas[CANTIDAD][i] = alarmas[CANTIDAD][i+1];
		alarmas[SECTOR][i+1] = aux;
		alarmas[CANTIDAD][i+1] = aux1;
		swap = 1;
	  }	
  }
}

void AlarmasXSector() {
   int j,alarmas[2][6];
   contarAlarmas(alarmas);
   ordenarAlarmas(alarmas);
   printf("Alarmas por sector\n");
   for(j=0;j<6;j++)
	printf("Sector %d: %d alarmas/s\n",alarmas[SECTOR][j],alarmas[CANTIDAD][j]);
}



void validarOp(int *i, int min, int max){
    while (*i < min || *i > max){
        printf("Opc invalida, vuelva a ingresar!\n");        
        scanf(" %i",&*i);
    }
}

void validarVariableTipo(char *c){
    while ((*c != 'T') && (*c != 'P') && (*c != 'N') && (*c != 'C')) {
        printf("Variable invalida, vuelva a ingresar!\n");
        fflush(stdin);        
        scanf(" %c",&*c);
    }
}
 
void mostrarMenu(){
    printf("================================================\n");
    printf("          ANITSELEC              \n");
    printf("================================================\n");
    printf("1- Filtrar por variable\n");
    printf("2- Generar alarmas\n");
    printf("3- Alarmas por sector\n");
    printf("4- Salir\n");
}



main() {
    int op=-5;
    char c;
    while (op != 4) {
        mostrarMenu();
        scanf(" %i",&op);
        validarOp(&op,1,4);
        switch (op) {
            case 1:
                printf("Ingrese la variable\n");
                fflush(stdin);
                scanf(" %c",&c);
                validarVariableTipo(&c);
                filtrar(c);
                break;
            case 2:
		generarAlarmas();
                break;
            case 3:
		AlarmasXSector();
                break;
        }
    }
}
    


