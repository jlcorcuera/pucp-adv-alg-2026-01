# Problema de la Mochila 0/1 (0/1 Knapsack Problem)

## Enunciado del Problema

Imagina que eres un explorador y has encontrado un cofre con $N$ objetos diferentes. Cada objeto posee dos atributos fundamentales:
- Un **peso** específico.
- Un **valor** (o ganancia) asociado.

Sin embargo, solo cuentas con una mochila que puede soportar una **capacidad máxima de peso ($W$)**. 
El objetivo es determinar inteligentemente qué objetos debes elegir para empacar de tal manera que se **maximice el valor total acumulado**, sin exceder jamás el límite de peso permitido por la mochila.

Esta versión se apellida "0/1", lo que significa que un objeto **no puede fraccionarse**: solo tienes la opción binaria de tomar el objeto íntegramente (1) o dejarlo atrás (0).

### Datos del Ejemplo

En la configuración codificada en el archivo base, se cuenta con una capacidad límite de $W = 5$ y un total de $N = 4$ objetos:

| Objeto | Peso ($w_i$) | Valor ($v_i$) |
| :---: | :---: | :---: |
| 1 | 2 | 12 |
| 2 | 1 | 10 |
| 3 | 3 | 20 |
| 4 | 2 | 15 |

*(Nota: En los arreglos de C++, estos listados corresponden a los índices 0 al 3)*

**Respuesta Teórica:**
La combinación óptima para lograr la mejor ganancia sin propasar la capacidad de $W=5$ es elegir los **Objetos 1, 2 y 4**. Al sumar sus pesos correspondientes ($2+1+2 = 5$) usamos eficientemente la bolsa a su máxima capacidad lógica y obtenemos un **Valor Total Máximo de 37** ($12+10+15$).

## Cómo aplicar Programación Dinámica

Dado que cada objeto se rige por un camino binario ("lo llevo" o "no lo llevo"), una solución rudimentaria implicaría evaluar exhaustivamente todas las $2^N$ combinaciones de objetos posibles. Aunque visualmente para 4 objetos parece poco, intentar este cálculo para un centenar de piezas volvería el procesamiento exponencialmente inmanejable por recursividad.

**La Programación Dinámica nos salva de la "fuerza bruta" apoyándose en:**
- **Tabulación de Subproblemas (Memoria):** En vez de intentar llenar la mochila grande directamente al azar o por mera intuición, empezamos calculando las respuestas de mochilas infinitamente pequeñas (capacidad 1, capacidad 2...) y las guardamos. Cuando nos toque analizar nuestro escenario grande, reciclamos toda esa iteración matemática previa.
- **Subestructura Óptima:** La mejor ganancia para una bolsa de peso grande $W$ puede construirse matemáticamente consultando las configuraciones ganadoras de bolsas más pequeñas que quedaron registradas.

## Análisis del Algoritmo (Programación Dinámica)

El algoritmo implementado en `main.cpp` lleva a la práctica este postulado lógico siguiendo los pasos descritos a continuación:

### 1. Planteamiento de la Matriz `dp`

Se define una matriz bidimensional `dp[N + 1][W + 1]`. 

> [!IMPORTANT]
> **¿Qué almacenamos exactamente en `dp`?**  
> La celda `dp[i][j]` almacena numéricamente **el valor máximo de ganancia (dinero) posible** asumiendo que, hipotéticamente, estuviéramos decidiendo únicamente usar los primeros `i` objetos de nuestro catálogo, y que nuestra mochila tuviera un tope máximo temporal de peso de `j`.

### 2. Inicialización / Caso Base

Antes de evaluar el peso de los objetos reales, la matriz se rellena explícitamente con `0`:
```cpp
dp[i][j] = 0;
```
Esto establece los casos base fundamentales del problema: Si estamos considerando `0` objetos, el valor a conseguir siempre será 0. A su vez, si el tamaño límite de la mochila actual es de `j = 0` kilos, por más miles de objetos valiosos que tengamos alrededor será imposible cargarlos, teniendo de valor 0 consecuente.

### 3. Iteración y Transición (Recurrencia)

Se declaran dos bucles de iteración continua y creciente: un bucle externo `i` que irá mirando los objetos nuevos del listado uno por uno, y un bucle interno `j` que va "probando" tamaños de mochila desde $1$ kilo hasta nuestra meta $W$.

Una vez situado ante un objeto con un peso `weight` y ganancia `value`, el algoritmo tomará una decisión matemática fundamentada en las siguientes reglas lógicas:

1. **Rechazo Trivial (El peso sobrepasa la mochila iterada temporal):** Si el peso del objeto `weight` supera la barrera `j`, físicamente no puede entrar en la mochila actual bajo ningún escenario. Ante esta imposibilidad, el algoritmo descarta el objeto y simplemente conserva y traslada el valor óptimo exacto que ya se había conseguido previamente sin incluir este objeto en la mochila.
   `dp[i][j] = dp[i-1][j];`

2. **Decisión Matemática (El objeto cabe en la mochila):** Dado que el objeto cabe, el algoritmo debe evaluar si incluirlo genera una ganancia mayor que la ya acumulada sin considerarlo. Para ello, se selecciona el mayor valor entre estas dos opciones:
   - Opción 1: **Ignorarlo**, quedándonos con las mejores combinaciones antiguas en esta misma capacidad: `dp[i-1][j]`.
   - Opción 2: **Empacarlo.** Si decidimos meter este objeto en la mochila, su `value` (valor del objeto actual) se suma a la mejor ganancia que habíamos logrado con la capacidad sobrante. Es decir, al incluir el objeto le "restamos" su peso a la capacidad actual de la mochila (`j - weight`), y consultamos en la tabla DP cuál fue el mejor valor que pudimos armar anteriormente con esa capacidad reducida: `value + dp[i-1][j - weight]`.
   
   La ecuación consolida esta decisión eligiendo siempre el mejor número:
   `dp[i][j] = max(dp[i-1][j], value + dp[i-1][j - weight]);`

### 4. Resolución de Salida

Tras los bucles procesando iterativamente desde limitaciones pequeñas hasta nuestro escenario de vida real (evaluar $N=4$ objetos asumiendo un peso máximo $W=5$), la mayor certidumbre reposará en el último cuadrante activo de nuestra tabulación. 

La máxima ganancia esperada termina documentada en `dp[N][W]`.
