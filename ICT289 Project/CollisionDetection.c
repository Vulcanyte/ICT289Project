#include "CollisionDetection.h"
#include <math.h>

short debugMode = 0;

point3 collisionDebug_PositiveColor = {1,0,0};   // Color that a collider will be if it is colliding (Debug mode only).
point3 collisionDebug_NegativeColor = {0,1,0};   // Color that a collider will be if it is NOT colliding (Debug mode only).

void collisionInit_S(collider_Sphere* sph, float posX, float posY, float posZ, float r)
{
    sph->position[0] = posX;
    sph->position[1] = posY;
    sph->position[2] = posZ;

    sph->radius = r;

    sph->isColliding = 0;
}

void collisionInit_B(collider_AABB* box, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ)
{
    box->position[0] = posX;
    box->position[1] = posY;
    box->position[2] = posZ;

    box->sizeX = sizeX;
    box->sizeY = sizeY;
    box->sizeZ = sizeZ;

    box->isColliding = 0;
}

short collisionCollideSS(collider_Sphere* sph1, collider_Sphere* sph2)
{
    float magX = (sph1->position[0] - sph2->position[0]) * (sph1->position[0] - sph2->position[0]);
    float magY = (sph1->position[1] - sph2->position[1]) * (sph1->position[1] - sph2->position[1]);
    float magZ = (sph1->position[2] - sph2->position[2]) * (sph1->position[2] - sph2->position[2]);

    if(sqrt(magX + magY + magZ) <= (sph1->radius + sph2->radius))
    {
        sph1->isColliding = 1;
        sph2->isColliding = 1;
        return 1;   // TRUE.
    }
    else
        return 0;   // FALSE.
}

short collisionCollideSB(collider_Sphere* sph, collider_AABB* box)
{
    // Test X axis.
    if(sph->position[0] + sph->radius < box->position[0] - 0.5f * box->sizeX) return 0;   // FALSE.
    if(sph->position[0] - sph->radius > box->position[0] + 0.5f * box->sizeX) return 0;   // FALSE.

    // Test Y axis.
    if(sph->position[1] + sph->radius < box->position[1] - 0.5f * box->sizeY) return 0;   // FALSE.
    if(sph->position[1] - sph->radius > box->position[1] + 0.5f * box->sizeY) return 0;   // FALSE.

    // Test Z axis.
    if(sph->position[2] + sph->radius < box->position[2] - 0.5f * box->sizeZ) return 0;   // FALSE.
    if(sph->position[2] - sph->radius > box->position[2] + 0.5f * box->sizeZ) return 0;   // FALSE.

    sph->isColliding = 1;
    box->isColliding = 1;
    return 1;   // TRUE;
}

short collisionCollideBB(collider_AABB* box1, collider_AABB* box2)
{
    // Test X axis.
    if(box1->position[0] + 0.5f * box1->sizeX < box2->position[0] - 0.5f * box2->sizeX) return 0;   // FALSE.
    if(box1->position[0] - 0.5f * box1->sizeX > box2->position[0] + 0.5f * box2->sizeX) return 0;   // FALSE.

    if(box1->position[1] + 0.5f * box1->sizeY < box2->position[1] - 0.5f * box2->sizeY) return 0;   // FALSE.
    if(box1->position[1] - 0.5f * box1->sizeY > box2->position[1] + 0.5f * box2->sizeY) return 0;   // FALSE.

    // Test Z axis.
    if(box1->position[2] + 0.5f * box1->sizeZ < box2->position[2] - 0.5f * box2->sizeZ) return 0;   // FALSE.
    if(box1->position[2] - 0.5f * box1->sizeZ > box2->position[2] + 0.5f * box2->sizeZ) return 0;   // FALSE.

    box1->isColliding = 1;
    box2->isColliding = 1;
    return 1;   // TRUE.
}

void collisionDebug_DrawS(collider_Sphere* sph)
{
    // Only draw the collider if Debug Mode is on.
    if(debugMode)
    {
        glPushMatrix();

        glTranslatef(sph->position[0], sph->position[1], sph->position[2]);

        if(sph->isColliding)
            glColor3f(collisionDebug_PositiveColor[0], collisionDebug_PositiveColor[1], collisionDebug_PositiveColor[2]);
        else
            glColor3f(collisionDebug_NegativeColor[0], collisionDebug_NegativeColor[1], collisionDebug_NegativeColor[2]);

        glBegin(GL_LINE_LOOP);

            glutWireSphere(sph->radius, 10, 10);

        glEnd();

        glPopMatrix();
    }
}

void collisionDebug_DrawB(collider_AABB* box)
{
    // Only draw the collider if Debug Mode is on.
    if(debugMode)
    {
        point3 points[8] = {{0.5f * box->sizeX, 0.5f * box->sizeY, 0.5f * box->sizeZ},
                            {-0.5f * box->sizeX, 0.5f * box->sizeY, 0.5f * box->sizeZ},
                            {0.5f * box->sizeX, 0.5f * box->sizeY, -0.5f * box->sizeZ},
                            {-0.5f * box->sizeX, 0.5f * box->sizeY, -0.5f * box->sizeZ},
                            {0.5f * box->sizeX, -0.5f * box->sizeY, 0.5f * box->sizeZ},
                            {-0.5f * box->sizeX, -0.5f * box->sizeY, 0.5f * box->sizeZ},
                            {0.5f * box->sizeX, -0.5f * box->sizeY, -0.5f * box->sizeZ},
                            {-0.5f * box->sizeX, -0.5f * box->sizeY, -0.5f * box->sizeZ}  };

        glPushMatrix();

        glTranslatef(box->position[0], box->position[1], box->position[2]);

        if(box->isColliding)
            glColor3f(collisionDebug_PositiveColor[0], collisionDebug_PositiveColor[1], collisionDebug_PositiveColor[2]);
        else
            glColor3f(collisionDebug_NegativeColor[0], collisionDebug_NegativeColor[1], collisionDebug_NegativeColor[2]);

        // Draw top square.
        glBegin(GL_LINE_LOOP);

            glVertex3fv(points[0]);
            glVertex3fv(points[1]);
            glVertex3fv(points[3]);
            glVertex3fv(points[2]);

        glEnd();

        // Draw bottom square.
        glBegin(GL_LINE_LOOP);

            glVertex3fv(points[4]);
            glVertex3fv(points[5]);
            glVertex3fv(points[7]);
            glVertex3fv(points[6]);

        glEnd();

        // Connect squares with extra vertical lines.
        glBegin(GL_LINES);

            glVertex3fv(points[0]);
            glVertex3fv(points[4]);

            glVertex3fv(points[1]);
            glVertex3fv(points[5]);

            glVertex3fv(points[2]);
            glVertex3fv(points[6]);

            glVertex3fv(points[3]);
            glVertex3fv(points[7]);

        glEnd();

        glPopMatrix();
    }
}

void collisionDebug_Toggle(short newDebugMode)
{
    debugMode = newDebugMode;
}

short collisionDebug_FlagStatus()
{
    return debugMode;
}

void collisionDebug_PosColor(float r, float g, float b)
{
    collisionDebug_PositiveColor[0] = r;
    collisionDebug_PositiveColor[1] = g;
    collisionDebug_PositiveColor[2] = b;
}

void collisionDebug_NegColor(float r, float g, float b)
{
    collisionDebug_NegativeColor[0] = r;
    collisionDebug_NegativeColor[1] = g;
    collisionDebug_NegativeColor[2] = b;
}
