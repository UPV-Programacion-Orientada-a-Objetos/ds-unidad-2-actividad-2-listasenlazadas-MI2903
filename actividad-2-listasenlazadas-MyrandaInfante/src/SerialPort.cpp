/**
 * @file SerialPort.cpp
 * @brief Implementacion de la comunicacion serial para Windows
 */

#include "SerialPort.h"
#include <iostream>

SerialPort::SerialPort(const char *portName)
{
    conectado = false;

#ifdef _WIN32
    // Abrir puerto serial
    hSerial = CreateFileA(portName,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error: No se pudo abrir el puerto " << portName << std::endl;
        return;
    }

    // Configurar parametros del puerto
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        std::cout << "Error al obtener configuracion del puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        std::cout << "Error al configurar puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }

    // Configurar timeouts mas largos
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 100;
    timeouts.ReadTotalTimeoutConstant = 500;
    timeouts.ReadTotalTimeoutMultiplier = 100;

    if (!SetCommTimeouts(hSerial, &timeouts))
    {
        std::cout << "Error al configurar timeouts" << std::endl;
        CloseHandle(hSerial);
        return;
    }

    // Limpiar buffers
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);

    conectado = true;
    std::cout << "Conexion establecida en " << portName << std::endl;
#endif
}

SerialPort::~SerialPort()
{
#ifdef _WIN32
    if (conectado)
    {
        CloseHandle(hSerial);
    }
#endif
}

bool SerialPort::leerLinea(char *buffer, int bufferSize)
{
#ifdef _WIN32
    if (!conectado)
        return false;

    DWORD bytesLeidos;
    int indice = 0;
    bool finDeLinea = false;

    // Limpiar buffer
    for (int i = 0; i < bufferSize; i++)
    {
        buffer[i] = '\0';
    }

    // Leer caracter por caracter hasta encontrar fin de linea
    while (indice < bufferSize - 1 && !finDeLinea)
    {
        char c;
        DWORD leidos = 0;

        if (ReadFile(hSerial, &c, 1, &leidos, NULL))
        {
            if (leidos > 0)
            {
                // Ignorar retorno de carro
                if (c == '\r')
                {
                    continue;
                }

                // Fin de linea con salto de linea
                if (c == '\n')
                {
                    if (indice > 0)
                    {
                        finDeLinea = true;
                    }
                }
                else
                {
                    buffer[indice++] = c;
                }
            }
        }
        else
        {
            // Error de lectura
            break;
        }
    }

    buffer[indice] = '\0';
    return (indice > 0);
#else
    return false;
#endif
}

bool SerialPort::estaConectado()
{
    return conectado;
}