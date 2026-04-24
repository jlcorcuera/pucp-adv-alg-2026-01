# Examen Parcial 2023-1: Criadero de Aves (Programación Dinámica)

## Enunciado del Problema

Un criador de aves (canarios y agapornis) instalará jaulas en **2 filas y `n` columnas** (una al lado de la otra).
Existe una importante restricción sobre los dueños de estas jaulas:
- **No se pueden colocar 2 agapornis uno al lado del otro**, ni de forma horizontal ni vertical, debido a su agresividad territorial.
- Sin embargo, sí toleran estar al lado de un canario.

El problema requiere averiguar: **¿Cuántas combinaciones diferentes de canarios y agapornis se pueden construir para $n$ columnas dadas estas restricciones?**

### Datos del Ejemplo

Para $n = 1$, las posibles combinaciones válidas en esa columna (de tamaño 2 altura x 1 de ancho) son 3:
1. Arriba: Canario (C) | Abajo: Canario (C)
2. Arriba: Agapornis (A) | Abajo: Canario (C)
3. Arriba: Canario (C) | Abajo: Agapornis (A)

*(Nota: Agapornis sobre Agapornis es inválido dado que se atacarían de forma vertical)*.

Para $n = 2$, el número de combinaciones dependerá de respetar que un Agapornis no quede "pegado" horizontalmente a un Agapornis de la columna anterior. **Por tal motivo con n=2 columnas se podrán formar 7 combinaciones diferentes:**

* *(Columna 1 $\rightarrow$ Columna 2)*
1. `(C/C)` junto a `(C/C)`
2. `(C/C)` junto a `(A/C)`
3. `(C/C)` junto a `(C/A)`
4. `(A/C)` junto a `(C/C)`
5. `(A/C)` junto a `(C/A)`
6. `(C/A)` junto a `(C/C)`
7. `(C/A)` junto a `(A/C)`

*(No son válidas opciones como `(A/C)` junto a `(A/C)` ni `(C/A)` junto a `(C/A)` porque provocarían que dos agapornis queden ubicados el uno al lado del otro horizontalmente).*

*Restricciones:* "No puede usar registros ni TADs, solo arreglos y matrices de enteros."

## Solución Propuesta (Programación Dinámica)

Este problema sigue un claro patrón de **Programación Dinámica de Máquina de Estados** (también conocido como *State Machine DP* u *Optimización de Perfiles*). En lugar de calcular cada posibilidad usando una búsqueda exhaustiva (cuyo tiempo sería exponencial), podemos aislar los casos de una sola columna y hacerlos "transicionar" a la siguiente.

El algoritmo implementado en `main.cpp` sigue los siguientes pasos:

### 1. Definición de los Estados

Dado que solo hay 2 filas por cada columna, en una columna cualquiera solo existen **3 variantes válidas (estados)**:
- **Estado 0:** Ambas jaulas albergan Canarios `(C / C)`.
- **Estado 1:** Agapornis arriba, Canario abajo `(A / C)`.
- **Estado 2:** Canario arriba, Agapornis abajo `(C / A)`.

### 2. Planteamiento de la Matriz `dp`

La función implementada utiliza internamente la matriz `dp[STATES][N_MAX + 1]` (donde `STATES = 3`).
> [!IMPORTANT]
> **¿Qué guardamos exactamente en `dp`?**  
> Al tratarse de un enfoque combinatorio, la posición `dp[estado][i]` almacena numéricamente: **"La cantidad total de combinaciones de jaulas que se pueden formar asumiendo una dimensión de `i` columnas, sabiendo certeramente que esta última columna tiene la forma final del `estado` seleccionado"**.

### 3. Caso Base (Inicialización)

Para la columna `i = 1`, la formación no depende de piezas históricas anteriores a su izquierda. Simplemente existe una sola forma de alcanzar cada estado de forma aislada.
```cpp
dp[0][1] = 1; // 1 combinación donde la columna 1 termina en C/C
dp[1][1] = 1; // 1 combinación donde la columna 1 termina en A/C
dp[2][1] = 1; // 1 combinación donde la columna 1 termina en C/A
```

### 4. Transición (Iterativamente para cada subsecuente columna)

Desde la columna `i = 2` hasta la meta `n`, para construir el resultado debemos basarnos en las decisiones de la etapa anterior de programación dinámica (`i - 1`):

- **Para alcanzar el Estado 0 (C/C):** Una columna de puros canarios puede unirse a cualquiera de las 3 formaciones de la columna izquierda previa sin problemas. Entonces es la suma del historial previo:
  `dp[0][i] = dp[0][i - 1] + dp[1][i - 1] + dp[2][i - 1];`

- **Para alcanzar el Estado 1 (A/C):** Esta columna tiene un Agapornis en la fila superior. Si la columna anterior también terminó en estado `(A/C)`, ambos agapornis quedarían adyacentes horizontalmente, lo cual viola la restricción del problema. Por lo tanto, se excluye el estado `(A/C)` previo y solo se suman las combinaciones provenientes de los otros dos estados compatibles:
  `dp[1][i] = dp[0][i - 1] + dp[2][i - 1];`

- **Para alcanzar el Estado 2 (C/A):** Esta columna tiene un Agapornis en la fila inferior. Si la columna anterior también terminó en estado `(C/A)`, ambos agapornis quedarían adyacentes horizontalmente, lo cual viola la restricción del problema. Por lo tanto, se excluye el estado `(C/A)` previo y solo se suman las combinaciones provenientes de los otros dos estados compatibles:
  `dp[2][i] = dp[0][i - 1] + dp[1][i - 1];`

### 5. Respuesta Final

Al terminar nuestro bucle hasta llegar a $n$, abarcaremos el total sumando la cantidad de combinaciones obtenidas desde los 3 perfiles sobre nuestra última columna evaluada:
`total = dp[0][n] + dp[1][n] + dp[2][n]`

Con esta aproximación, podemos solucionar el problema garantizando recursos exactos a través de complejidad iterativa lineal **O(N)**.
