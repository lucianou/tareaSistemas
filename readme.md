# Menu personalizado en consola

## Descripción

Menú personalizado en consola que solicita parámetros de entrada necesarios, tanto de texto como numéricos, para realizar diversas operaciones. Ahora incluye funcionalidades avanzadas de búsqueda, almacenamiento en caché y análisis de performance

## Funcionalidades
1. Verificar que una frase es palíndromo, independiente de mayúsculas y minúsculas
2. Contar las vocales en una frase
3. Contar las letras en una frase
4. Realizar la sumatoria de los valores en un vector, y calcular su promedio.
5. Calcular f(x) = 5*x*x + 1/x
6. Realizar un conteo de palabras en archivos de una carpeta y generar un índice invertido.
7. Análisis de performance del conteo paralelo con múltiples threads.
8. Planificación de operaciones con un sistema de distribución de tareas.
9. Interfaz de Búsqueda: Buscar frases específicas en un sistema conectado con servicios de caché y motor de búsqueda.

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

## Funcionalidades Adicionales
1. Gestión de Usuarios y Roles
    Roles Disponibles: "Admin" y "Usuario Genérico".
    Solo los Administradores pueden acceder a las siguientes opciones adicionales:
    1. Ingresar Usuarios: Permite registrar nuevos usuarios con rol asignado.
    2. Listar Usuarios: Muestra todos los usuarios y su rol.
    3. Eliminar Usuarios: Elimina únicamente usuarios genéricos.
Los datos de usuarios se almacenan en un archivo de texto con el formato:
usuario;contraseña;rol.

2. Conteo de Palabras en Archivos
   1. Permite procesar archivos de una carpeta, contando la frecuencia de cada palabra.
   2. Los resultados se guardan en una carpeta de salida, generando un archivo por cada archivo de entrada con el formato:
        palabra1;cantidad  
        palabra2;cantidad  
   3. Opciones del Menú:
        Extensión de archivos a procesar.
        Path de la carpeta de entrada.
        Path de la carpeta de salida.
   4. Procesar archivos.

3. Conteo Paralelo con Threads
   1. Procesa archivos utilizando múltiples threads controlados por la variable de entorno CANTIDAD_THREAD.
   2. Limpia las palabras de "stop words" antes de realizar el conteo.
   3. Genera un índice invertido al finalizar el conteo, que incluye el ID del archivo y la cantidad de palabras encontradas.

4. Análisis de Performance
   1. Ejecuta el conteo paralelo con distintas configuraciones de threads, almacenando tiempos de ejecución en un archivo definido por DATOS.
   2. Genera gráficos de performance en formato .png utilizando un script externo en Python.

5. Planificador de Ejecución
   1. Distribuye operaciones básicas (suma, resta, multiplicación, división) entre múltiples "cores" simulados.
   2. Los resultados se almacenan en un archivo especificado por RESULTADOS.
   3. El sistema utiliza un archivo de entrada con el formato:
        operación;num1,num2.

6. Sistema de Búsqueda y Caché
    1. CACHE
        1. Implementa almacenamiento temporal de respuestas con una política de reemplazo.
        2. Responde consultas buscando en la caché o solicitando al MOTOR DE BÚSQUEDA.
        3. Configurado con la variable de entorno MEMORY_SIZE para limitar su tamaño.

    2. MOTOR DE BÚSQUEDA
        1. Carga un índice invertido definido en INVERTED_INDEX.
        2. Realiza búsquedas en base a las palabras recibidas.
        3. Responde con una lista ordenada de resultados, limitada por TOPK.
    3. BUSCADOR
        1. Proporciona una interfaz para buscar frases y recibir resultados procesados.
        2. Utiliza MAPA_ARCHIVOS para asignar nombres a los resultados.
        3. Al buscar "SALIR AHORA", envía este mensaje al CACHE y MOTOR DE BÚSQUEDA, cerrando todos los procesos relacionados.
   
## Variables de Entorno
Asegúrate de configurar las siguientes variables en el entorno antes de ejecutar el sistema, estas pueden ser modificadas a gusto:

1. Rutas y archivos:

    1. PATH_DATOS=assets/datos.txt
    2. EXTENSION_ARCHIVO=txt
    3. PATH_ENTRADA=assets/entrada
    4. PATH_SALIDA=assets/salida
    5. MAPA_ARCHIVOS=assets/map.txt
    6. INVERTED_INDEX=assets/index.INDEX
    7. STOP_WORD=assets/stopword.txt

2. Configuración del sistema:

    1. CANTIDAD_THREAD=3
    2. ARRAY_THREADS=1,2,4,8
    3. CANTIDAD_CORES=2
    4. MEMORY_SIZE=100
    5. TOPK=5
    6. PORT_CACHE=8080
    7. PORT_SEARCH=2020

3. Estadísticas y resultados:

    1. DATOS=assets/tiempos.txt
    2. RESULTADOS=assets/resultados.txt
    3. GRAFICO=assets/grafico.png
    4. PROCESOS=assets/procesos.txt

## Comunicación y Finalización
1. El BUSCADOR se comunica con el CACHE y MOTOR DE BÚSQUEDA usando sockets. 
2. Al recibir "SALIR AHORA", cierra los procesos externos y regresa al Menú Principal.

## Notas
El programa utiliza procesos externos para las operaciones avanzadas, asegurando modularidad y eficiencia.
Validaciones integradas aseguran consistencia en los datos de entrada y carpetas.