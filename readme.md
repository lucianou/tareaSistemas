# Menu personalizado en consola

## Descripción

Menu personalizado en consola que solicita parámetros de entrada necesarios, de texto y numéricos, para realizar las siguientes operaciones:
1. Verificar que una frase es palíndromo, independiente de mayúsculas y minúsculas
2. Contar las vocales en una frase
3. Contar las letras en una frase
4. Realizar la sumatoria de los valores en un vector, y calcular su promedio.
5. Calcular f(x) = 5*x*x + 1/x

## Compilación

1. Extraer el archivo comprimido en una carpeta
2. Abrir una consola en esa carpeta
3. Ejecutar el Makefile a través de la consola, con el comando make

## Ejecución
1. Desde la misma consola, ejecutar la línea de la forma 
./main -u parametro1 -p parametro2 -t parametro3 -v parametro4 -n parametro5
2. Habiendo realizado la ejecución correctamente, seguir los pasos indicados por el menú

## Parámetros
Cada parámetro ingresado en la línea de ejecución corresponde respectivamente a:
1. Nombre de usuario (-u) 
2. Contraseña del usuario (-p)
3. Frase que utilizará el programa (-t)
4. Vector que utilizará el programa, en el formato "1;2;3", donde cada elemento del vector está separado por ";" (-v)
5. El valor numérico que se usará en el programa para calcular f(x), puede ser entero o decimal (-n)

Los parámetros entregados en 1. y 2. deben coincidir con los de la variable de entorno presente en la carpeta (.env) para
que el programa se ejecute correctamente (USERNAME y PASSWORD respectivamente).