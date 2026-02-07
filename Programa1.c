#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NNA {
    char nombre[30];
    char apellidop[30];
    char apellidom[30];
    int edad;
    char sexo;
    char login[20];
    char numero[10];
    char correo[50];
    struct NNA *ptrsig;
};

/* --- PROTOTIPOS --- */
int esDuplicado(struct NNA *inicio, char log[], char mail[], struct NNA *omitir);
int listarTodo(struct NNA *inicio);
int buscarPorLogin(struct NNA *inicio);
int agregarNNA(struct NNA **inicio);
int modificarNNA(struct NNA *inicio);

// Función auxiliar para limpiar el búfer del teclado manualmente
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct NNA *inicio = NULL;
    int opcion;

    for (;;) {
        printf("\n--- ADMINISTRADOR DE NNA's ---");
        printf("\n1-. Agregar NNA\n2-. Listar Todo\n3-. Buscar por Login\n4-. Modificar Registro\n5-. Salir\nOpcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            limpiarBuffer(); // Limpia si el usuario mete letras en lugar de números
            continue;
        }
        limpiarBuffer(); // Limpia el 'Enter' después de capturar la opción

        if (opcion == 5) {
            printf("\nCerrando sistema...\n");
            break;
        }

        switch (opcion) {
            case 1: agregarNNA(&inicio); break;
            case 2: listarTodo(inicio); break;
            case 3: buscarPorLogin(inicio); break;
            case 4: modificarNNA(inicio); break;
            default: printf("\nOpcion no valida.\n");
        }
    }
    return 0;
}

int esDuplicado(struct NNA *inicio, char log[], char mail[], struct NNA *omitir) {
    struct NNA *temp = inicio;
    while (temp != NULL) {
        if (temp != omitir) { 
            if (strcmp(temp->login, log) == 0 || strcmp(temp->correo, mail) == 0) {
                return 1; 
            }
        }
        temp = temp->ptrsig;
    }
    return 0;
}

int listarTodo(struct NNA *inicio) {
    if (inicio == NULL) {
        printf("\n[AVISO]: No existen registros.\n");
        return 0;
    }
    struct NNA *aux = inicio;
    printf("\n---------- LISTADO GENERAL ----------");
    while (aux != NULL) {
        printf("\nNombre: %s %s %s", aux->nombre, aux->apellidop, aux->apellidom);
        printf("\nEdad: %d | Sexo: %c", aux->edad, aux->sexo);
        printf("\nLogin: %s | Tel: %s | Correo: %s", aux->login, aux->numero, aux->correo);
        printf("\n-------------------------------------");
        aux = aux->ptrsig;
    }
    return 1;
}

int buscarPorLogin(struct NNA *inicio) {
    char logB[20];
    printf("\nIngrese login a buscar: "); 
    scanf(" %19s", logB); // Limpia y limita
    limpiarBuffer();
    
    struct NNA *aux = inicio;
    while (aux != NULL) {
        if (strcmp(aux->login, logB) == 0) {
            printf("\nDATOS ENCONTRADOS:");
            printf("\nNombre: %s %s %s", aux->nombre, aux->apellidop, aux->apellidom);
            printf("\nEdad: %d anos | Mail: %s", aux->edad, aux->correo);
            return 1;
        }
        aux = aux->ptrsig;
    }
    printf("\n[ERROR]: No se encontro registro.\n");
    return 0;
}

int agregarNNA(struct NNA **inicio) {
    char t_log[20], t_mail[50];
    printf("\n--- REGISTRO NUEVO ---");
    
    printf("\nLogin: "); 
    scanf(" %19s", t_log);
    
    printf("Correo: "); 
    scanf(" %49s", t_mail);

    if (esDuplicado(*inicio, t_log, t_mail, NULL)) {
        printf("\n[ERROR]: El login o correo ya estan registrados.\n");
        limpiarBuffer();
        return 0;
    }

    struct NNA *ptrnew = (struct NNA*) malloc(sizeof(struct NNA));
    if (ptrnew == NULL) return 0;

    strcpy(ptrnew->login, t_log);
    strcpy(ptrnew->correo, t_mail);
    
    printf("Nombre: "); scanf(" %29s", ptrnew->nombre);
    printf("Apellido Paterno: "); scanf(" %29s", ptrnew->apellidop);
    printf("Apellido Materno: "); scanf(" %29s", ptrnew->apellidom);
    
    printf("Edad: "); 
    if(scanf("%d", &ptrnew->edad) != 1) { ptrnew->edad = 0; }
    limpiarBuffer(); // Vital tras leer un entero
    
    printf("Sexo (M/F): "); 
    scanf(" %c", &ptrnew->sexo);
    limpiarBuffer();
    
    printf("Numero: "); 
    scanf(" %9s", ptrnew->numero);
    limpiarBuffer();
    
    ptrnew->ptrsig = NULL;

    if (*inicio == NULL) {
        *inicio = ptrnew;
    } else {
        struct NNA *ptraux = *inicio;
        while (ptraux->ptrsig != NULL) ptraux = ptraux->ptrsig;
        ptraux->ptrsig = ptrnew;
    }
    printf("\n[OK]: Agregado con exito.\n");
    return 1;
}

int modificarNNA(struct NNA *inicio) {
    char logB[20];
    printf("\nLogin del NNA a modificar: "); 
    scanf(" %19s", logB);
    limpiarBuffer();

    struct NNA *aux = inicio;
    while (aux != NULL) {
        if (strcmp(aux->login, logB) == 0) {
            int op;
            printf("\n¿Que desea modificar?\n1.Nombre\n2.Apellidos\n3.Edad\n4.Sexo\n5.Login\n6.Tel\n7.Correo\nOpcion: ");
            if(scanf("%d", &op) != 1) { limpiarBuffer(); return 0; }
            limpiarBuffer();
            
            char nuevo[50];
            if (op != 3 && op != 4) { 
                printf("Nuevo valor: "); 
                scanf(" %49s", nuevo); 
                limpiarBuffer();
            }

            switch(op) {
                case 1: strcpy(aux->nombre, nuevo); break;
                case 2: 
                    strcpy(aux->apellidop, nuevo); 
                    printf("Nuevo Materno: "); scanf(" %29s", aux->apellidom); 
                    limpiarBuffer();
                    break;
                case 3: printf("Nueva edad: "); scanf("%d", &aux->edad); limpiarBuffer(); break;
                case 4: printf("Nuevo sexo (M/F): "); scanf(" %c", &aux->sexo); limpiarBuffer(); break;
                case 5: 
                    if (esDuplicado(inicio, nuevo, aux->correo, aux)) printf(" [ERROR]: Login ocupado.");
                    else strcpy(aux->login, nuevo); 
                    break;
                case 6: strcpy(aux->numero, nuevo); break;
                case 7: 
                    if (esDuplicado(inicio, aux->login, nuevo, aux)) printf(" [ERROR]: Correo ocupado.");
                    else strcpy(aux->correo, nuevo); 
                    break;
                default: printf("Opcion invalida."); return 0;
            }
            printf("\n[OK]: Registro actualizado.\n");
            return 1;
        }
        aux = aux->ptrsig;
    }
    printf("\n[ERROR]: No se encontro el registro.\n");
    return 0;
}
