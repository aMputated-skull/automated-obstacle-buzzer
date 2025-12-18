#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main()
{
    HANDLE hSerial;
    char buffer[128];
    DWORD bytesRead;
    int index = 0;

    hSerial = CreateFile(
        "\\\\.\\COM3",
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        printf("Error opening serial port\n");
        return 1;
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    SetCommState(hSerial, &dcb);

    printf("Listening...\n");

    while (1)
    {
        char c;
        ReadFile(hSerial, &c, 1, &bytesRead, NULL);

        if (bytesRead > 0)
        {
            if (c == '\n')
            {
                buffer[index] = '\0';
                printf("Received: %s\n", buffer);

                if (strcmp(buffer, "BEEP") == 0)
                {
                    PlaySound(TEXT("alarm.wav"), NULL, SND_FILENAME | SND_ASYNC);
                }

                index = 0; // reset buffer
            }
            else if (c != '\r')
            {
                buffer[index++] = c;
            }
        }
    }

    CloseHandle(hSerial);
    return 0;
}
