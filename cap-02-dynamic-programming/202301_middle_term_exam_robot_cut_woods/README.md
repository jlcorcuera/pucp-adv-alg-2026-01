# Examen Parcial 2023-1: Robot Cortador de Madera (Programación Dinámica)

## Enunciado del Problema

Una empresa maderera ha comprado un robot aserrador encargado de cortar **N troncos de madera** de acuerdo con **M presentaciones**. Cada presentación está determinada por:
- Un **punto de inicio del corte** a `X` metros con respecto a la base.
- Un **punto final de corte** a `Y` metros con respecto a la base.
- Un **beneficio o ganancia** (en S/.).

El objetivo es hacer que el robot seleccione qué presentaciones debe cortar de un tronco de forma que se **maximice el beneficio o ganancia total** (sin importar el desperdicio).
- Las presentaciones cortadas en un mismo tronco **no pueden intersecarse**.
- No es posible unir residuos para formar una presentación.

### Datos del Ejemplo

Tenemos **N = 10** troncos y **M = 4** presentaciones, con la siguiente información:

| Presentación | Inicio (m) | Fin (m) | Beneficio (S/.) |
| :---: | :---: | :---: | :---: |
| 1 | 5 | 10 | 30 |
| 2 | 2 | 4 | 40 |
| 3 | 6 | 12 | 80 |
| 4 | 4 | 15 | 100 |

**Respuesta Teórica:**
Para un solo tronco, las presentaciones óptimas que no se intersecan son la **2** y la **4** (beneficio de 40 + 100 = 140).
Para los `N = 10` troncos, la ganancia máxima obtenida será de **S/. 1400**.

*Restricciones:* "No puede usar registros ni TADs, solo arreglos y matrices de enteros."

## Cómo aplicar Programación Dinámica

Dado que el objetivo es maximizar la ganancia seleccionando presentaciones que tienen puntos de inicio y final precisos (y que por lo tanto pueden superponerse bloqueándose mutuamente), una solución rudimentaria evaluaría exhaustivamente todas las combinaciones posibles de presentaciones. Probar para cada presentación si "la incluimos" o "la descartamos" genera la evaluación redundante de las mismas presentaciones muchísimas veces, aumentando el tiempo de resolución exponencialmente.

**La Programación Dinámica evita este reproceso aprovechando dos bases:**
- **Tabulación de Subproblemas (Memoria):** Si mientras iteramos almacenamos en un arreglo **la máxima ganancia que pudimos obtener al cortar el tronco luego de haber analizado la presentación $i$**, nunca más tendremos que volver a indagar o recalcular combinaciones sobre las presentaciones que ya revisamos en el pasado.
- **Subestructura Óptima:** La ganancia máxima global se puede construir matemáticamente a partir de soluciones óptimas más pequeñas. Si determinamos que debemos cortar la presentación actual, la ganancia ideal se formará sumando el beneficio de esa presentación elegida más la ganancia máxima que ya habíamos conseguido con la presentación compatible más cercana anterior (aquella cuyo punto final no se solapa con el punto inicial de la actual).

## Análisis del Algoritmo (Programación Dinámica)

Dado que el enunciado impone la restricción de trabajar únicamente con matrices primitivas (prohibiendo usar objetos o registros para agrupar datos), el algoritmo en `main.cpp` implementa la teoría anterior mediante los siguientes pasos iterativos:

### 1. Representación de Datos en Matriz
Dada la prohibición de uso de registros (structs/objetos), la información se almacena en una matriz bidimensional `data[ATTRIBUTES][N_PRESENTATIONS]`.
- **Fila 0:** Inicio de la presentación (en metros).
- **Fila 1:** Fin de la presentación (en metros).
- **Fila 2:** Beneficio de la presentación (en S/.).

### 2. Ordenamiento por "Punto Final"
Para que la Programación Dinámica funcione correctamente sobre intervalos, **se debe ordenar la matriz basándose en las coordenadas finales (Fila 1)**, de menor a mayor.
**Ordenar por la coordenada final asegura que, conforme iteramos, procesamos las presentaciones de izquierda a derecha en el tronco. Esto facilita buscar la presentación anterior compatible (aquella que no se solapa con la actual).**

### 3. Planteamiento del Arreglo DP
Se crea un arreglo `dp` de tamaño `N_PRESENTATIONS + 1`.

> [!IMPORTANT]
> **¿Qué guardamos exactamente en `dp`?**  
> La posición `dp[i]` almacena **la ganancia máxima posible (S/.) obtenida al seleccionar un subconjunto de presentaciones no solapantes**, considerando únicamente las primeras `i` presentaciones ordenadas. El arreglo no registra cuáles presentaciones fueron cortadas, solo el mejor beneficio acumulado hasta ese punto.

### 4. Inicialización / Caso Base

El caso base corresponde a la primera presentación después de ser ordenada (índice 0). Dado que es la primera en evaluarse y no existe ninguna presentación anterior con la cual pueda intersecarse, su máxima ganancia es directamente su propio beneficio:
```cpp
dp[0] = data[2][0];
```
Es fundamental inicializar este valor manualmente porque el bucle `for` principal arranca desde el índice 1 (`for (int i = 1; ...`), apoyándose siempre en resultados anteriores. Sin este caso base, el algoritmo no tendría un punto de partida válido.

### 5. Ecuación de Recurrencia (Transición)

Para cada presentación `i` iterada, el algoritmo debe tomar una decisión matemática fundamentada en las siguientes reglas lógicas:

1. **No Cortar esta presentación:** La ganancia será simplemente la ganancia máxima acumulada hasta la presentación anterior: `dp[i-1]`.

2. **Sí Cortar esta presentación:** Si decidimos cortar esta presentación, su beneficio (`data[2][i]`) se suma a la mejor ganancia que habíamos logrado con las presentaciones compatibles previas. Es decir, buscamos el índice `j` de la última presentación cuyo *punto final* sea menor o igual al *punto inicial* de la presentación actual (es decir, que no se solapen), y consultamos en el arreglo DP cuál fue el mejor beneficio acumulado hasta esa presentación compatible: `data[2][i] + dp[j]`.

El algoritmo selecciona el mayor valor entre estas dos opciones:
`dp[i] = max(dp[i-1], data[2][i] + dp[j])`

### 6. Multiplicar por N (Troncos)

El arreglo DP calcula el valor máximo óptimo asumiendo **un solo tronco**. Para nuestro ejemplo, el máximo es de S/. 140 (combinando las presentaciones 2 y 4).

Dado que todos los troncos son copias idénticas, el beneficio total se obtiene multiplicando el resultado de un tronco por `N`:
`ganancia_total = dp[mejor] * N` → 140 × 10 = **S/. 1400**.
