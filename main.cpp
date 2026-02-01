/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#define N 1000      // Tamaño de los arreglos
#define CHUNK 100   // Tamaño del bloque de iteraciones por hilo
#define MOSTRAR 10  // Cantidad de datos a imprimir para validación

void imprimeArreglo(float *d);

int main()
{
    std::cout << "Suma de Arreglos en Paralelo con OpenMP" << std::endl;

    // Declaración de variables y arreglos
    float a[N], b[N], c[N];
    int i;

    // Inicialización de la semilla para números aleatorios
    srand(time(NULL));

    // Llenado de los arreglos A y B con valores aleatorios (0-99)
    for (i = 0; i < N; i++)
    {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    int pedazos = CHUNK;

    // Configuración de la región paralela:
    // Se comparten los arreglos entre los hilos y se mantiene 'i' como privada.
    // Se utiliza schedule estático para dividir la carga de trabajo.
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)
    for (i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
    }

    // Impresión de los primeros resultados para verificar la suma correcta
    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo A: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo B: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo Resultado: " << std::endl;
    imprimeArreglo(c);

    return 0;
}

// Función auxiliar para mostrar elementos del arreglo
void imprimeArreglo(float *d)
{
    for (int x = 0; x < MOSTRAR; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}