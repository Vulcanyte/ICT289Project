#include "FileIO.h"
#include <GL/freeglut.h>

char currentWorkingDirectory[1024];
short cwdSet = 0;

FILE* inf_handle;
int MAXROW = 200, MAXCOL = 320;
GLubyte image[200][320][3];

GLuint fileGetTexImage(char* name)
{
    char dir_R[1024 + 128];
    _getcwd(currentWorkingDirectory, sizeof(currentWorkingDirectory));
    strcpy(dir_R, currentWorkingDirectory);
    strcat(dir_R, name);
    //printf("%s", dir_R);

	GLuint tmpTex;
	int charin, r, c;
	//printf("Enter the name of the input file  : ");
   //gets(inf_name);

   /* try to open file for reading (r) in binary (b) mode */
   if  ((inf_handle = fopen(dir_R, "rb")) == NULL)  /* open failed */
    {
         puts("*** Can't open input file - please check file name typed!\n ");
         fprintf(stderr,"filename %s not found\n",name);
         charin = getchar();
         exit(1);   /* terminate execution */
    }

   /* reaching this line of code means file opened successfully,
   now read file contents into image array */
  	for ( r = 0;  r < MAXROW; r++ )
      	for ( c = 0;  c < MAXCOL; c++)  {
            if((charin=fgetc(inf_handle))==EOF)   /* read failed */
            {
              printf("***File reading failed! \n");
              charin = getchar();
              exit(1);    /* terminate execution */
            }
            image[r][c][0] = image[r][c][1] = image[r][c][2] = charin;
         }

   /* reaching this line of code means all of file read successfully */
   printf("\nImage input completed!\n");
   fclose(inf_handle);    /* close input file  */

   glGenTextures(1, &tmpTex);    // generate one texture name and return in tmpTex
   glBindTexture(GL_TEXTURE_2D, tmpTex); // bind tmpTex to 2D texture
   glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, MAXCOL, MAXROW, 0, GL_ALPHA, GL_UNSIGNED_BYTE, image);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   gluBuild2DMipmaps(GL_TEXTURE_2D,3, MAXCOL,MAXROW, GL_RGB, GL_UNSIGNED_BYTE,image);

   return tmpTex;
 }

unsigned int fileGenRawTexture(const char* filePath, int width, int height)
{
    FILE* rawFile = NULL;

    char dir_R[1024 + 128];
    _getcwd(currentWorkingDirectory, sizeof(currentWorkingDirectory));
    strcpy(dir_R, currentWorkingDirectory);
    strcat(dir_R, filePath);
    //printf("%s", dir_R);

    // Try to open the referenced file in BINARY mode.
    if(rawFile = fopen(dir_R, "rb") == NULL)
    {
        printf("Raw File not found.\n");
        return;
    }

    /**GLubyte data[width][height][3];
    int r = 0, c = 0, ch;

    for(r = 0; r < width; r++)
        for(c = 0; c < height; c++)
        {
            if(ch = fgetc(rawFile) == EOF)
            {
                printf("%d   ", ch);
                printf("Error reading filepath: %s\n", filePath);
                return;
            }

            //data[r][c][0] = data[r][c][1] = data[r][c][2] = ch;
            //fread(data, sizeof(unsigned char), width * height * 3, rawFile);
            //data[r][c][1] = data[r][c][2] = data[r][c][0];
            //fread(data[r][c][1], sizeof(unsigned char), 1, rawFile);
            //fread(data[r][c][2], sizeof(unsigned char), 1, rawFile);
        }

    // Read the image data from the file.
    //fread(data, sizeof(unsigned char), width * height * 3, rawFile);

    /*if(data == NULL)
    {
        printf("Error reading data.\n");
        return;
    }*

    // Close the file.
    fclose(rawFile);**/

    // Generate the texture from the file information.
    unsigned int texID;

    //texID = GenTexImage(filePath, rawFile, 320, 200);
    //glGenTextures(1, &texID);
    //glBindTexture(GL_TEXTURE_2D, texID);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, height, width, GL_RGB, GL_UNSIGNED_BYTE, data);

    return texID;
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
