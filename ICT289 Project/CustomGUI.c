
#include "CustomGUI.h"

#include <memory.h>
#include <stdlib.h>

point3 textColor = {0.0f, 0.0f, 0.0f};

void GUInewLine(GUIline* newLine, float startX, float startY, float endX, float endY, float thickness, float colorR, float colorG, float colorB)
{
    // Set the origin point.
    newLine->startPoint[0] = startX;
    newLine->startPoint[1] = startY;

    // Set the destination point.
    newLine->endPoint[0] = endX;
    newLine->endPoint[1] = endY;

    // Set the thickness of the line.
    newLine->thickness = thickness;

    // Set the color of the line.
    newLine->color[0] = colorR;
    newLine->color[1] = colorG;
    newLine->color[2] = colorB;
}

void GUInewText(GUItext* newText, char* text, float posX, float posY, void* font)
{
    // Set text.
    newText->text = text;

    // Set position.
    newText->position[0] = posX;
    newText->position[1] = posY;
    newText->position[2] = 0;

    // Set font.
    newText->font = font;

    // Set value linkage parameters.
    newText->linkedParam = NULL;
    newText->paramType = 0;
}

void GUIlinkTextToParam(GUItext* textElement, void* param, LinkedParamType paramType)
{
    textElement->paramType = paramType;
    textElement->linkedParam = param;
}

void GUInewFrame(GUIframe* newFrame, int identifierTag, GUIframeEntry options[], int numOptions)
{
    newFrame->frameID = identifierTag;
    newFrame->frameElements = options;
    newFrame->numElements = numOptions;

    // By default, turn frame rendering ON.
    newFrame->renderON = 1;

    // By default, set the frame's offset to (0,0) window co-ordinates.
    newFrame->offset[0] = 0;
    newFrame->offset[1] = 0;
}

void GUIpositionFrame(GUIframe* frame, int offsetX, int offsetY)
{
    frame->offset[0] = offsetX;
    frame->offset[1] = offsetY;
}

void GUIenable2DRendering(GL_Window* activeWindow)
{
    // Only do the setup if the widow is NOT already set up. Prevents errors from multiple calls.
    if(activeWindow->renderGUI == 0)
    {
        glMatrixMode(GL_PROJECTION);

        glPushMatrix();

        glLoadIdentity();

        gluOrtho2D(0, activeWindow->dimensions[0], 0, activeWindow->dimensions[1]);

        glScalef(1, -1, 1);

        glTranslatef(0, -activeWindow->dimensions[1], 0);

        activeWindow->renderGUI = 1;

        glMatrixMode(GL_MODELVIEW);
    }
}

void GUIdisable2DRendering(GL_Window* activeWindow)
{
    // Only do the setup if the widow is ALREADY set up. Prevents errors from multiple calls.
    if(activeWindow->renderGUI == 1)
    {
        glMatrixMode(GL_PROJECTION);

        glPopMatrix();

        activeWindow->renderGUI = 0;

        glMatrixMode(GL_MODELVIEW);
    }
}

