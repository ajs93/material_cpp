# Servidor TCP (version con threads) en C

Este ejemplo muestra como se puede crear un servidor que puede atender a multiples clientes. El funcionamiento es muy simple y es simplemente para demostrar un ejemplo utilizando threads para un objetivo conciso.

Cada cliente conectado puede enviar datos, los cuales se intentaran parsear como un numero. En caso de ser parseados correctamente, se incrementara el contador del servidor en esa cantidad, y se respondera con el nuevo valor del contador.

El servidor estará escuchando en todas las interfaces y en particular, en el puerto 15001 por conexiones TCP. Para finalizar el programa, basta con enviar SIGINT al proceso (Ctrl+C). Asimismo, se informarán por la consola los distintos eventos que vayan ocurriendo.

## Funcionamiento basico

En el siguiente diagrama se boceta la idea principal de los componentes *servidor* y *cliente*:

![Funcionamiento basico](threading/servidor_tcp_c/diagrams/funcionamiento.png)