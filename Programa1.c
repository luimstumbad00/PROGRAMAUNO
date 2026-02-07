#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * ESTRUCTURA: NNA (Niñas, Niños y Adolescentes)
 * Representa un nodo en la lista ligada con datos personales.
 */
struct NNA {
    char nombre[30];
    char apellidop[30];
    char apellidom[30];
    int edad;
    char sexo;
    char login[20];
    char numero[10];
    char correo[50];
    struct NNA *ptrsig; // Puntero al siguiente elemento de la lista
};

/* --- PROTOTIPOS DE FUNCIONES --- */
int esDuplicado(struct NNA *inicio, char log[], char mail[], struct NNA *omitir);
int listarTodo(struct NNA *inicio);
int buscarPorLogin(struct NNA *inicio);
int agregarNNA(struct NNA **inicio);
int modificarNNA(struct NNA *inicio);

int main() {
    struct NNA *inicio = NULL; // Cabecera de la lista ligada
    int opcion;

    for (;;) {
        printf("\n--- ADMINISTRADOR DE NNA's ---");
        printf("\n1-. Agregar NNA\n2-. Listar Todo\n3-. Buscar por Login\n4-. Modificar Registro\n5-. Salir\nOpcion: ");
        
        // Validación de entrada para evitar bucles infinitos por caracteres no numéricos
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n'); // Limpiar buffer
            continue;
        }

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

/**
 * Verifica si un login o correo ya existen en la lista.
 * @param omitir Puntero a un nodo que no debe compararse (útil al modificar).
 * @return 1 si es duplicado, 0 si está disponible.
 */
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

/**
 * Recorre la lista y muestra todos los registros almacenados.
 */
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

/**
 * Busca un registro específico mediante el campo único 'login'.
 */
int buscarPorLogin(struct NNA *inicio) {
    char logB[20];
    printf("\nIngrese login a buscar: "); 
    scanf("%s", logB);
    
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
    printf("\n[ERROR]: No se encontro registro con ese login.\n");
    return 0;
}

/**
 * Crea un nuevo nodo, valida duplicidad e inserta al final de la lista.
 * @param inicio Puntero doble para modificar la dirección de la cabecera si es necesario.
 */
int agregarNNA(struct NNA **inicio) {
    char t_log[20], t_mail[50];
    printf("\n--- REGISTRO NUEVO ---");
    printf("\nLogin: "); scanf("%s", t_log);
    printf("Correo: "); scanf("%s", t_mail);

    // Validación de integridad de datos (Unicidad)
    if (esDuplicado(*inicio, t_log, t_mail, NULL)) {
        printf("\n[ERROR]: El login o correo ya estan registrados.\n");
        return 0;
    }

    // Reserva dinámica de memoria
    struct NNA *ptrnew = (struct NNA*) malloc(sizeof(struct NNA));
    if (ptrnew == NULL) return 0; // Error de memoria

    strcpy(ptrnew->login, t_log);
    strcpy(ptrnew->correo, t_mail);
    
    printf("Nombre: "); scanf("%s", ptrnew->nombre);
    printf("Apellido Paterno: "); scanf("%s", ptrnew->apellidop);
    printf("Apellido Materno: "); scanf("%s", ptrnew->apellidom);
    printf("Edad: "); scanf("%d", &ptrnew->edad);
    printf("Sexo (M/F): "); scanf(" %c", &ptrnew->sexo);
    printf("Numero: "); scanf("%s", ptrnew->numero);
    ptrnew->ptrsig = NULL;

    // Inserción en lista (si está vacía o al final)
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

/**
 * Localiza un nodo y permite editar un campo específico.
 */
int modificarNNA(struct NNA *inicio) {
    char logB[20];
    printf("\nLogin del NNA a modificar: "); scanf("%s", logB);
    struct NNA *aux = inicio;
    
    while (aux != NULL) {
        if (strcmp(aux->login, logB) == 0) {
            int op;
            printf("\n¿Que desea modificar?\n1.Nombre\n2.Apellidos\n3.Edad\n4.Sexo\n5.Login\n6.Tel\n7.Correo\nOpcion: ");
            scanf("%d", &op);
            
            char nuevo[50];
            // No pedimos "nuevo valor" en cadena si es edad (int) o sexo (char)
            if (op != 3 && op != 4) { printf("Nuevo valor: "); scanf("%s", nuevo); }

            switch(op) {
                case 1: strcpy(aux->nombre, nuevo); break;
                case 2: 
                    strcpy(aux->apellidop, nuevo); 
                    printf("Nuevo Materno: "); scanf("%s", aux->apellidom); 
                    break;
                case 3: printf("Nueva edad: "); scanf("%d", &aux->edad); break;
                case 4: printf("Nuevo sexo (M/F): "); scanf(" %c", &aux->sexo); break;
                case 5: 
                    // Al modificar login, validamos que el nuevo no exista en otros nodos
                    if (esDuplicado(inicio, nuevo, aux->correo, aux)) printf(" [ERROR]: Login ocupado.");
                    else strcpy(aux->login, nuevo); 
                    break;
                case 6: strcpy(aux->numero, nuevo); break;
                case 7: 
                    // Al modificar correo, validamos que el nuevo no exista en otros nodos
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
