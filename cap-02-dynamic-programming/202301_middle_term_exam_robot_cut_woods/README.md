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

Dado que el objetivo es maximizar la ganancia de cortes que tienen puntos de inicio y final precisos (y que por lo tanto pueden superponerse bloqueándose mutuamente), una solución rudimentaria evaluaría exhaustivamente todas las selecciones posibles. Probar si para cada pieza "la incluimos" o "evaluamos otra" genera la evaluación redundante del mismo pedazo de madera muchísimas veces aumentando el tiempo de resolución exponencialmente.

**La Programación Dinámica evita este reproceso aprovechando dos bases:**
- **Tabulación de Subproblemas (Memoria):** Si mientras iteramos almacenamos en un arreglo **la máxima ganancia que pudimos obtener al cortar el tronco luego de haber analizado la presentación $i$**, nunca más tendremos que volver a indagar o recalcular combinaciones sobre las presentaciones que ya revisamos en el pasado.
- **Subestructura Óptima:** La ganancia máxima global se puede construir matemáticamente a partir de soluciones óptimas más pequeñas. Si determinamos que debemos cortar la presentación actual, el sub-conjunto de cortes ideal se formará sumando la ganancia de esa presentación elegida más la ganancia máxima que ya habíamos conseguido en el espacio previo compatible (la presentación antes de ella que no se solapa).

## Análisis del Algoritmo (Programación Dinámica)

Dado que el enunciado impone la estricta restricción de trabajar únicamente con matrices primitivas (prohibiendo usar objetos o registros para agrupar datos), el algoritmo en `main.cpp` implementa la teoría anterior convirtiendo el reto de optimización bidimensional en un proceso de decisiones continuas de "cortar" o "no cortar" mediante los siguientes pasos iterativos:

### 1. Representación de Datos en Matriz
Dada la prohibición de uso de registros (structs/objetos), la información se almacena en una matriz bidimensional `data[ATTRIBUTES][N_PRESENTATIONS]`.
- **Fila 0:** Inicio de la presentación.
- **Fila 1:** Fin de la presentación.
- **Fila 2:** Beneficio de la presentación.

### 2. Ordenamiento por "Punto Final"
Para que la Programación Dinámica funcione correctamente sobre intervalos, **se debe ordenar la matriz basándose en las coordenadas finales (Fila 1)**, de menor a mayor.
Ordenar por la coordenada final asegura que, conforme iteramos, procesamos los posibles intervalos de izquierda a derecha en nuestro tronco, siendo fácil buscar la presentación anterior compatible más óptima.

### 3. Planteamiento del Arreglo DP
Se crea un arreglo `dp` de tamaño `N_PRESENTATIONS + 1`.
**La posición `dp[i]` almacenará la ganancia máxima que se puede obtener utilizando un subconjunto óptimo dentro de las primeras `i` presentaciones ordenadas.**

> [!IMPORTANT]
> **¿Qué guardamos exactamente en `dp`?**  
> Este arreglo opera como la memoria táctica del algoritmo. En lugar de registrar el orden de qué presentaciones específicas hemos cortado, sus celdas documentan únicamente **el valor numérico (S/.) de la mayor ganancia confirmada y acumulada** hasta ese instante en el progreso de la iteración.

**Inicialización (`dp[0]`):**
El caso base del arreglo corresponde a la primera presentación después de ser ordenada (índice 0). Dado que es el primer elemento a evaluar y no existe ninguna presentación anterior con la cual pueda intersecarse temporalmente, su máxima ganancia es su propio beneficio directo. **Es fundamental inicializar este valor manualmente** porque servirá como el punto de partida que alimenta de información a la iteración del código principal, ya que el bucle `for` está diseñado para arrancar su lógica recién a partir del índice 1 (`for (int i = 1...`), apoyándose siempre en cálculos anteriores y evitando así desbordes por ínidices negativos. Por esto, se inicializa como:
`dp[0] = data[2][0];`

### 4. Ecuación de Recurrencia
Para cada presentación `i` iterada, el robot tiene dos opciones:
1. **No Cortar esa presentación**: La ganancia será simplemente la ganancia máxima acumulada hasta la presentación anterior (`dp[i-1]`).
2. **Sí Cortar esta presentación**: Sumamos la ganancia de la presentación actual (`data[2][i]`) **más** el máximo beneficio compatible previamente calculado (`dp[j]`). Aquí, `j` representa el índice de la presentación óptima previa cuyo *punto final* es menor o igual al *punto inicial* de nuestra presentación `i` (es decir, no se superponen).

Por lo que la ganancia de ese punto en `dp` será el máximo entre estas dos opciones:
`dp[i] = max(beneficio_anterior, beneficio_incluyendo_actual)`

### 5. Multiplicar por N (Troncos)
El arreglo DP y la lógica general encuentra el valor máximo óptimo asumiendo **1 solo tronco** (que, para nuestro ejemplo, es un máximo de 140 combinando las presentaciones 2 y 4).
El beneficio de todos los troncos en su conjunto, al ser copias exactas, basta con realizar la multiplicación del beneficio de uno por `N` (140 * 10 = S/. 1400).