void GUIrenderText(GUItext* textElement)
{
    char* c;

    glPushMatrix();
    glLoadIdentity();

    glColor3fv(textColor);
    glRasterPos3fv(textElement->position);

    char* extendedText;
    char* temp;
    char extraText1[10];
    char extraText2[10];
    char extraText3[10];
    char extraText_final[34];

    if(textElement->paramType != 0)
    {
        switch(textElement->paramType)
        {
            case CHAR_param:
                extendedText = (char*)textElement->linkedParam;
                break;

            case STR_param:
                // Do nothing...
                break;

            case INT_param:

                snprintf(extraText_final, 10, "%d", *((int*)textElement->linkedParam));
                break;

            case FLOAT_param:

                snprintf(extraText_final, 10, "%.3f", *((float*)textElement->linkedParam));
                break;

            case POINT2_param:

                // Convert param numbers to strings.
                snprintf(extraText1, 10, "%.3f", *((float*)textElement->linkedParam));
                snprintf(extraText2, 10, "%.3f", *((float*)textElement->linkedParam +1));

                // Concatenate all strings together.
                strcpy(extraText_final, extraText1);
                strcat(extraText_final, ",");
                strcat(extraText_final, extraText2);
                break;

            case POINT3_param:

                // Convert param values to strings.
                snprintf(extraText1, 10, "%.3f", *((float*)textElement->linkedParam));
                snprintf(extraText2, 10, "%.3f", *((float*)textElement->linkedParam +1));
                snprintf(extraText3, 10, "%.3f", *((float*)textElement->linkedParam +2));

                // Concatenate all strings together.
                strcpy(extraText_final, extraText1);
                strcat(extraText_final, ", ");
                strcat(extraText_final, extraText2);
                strcat(extraText_final, ", ");
                strcat(extraText_final, extraText3);
                break;

            case TIME_param:

                // Convert param values to strings.
                if((int)*((float*)textElement->linkedParam) < 10)
                    snprintf(extraText1, 10, "0%d", (int)*((float*)textElement->linkedParam));
                else
                    snprintf(extraText1, 10, "%d", (int)*((float*)textElement->linkedParam));

                if((int)*((float*)textElement->linkedParam +1) < 10)
                    snprintf(extraText2, 10, "0%d", (int)*((float*)textElement->linkedParam +1));
                else
                    snprintf(extraText2, 10, "%d", (int)*((float*)textElement->linkedParam +1));

                if((int)*((float*)textElement->linkedParam +2) < 10)
                    snprintf(extraText3, 10, "0%d", (int)*((float*)textElement->linkedParam +2));
                else
                    snprintf(extraText3, 10, "%d", (int)*((float*)textElement->linkedParam +2));

                // Concatenate all strings together.
                strcpy(extraText_final, extraText1);
                strcat(extraText_final, ":");
                strcat(extraText_final, extraText2);
                strcat(extraText_final, ":");
                strcat(extraText_final, extraText3);
                break;

            default:
                printf("Error: Unknown param type specified: %d\n", textElement->paramType);
                break;
        }

        // Manually allocate enough memory to contain all of the above collected data in extendedText.
        if(textElement->paramType == CHAR_param)
        {
            for(c = textElement->text; *c != '\0'; c++)
                glutBitmapCharacter(textElement->font, *c);

            glutBitmapCharacter(textElement->font, *extendedText);
        }
        else
        {
            if(textElement->paramType == STR_param)
            {
                extendedText = (char*)malloc(1 + strlen(textElement->text) + strlen((char*)textElement->linkedParam));
                strcpy(extendedText, textElement->text);
                strcat(extendedText, (char*)textElement->linkedParam);
            }
            else
            {
                extendedText = (char*)malloc(1 + strlen(textElement->text) + strlen(extraText_final));
                strcpy(extendedText, textElement->text);
                strcat(extendedText, extraText_final);
            }

            for(c = extendedText; *c != '\0'; c++)
                glutBitmapCharacter(textElement->font, *c);

        }

        // Dump the excess memory to prevent memory leaks.
        free(extendedText);
    }
    else
    {
        // Draw initial text.
        for(c = textElement->text; *c != '\0'; c++)
            glutBitmapCharacter(textElement->font, *c);
    }

    glPopMatrix();
}

void GUIrenderLine(GUIline* newLine)
{
    glLineWidth(newLine->thickness);
    glColor3f(newLine->color[0], newLine->color[1], newLine->color[2]);

    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_LINES);
        glVertex2d(newLine->startPoint[0], newLine->startPoint[1]);
        glVertex2d(newLine->endPoint[0], newLine->endPoint[1]);
    glEnd();

    glPopMatrix();

    glLineWidth(5.0);
    glColor3fv(textColor);
}

void GUIrenderFrame(GUIframe* frame)
{
    if(frame->renderON == 1)
    {
        int i;

        for(i = 0; i < frame->numElements; i++)
        {
            switch(frame->frameElements[i].type)
            {
                case GUI_TEXT:

                    // Apply frame offset;
                    ((GUItext*)frame->frameElements[i].GUIelement)->position[0] += frame->offset[0];
                    ((GUItext*)frame->frameElements[i].GUIelement)->position[1] += frame->offset[1];

                    GUIrenderText((GUItext*)frame->frameElements[i].GUIelement);

                    // Undo frame offset.
                    ((GUItext*)frame->frameElements[i].GUIelement)->position[0] -= frame->offset[0];
                    ((GUItext*)frame->frameElements[i].GUIelement)->position[1] -= frame->offset[1];
                    break;

                case GUI_LINE:

                    // Apply frame offset;
                    ((GUIline*)frame->frameElements[i].GUIelement)->startPoint[0] += frame->offset[0];
                    ((GUIline*)frame->frameElements[i].GUIelement)->startPoint[1] += frame->offset[1];
                    ((GUIline*)frame->frameElements[i].GUIelement)->endPoint[0] += frame->offset[0];
                    ((GUIline*)frame->frameElements[i].GUIelement)->endPoint[1] += frame->offset[1];

                    GUIrenderLine((GUIline*)frame->frameElements[i].GUIelement);

                    // Undo frame offset.
                    ((GUIline*)frame->frameElements[i].GUIelement)->startPoint[0] -= frame->offset[0];
                    ((GUIline*)frame->frameElements[i].GUIelement)->startPoint[1] -= frame->offset[1];
                    ((GUIline*)frame->frameElements[i].GUIelement)->endPoint[0] -= frame->offset[0];
                    ((GUIline*)frame->frameElements[i].GUIelement)->endPoint[1] -= frame->offset[1];

                    break;

                default:
                    break;
            }
        }
    }
}

void GUIenableFrame(GUIframe* frame)
{
    frame->renderON = 1;
}

void GUIdisableFrame(GUIframe* frame)
{
    frame->renderON = 0;
}

void GUIsetTextColor(float r, float g, float b)
{
    textColor[0] = r;
    textColor[1] = g;
    textColor[2] = b;
}
