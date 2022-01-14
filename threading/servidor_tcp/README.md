# Servidor TCP (version con threads)

Este ejemplo muestra como se puede crear un servidor que puede atender a multiples clientes. El funcionamiento es muy simple y es simplemente para demostrar un ejemplo utilizando threads para un objetivo conciso.

Cada cliente conectado puede enviar datos, los cuales seran respondidos con su mismo contenido, solo que invertido. Esto es simple de ver conectandose con un cliente TCP y enviando datos imprimibles en pantalla.

El servidor estará escuchando en todas las interfaces y en particular, en el puerto 15001 por conexiones TCP. Para finalizar el programa, basta con enviar SIGINT al proceso (Ctrl+C). Asimismo, se informarán por la consola los distintos eventos que vayan ocurriendo.