#include "FileIO.h"

char currentWorkingDirectory[1024];
short cwdSet = 0;

void fileReadRAW_G(const char* filePath, unsigned char data[], int width, int height)
{
    FILE* rawFile = NULL;

    char dir_R[1024 + 128];
    _getcwd(currentWorkingDirectory, sizeof(currentWorkingDirectory));
    strcpy(dir_R, currentWorkingDirectory);
    strcat(dir_R, filePath);
    //printf("%s", dir_R);

    // Open the referenced file in BINARY mode.
    rawFile = fopen(dir_R, "rb");

    if(rawFile == NULL)
    {
        printf("Raw File not found.\n");
        return;
    }
    else
    {
        // Read the image data from the file.
        fread(data, sizeof(unsigned char), width * height * 3, rawFile);

        if(data == NULL)
        {
            printf("Error reading data.\n");
            return;
        }
    }

    // Close the file.
    fclose(rawFile);
}

void fileConvertRAWtoTXT(const char* rawFilePath, const char* txtFilePath, int width, int height)
{
    FILE* rawFile = NULL;
    FILE* txtFile = NULL;
    unsigned char data[width * height];

    char dir_R[1024 + 128];
    char dir_T[1024 + 128];
    _getcwd(currentWorkingDirectory, sizeof(currentWorkingDirectory));
    strcpy(dir_R, currentWorkingDirectory);
    strcpy(dir_T, currentWorkingDirectory);
    strcat(dir_R, rawFilePath);
    strcat(dir_T, txtFilePath);
    printf("%s", dir_R);
    printf("%s", dir_T);

    // Open the referenced file in BINARY mode.
    rawFile = fopen(dir_R, "rb");

    // Write the data to a txt file.
    txtFile = fopen(dir_T, "w");

    if(rawFile == NULL)
    {
        printf("Raw File not found.\n");
        return;
    }
    else
    {
        // Read the image data from the file.
        fread(data, sizeof(unsigned char), width * height, rawFile);

        if(data == NULL)
        {
            printf("Error reading data.\n");
            return;
        }
    }

    if(txtFile == NULL)
    {
        printf("Txt File not found\n");
        return;
    }
    else
    {
        int i = 0;
        for(i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        {
            if(i % height == 0)
            {
                fputs("\n", txtFile);
            }

            char str[3];
            snprintf(str, 5, " %d ", (int)data[i]);
            fputs(str, txtFile);
        }

        printf("Data written to TXT file.\n\n");
    }

    // Close the file.
    fclose(rawFile);
    fclose(txtFile);
}

const char* fileGetWorkingDirectory()
{
    if(cwdSet == 0)
    {
        _getcwd(currentWorkingDirectory, sizeof(currentWorkingDirectory));
        cwdSet = 1;
    }

    return currentWorkingDirectory;
}
