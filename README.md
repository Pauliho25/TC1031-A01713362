# Partidos de Fútbol (Busqueda y Predicción)

**Paulo Marques Pinhal Ticó - A01713362**

Aplicación de consola en C++ para gestionar partidos de fútbol, con búsquedas y ordenamientos, ademas de crear una prediccion en base a los puntos y rendimiento de los equipos.

## Descripción

Este programa tiene como objetivo crear un sistema para partidos de Fútbol, en este sistema se incluye lo siguiente:

1.  Display de los partidos
2.  Busqueda
3.  Ordenamiento
4.  Analisis
5.  Prediccion

## Características

* Agregar y mostrar partidos
* Buscar por equipo o liga
* Ordenar por fecha o hora
* Menú interactivo para buscar y ordenar partidos.
* Menu para obtener información de un equipo
* Realizar predicción de un partido (en base al rendimiento y puntos de un equipo)

## Estructura

* `main.cpp`: Programa principal
* `Futbol.h`: Estructuras y clase de base de datos

---

## Análisis de Complejidad y Selección de Componentes

Esta sección detalla la selección y el análisis de complejidad temporal (Big O) de los componentes clave del programa.

### 1. Selección y Análisis de Algoritmos de Ordenamiento
* Se selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente (ej. `std::sort` para ordenamientos por fecha/hora).
* Se hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados.
* **Algoritmo:** `[Nombre del algoritmo, ej. std::sort]`
* **Complejidad Temporal:** $O(N \log N)$

### 2. Selección y Análisis de Estructuras de Datos
* Se selecciona una estructura de datos adecuada al problema y la usa correctamente (ej. `std::vector` para almacenar la lista principal de partidos).
* Se hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos.
* **Estructura:** `[Nombre de la estructura, ej. std::vector<Partido>]`
    * **Uso:** Almacenamiento principal de partidos.
    * **Inserción (Agregar partido):** $O(1)$ amortizado
    * **Búsqueda (lineal):** $O(N)$
* **Estructura:** `[Nombre de la estructura, ej. std::map<string, Equipo>]`
    * **Uso:** Búsqueda rápida de equipos por nombre para análisis.
    * **Inserción:** $O(\log N)$
    * **Búsqueda:** $O(\log N)$

### 3. Análisis de Otros Componentes y Complejidad Final
* Se hace un análisis de complejidad correcto y completo para todos los demás componentes del programa (funciones de búsqueda, análisis, predicción) y determina la complejidad final del programa.
* **Componente (Búsqueda por equipo/liga):**
    * **Complejidad:** $O(N)$ (si itera sobre el vector)
* **Componente (Análisis/Predicción):**
    * **Complejidad:** $O(N)$ (si itera sobre todos los partidos para calcular estadísticas)
* **Componente (Carga de datos):**
    * **Complejidad:** $O(N)$ (para $N$ partidos)

---

* **Complejidad Final del Programa:**
    * La complejidad final del programa está determinada por la operación más costosa, que es **el ordenamiento**.
    * **Complejidad Final:** $O(N \log N)$
