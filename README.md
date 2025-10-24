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

## Análisis de Complejidad

Esta sección detalla el análisis de complejidad temporal (Big O) de los componentes clave del programa.

### 1. Algoritmos de Ordenamiento
Se hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa (utilizados para ordenar por fecha y hora).

* **Algoritmo de ordenamiento:** `[Nombre del algoritmo, ej. Merge Sort, std::sort]`
* **Complejidad Temporal:** $O(...)$

### 2. Estructuras de Datos
Se hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa (ej. vectores para almacenar partidos, mapas para búsqueda rápida, etc.).

* **Estructura:** `[Nombre de la estructura, ej. std::vector<Partido>]`
    * **Uso:** Almacenamiento principal de partidos.
    * **Inserción (Agregar partido):** $O(...)$
    * **Búsqueda (lineal):** $O(...)$
* **Estructura:** `[Nombre de la estructura, ej. std::map<string, Equipo>]`
    * **Uso:** Búsqueda de equipos por nombre.
    * **Inserción:** $O(...)$
    * **Búsqueda:** $O(...)$

### 3. Otros Componentes y Complejidad Final
Se hace un análisis de complejidad correcto y completo para todos los demás componentes del programa (funciones de búsqueda, análisis, predicción) y se determina la complejidad final.

* **Componente (Búsqueda por equipo/liga):**
    * **Complejidad:** $O(...)$
* **Componente (Análisis/Predicción):**
    * **Complejidad:** $O(...)$
* **Componente (Menú interactivo / Carga de datos):**
    * **Complejidad:** $O(...)$

---

* **Complejidad Final del Programa:**
    * La complejidad final del programa está determinada por la operación más costosa, que es `[Indicar la operación, ej. el ordenamiento]`
    * **Complejidad Final:** $O(...)$
