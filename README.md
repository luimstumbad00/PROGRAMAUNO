# PROGRAMAUNO
# Administrador de NNA (Niñas, Niños y Adolescentes)

Este es un sistema de gestión desarrollado en **Lenguaje C** diseñado para administrar un directorio de registros de menores de edad. El programa utiliza una estructura de **lista ligada simple** para el manejo dinámico de la memoria, permitiendo gestionar la información de manera eficiente durante la ejecución.

## 🚀 Funcionalidades

El sistema ofrece un menú interactivo con las siguientes opciones:

* **Registro de Usuarios:** Permite añadir nuevos registros capturando nombre completo, edad, sexo, teléfono, login y correo.
* **Validación de Seguridad:** El sistema impide el registro de logins o correos electrónicos duplicados para mantener la integridad de la base de datos.
* **Consulta General:** Listado detallado de todos los NNA almacenados en memoria.
* **Búsqueda por Login:** Localización rápida de registros específicos.
* **Modificación Dinámica:** Capacidad de editar cualquier campo de un registro existente de forma individual.

## 🛠️ Requisitos del Sistema

* **Compilador:** GCC (instalado por defecto en la mayoría de las distribuciones Linux).
* **Librerías:** Utiliza librerías estándar de C (`<stdio.h>`, `<stdlib.h>`, `<string.h>`).

## 🐧 Instrucciones para Linux

Si estás en Linux, puedes compilar y ejecutar el programa siguiendo estos pasos desde la terminal:

1. **Clonar el repositorio:**
   ```bash
   git clone [https://github.com/luimstumbad00/PROGRAMAUNO.git](https://github.com/luimstumbad00/PROGRAMAUNO.git)
   cd PROGRAMAUNO

2. **Compilar el código: (Asegúrate de respetar la mayúscula en el nombre del archivo)**

Bash
gcc Programa1.c -o Programa1

3. **Ejecutar el programa:**

Bash
./Programa1

Desarrollado por Luis Aguilar Torres