# protos-mediaTypes 

### Objetivo:
Desarrollar un programa que reciba por argumento de línea de comando un media-range (sección 5.3.2 Accept del RFC7231) y por entrada estándar un media-type (Sección 3.1.1.1 Media Type del RFC7231) por cada línea. El programa imprimirá en la salida estándar por cada media-type recibido los literales true, false, null según esté incluido por los media-range o la entrada esté mal formada.

### Forma de compilación:

`cd protos-mediaTypes`
`make all`
    
### Forma de ejecución:

`> ./match '<media-range>'`

### Finalización de la entrada estándar:

Enviar un EOF Signal desde el teclado. En Linux: Ctrl + D