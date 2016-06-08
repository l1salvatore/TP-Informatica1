#include <stdio.h>
#define SECTOR 0
#define CANTIDAD 1

void filtrar(char TipoSensor) {
    int ID,Hora,Minuto;
    char TipoSensor_;
    float CotaInf, CotaSup, Medicion;
    FILE *mediciones = fopen("mediciones.dat","r");
    fscanf(mediciones,"%d %c %f %f %f %d %d",&ID,&TipoSensor_,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto);
    printf("\t\tID_Sensor\tMedicion\n");
    while(feof(mediciones)==0){
            if (TipoSensor_ == TipoSensor) 
                printf("\t\t%d\t\t%f\n",ID,Medicion);
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
   int i,aux,swap = 1;
   while(swap == 1){
	swap = 0;
	for(i=0;i<5;i++)
	  if (alarmas[CANTIDAD][i] < alarmas[CANTIDAD][i+1]){
		aux = alarmas[SECTOR][i];
		alarmas[SECTOR][i] = alarmas[SECTOR][i+1];
		alarmas[SECTOR][i+1] = aux;
		aux = alarmas[CANTIDAD][i];
		alarmas[CANTIDAD][i] = alarmas[CANTIDAD][i+1];
		alarmas[CANTIDAD][i+1] = aux;
		swap = 1;
	  }	
  }
}

void AlarmasXSector() {
   int j,alarmas[2][6];
   contarAlarmas(alarmas);
   ordenarAlarmas(alarmas);
   printf("\t\tAlarmas por sector\n");
   for(j=0;j<6;j++)
	printf("\t\tSector %d: %d alarmas/s\n",alarmas[SECTOR][j],alarmas[CANTIDAD][j]);
}



void validarOp(int *i, int min, int max){
    while (*i < min || *i > max){
        printf("AVISO:Opcion invalida, vuelva a ingresar!\n"); 
        printf("Ingrese Opcion>");       
        scanf(" %i",&*i);
    }
}

void validarVariableTipo(char *c){
    while ((*c != 'T') && (*c != 'P') && (*c != 'N') && (*c != 'C')) {
        printf("AVISO:Variable invalida, vuelva a ingresar!\n");
        fflush(stdin);
        printf("Ingrese la variable>");        
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
    printf("Ingrese Opcion>");
}



main() {
    int op=-5;
    int ArchAlarmasGenerado = 0;
    char c;
    while (op != 4) {
        mostrarMenu();
        scanf(" %i",&op);
        validarOp(&op,1,4);
        switch (op) {
            case 1:
                printf("Ingrese la variable>");
                fflush(stdin);
                scanf(" %c",&c);
                validarVariableTipo(&c);
                filtrar(c);
                break;
            case 2:
		        generarAlarmas();
		        ArchAlarmasGenerado=1;
                break;
            case 3:
		        if (ArchAlarmasGenerado==0)
		            printf("AVISO:Primero tiene que generar las alarmas!\n");
		        else 
		            AlarmasXSector();
                break;
        }
    }
}
    


