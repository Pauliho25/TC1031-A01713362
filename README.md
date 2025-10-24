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

* Se selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente: **`std::sort`** (implementación eficiente, generalmente IntroSort) se utiliza para ordenar los partidos por fecha (`sortByDate`, `searchByTeam`, `searchByLeague`) y por hora (`sortByHour`).
* Se hace un análisis de complejidad correcto y completo para el algoritmo de ordenamiento usado.
* **Algoritmo:** `std::sort`
* **Complejidad Temporal:** $O(N \log N)$, donde $N$ es el número de partidos a ordenar.

### 2. Selección y Análisis de Estructuras de Datos

* Se selecciona una estructura de datos adecuada al problema y la usa correctamente: **`std::vector<Match>`** se usa dentro de la clase `SoccerDB` para almacenar la lista principal de partidos. Los resultados de búsqueda también se almacenan temporalmente en un `std::vector<Match>`.
* Se hace un análisis de complejidad correcto y completo de esta estructura y sus usos.
* **Estructura:** `std::vector<Match>` (en `SoccerDB`)
    * **Uso:** Almacenamiento principal de partidos.
    * **Inserción (`addMatch`):** $O(1)$ amortizado. Añadir un elemento al final de un vector es típicamente $O(1)$, pero puede ser $O(N)$ si el vector necesita redimensionarse.
    * **Acceso/Lectura (Iteración para mostrar/buscar):** $O(N)$. Se requiere recorrer todos los elementos.
    * **Búsqueda (lineal en `searchByTeam`/`searchByLeague`):** $O(N)$. Implica iterar sobre todos los partidos del vector original.

### 3. Análisis de Otros Componentes y Complejidad Final

* Se hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.
* **Componente (Carga de datos - `readMatchesFromCSV`):**
    * **Complejidad:** $O(N)$, donde $N$ es el número de partidos en el archivo CSV.
* **Componente (Búsqueda por equipo/liga - `searchByTeam`/`searchByLeague`):**
    * **Complejidad:** $O(N) + O(M \log M)$, donde $N$ es el total de partidos y $M$ es el número de resultados encontrados. $O(N)$ para la búsqueda lineal y $O(M \log M)$ para ordenar los resultados con `std::sort`. En el peor caso ($M=N$), es $O(N \log N)$.
* **Componente (Mostrar todos los partidos):**
    * **Complejidad:** $O(N)$, itera sobre el vector. 
* **Componente (Menú interactivo):**
    * **Complejidad:** Depende de la opción seleccionada. Las operaciones individuales tienen las complejidades mencionadas arriba. El bucle `while` se ejecuta hasta que el usuario elige salir. 
---

* **Complejidad Final del Programa:**
    * La complejidad final del programa está determinada por la operación más costosa computacionalmente en el peor de los casos, que es **el ordenamiento** (`std::sort`) aplicado a toda la lista de partidos o a los resultados de búsqueda (cuando $M \approx N$).
    * **Complejidad Final:** $O(N \log N)$
