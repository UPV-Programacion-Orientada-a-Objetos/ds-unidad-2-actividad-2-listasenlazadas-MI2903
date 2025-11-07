/**
 * Emisor de protocolo PRT-7 para Arduino
 * Envia tramas de tipo LOAD y MAP por el puerto serial en bucle
 */

void setup()
{
    // Inicializar comunicacion serial a 9600 baudios
    Serial.begin(9600);
    delay(2000); // Esperar a que se establezca la conexion
}

void loop()
{
    // Mensaje: "HOLA MUNDO"
    Serial.println("L,H");
    delay(1000);

    Serial.println("L,O");
    delay(1000);

    Serial.println("L,L");
    delay(1000);

    Serial.println("L,A");
    delay(1000);

    Serial.println("L, "); // Espacio
    delay(1000);

    Serial.println("M,2"); // Rotar +2
    delay(1000);

    Serial.println("L,K"); // M con rotacion +2
    delay(1000);

    Serial.println("L,S"); // U con rotacion +2
    delay(1000);

    Serial.println("L,L"); // N con rotacion +2
    delay(1000);

    Serial.println("L,B"); // D con rotacion +2
    delay(1000);

    Serial.println("L,M"); // O con rotacion +2
    delay(1000);

    Serial.println("M,-2"); // Regresar rotacion a 0 (PATRON DE FIN)
    delay(1000);

    // Pausa entre ciclos
    delay(2000);
}