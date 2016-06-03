#include <stdio.h>
#include <stdlib.h>

void filtrar(char TipoSensor) {
    int ID,Hora,Minuto;
    char TipoSensor_;
    float CotaInf, CotaSup, Medicion;
    FILE *mediciones = fopen("mediciones.dat","r");
    while(feof(mediciones)==0){
            fscanf(mediciones,"%d %c %f %f %f %d %d",&ID,&TipoSensor_,&CotaInf,&CotaSup,&Medicion,&Hora,&Minuto);
            if (TipoSensor_ == TipoSensor) 
                printf("%d\t%c\t%f\t%f\t%f\t%d\t%d\n",ID,TipoSensor_,CotaInf,CotaSup,Medicion,Hora,Minuto);
    }
    fclose(mediciones);
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
                break;
            case 3:
                break;
        }
    }
}
    


