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

    sph->offset[0] = 0;
    sph->offset[1] = 0;
    sph->offset[2] = 0;

    sph->radius = r;

    sph->isColliding = 0;
}

void collisionInit_B(collider_AABB* box, float posX, float posY, float posZ, float sizeX, float sizeY, float sizeZ)
{
    box->position[0] = posX;
    box->position[1] = posY;
    box->position[2] = posZ;

    box->offset[0] = 0;
    box->offset[1] = 0;
    box->offset[2] = 0;

    box->sizeX = sizeX;
    box->sizeY = sizeY;
    box->sizeZ = sizeZ;

    box->isColliding = 0;
}

void collisionOffset_S(collider_Sphere* sph, float offsetX, float offsetY, float offsetZ)
{
    sph->offset[0] = offsetX;
    sph->offset[1] = offsetY;
    sph->offset[2] = offsetZ;
}

void collisionOffset_B(collider_AABB* box, float offsetX, float offsetY, float offsetZ)
{
    box->offset[0] = offsetX;
    box->offset[1] = offsetY;
    box->offset[2] = offsetZ;
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

void collisionFindNormalSS(collider_Sphere* coll_1, collider_Sphere* coll_2, point3 normal_1, point3 normal_2)
{
    // Find the un-normalised direction of the collision face of the other sphere.
    point3 dir = {  coll_1->position[0] - coll_2->position[0],
                    coll_1->position[1] - coll_2->position[1],
                    coll_1->position[2] - coll_2->position[2]};

    float dir_sq = dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2];

    // Normalise the un-normalised direction.
    normal_1[0] = -dir[0] / sqrt(dir_sq);
    normal_1[1] = -dir[1] / sqrt(dir_sq);
    normal_1[2] = -dir[2] / sqrt(dir_sq);

    normal_2[0] = -normal_1[0];
    normal_2[1] = -normal_1[1];
    normal_2[2] = -normal_1[2];

    if(debugMode)
    {
        glBegin(GL_LINES);
            glColor3f(0.5f, 0.5f, 0.5f);
            glVertex3fv(coll_1->position);
            glVertex3f(coll_1->position[0] + normal_1[0] * 100, coll_1->position[1] + normal_1[1] * 100, coll_1->position[2] + normal_1[2] * 100);
        glEnd();

        glBegin(GL_LINES);
            glColor3f(0, 0, 0);
            glVertex3fv(coll_2->position);
            glVertex3f(coll_2->position[0] + normal_2[0] * 100, coll_2->position[1] + normal_2[1] * 100, coll_2->position[2] + normal_2[2] * 100);
        glEnd();
    }
}

void collisionFindNormalsSB(collider_Sphere* coll_1, collider_AABB* coll_2, point3 normal_1, point3 normal_2)
{
    normal_1[1] = 0;
    normal_1[2] = 0;
    normal_1[3] = 0;

    normal_2[1] = 0;
    normal_2[2] = 0;
    normal_2[3] = 0;

    // The penetration depths for each set of faces. FORMAT: { sphere <-> right, sphere <-> left, sphere <-> bottom, sphere <-> top, sphere <-> back, sphere <-> front  }.
    float penetrations[6] = {0,0,0,0,0,0};

    // Calculate the penetration depths for each set of sides.
    penetrations[0] = abs((coll_1->position[0] - coll_1->radius) - (coll_2->position[0] + coll_2->sizeX * 0.5f));
    penetrations[1] = abs((coll_1->position[0] + coll_1->radius) - (coll_2->position[0] - coll_2->sizeX * 0.5f));
    penetrations[2] = abs((coll_1->position[0] + coll_1->radius) - (coll_2->position[0] - coll_2->sizeY * 0.5f));
    penetrations[3] = abs((coll_1->position[0] - coll_1->radius) - (coll_2->position[0] + coll_2->sizeY * 0.5f));
    penetrations[4] = abs((coll_1->position[0] + coll_1->radius) - (coll_2->position[0] - coll_2->sizeZ * 0.5f));
    penetrations[5] = abs((coll_1->position[0] - coll_1->radius) - (coll_2->position[0] + coll_2->sizeZ * 0.5f));

    // Find the smallest penetration depth.
    int i;
    float min = penetrations[0];
    int minIndex = 0;

    for(i = 1; i < 6; i++)
        if(penetrations[i] < min)
        {
            min = penetrations[i];
            minIndex = i;
        }

        // Use the index of the smallest penetration depth to dictate the normal of the colliding face.
    switch(minIndex)
    {
        case 0:
            normal_1[0] = 1;
            normal_2[0] = -1;
            break;

        case 1:
            normal_1[0] = -1;
            normal_2[0] = 1;
            break;

        case 2:
            normal_1[1] = -1;
            normal_2[1] = 1;
            break;

        case 3:
            normal_1[1] = 1;
            normal_2[1] = -1;
            break;

        case 4:
            normal_1[2] = -1;
            normal_2[2] = 1;
            break;

        case 5:
            normal_1[2] = 1;
            normal_2[2] = -1;
            break;

        default:
            // Do nothing...
            break;
    }

    if(debugMode)
    {
        glBegin(GL_LINES);
            glColor3f(0.5f, 0.5f, 0.5f);
            glVertex3fv(coll_1->position);
            glVertex3f(coll_1->position[0] + normal_1[0] * 100, coll_1->position[1] + normal_1[1] * 100, coll_1->position[2] + normal_1[2] * 100);
        glEnd();

        glBegin(GL_LINES);
            glColor3f(0, 0, 0);
            glVertex3fv(coll_2->position);
            glVertex3f(coll_2->position[0] + normal_2[0] * 100, coll_2->position[1] + normal_2[1] * 100, coll_2->position[2] + normal_2[2] * 100);
        glEnd();
    }
}

void collisionFindNormalBB(collider_AABB* coll_1, collider_AABB* coll_2, point3 normal_1, point3 normal_2)
{
    normal_1[1] = 0;
    normal_1[2] = 0;
    normal_1[3] = 0;

    normal_2[1] = 0;
    normal_2[2] = 0;
    normal_2[3] = 0;

    // The penetration depths for each set of faces. FORMAT: { left1 <-> Right2, right1 <-> Left2, top1 <-> Bottom2, bottom1 <-> Top2, front1 <-> Back2, back1 <-> Front2  }.
    float penetrations[6] = {0,0,0,0,0,0};

    // Calculate the penetration depths for each set of sides.
    penetrations[0] = abs((coll_1->position[0] - coll_1->sizeX * 0.5f) - (coll_2->position[0] + coll_2->sizeX * 0.5f));
    penetrations[1] = abs((coll_1->position[0] + coll_1->sizeX * 0.5f) - (coll_2->position[0] - coll_2->sizeX * 0.5f));
    penetrations[2] = abs((coll_1->position[0] + coll_1->sizeY * 0.5f) - (coll_2->position[0] - coll_2->sizeY * 0.5f));
    penetrations[3] = abs((coll_1->position[0] - coll_1->sizeY * 0.5f) - (coll_2->position[0] + coll_2->sizeY * 0.5f));
    penetrations[4] = abs((coll_1->position[0] + coll_1->sizeZ * 0.5f) - (coll_2->position[0] - coll_2->sizeZ * 0.5f));
    penetrations[5] = abs((coll_1->position[0] - coll_1->sizeZ * 0.5f) - (coll_2->position[0] + coll_2->sizeZ * 0.5f));

    // Find the smallest penetration depth.
    int i;
    float min = penetrations[0];
    int minIndex = 0;

    for(i = 1; i < 6; i++)
        if(penetrations[i] < min)
        {
            min = penetrations[i];
            minIndex = i;
        }

    // Use the index of the smallest penetration depth to dictate the normal of the colliding face.
    switch(minIndex)
    {
        case 0:
            normal_1[0] = 1;
            normal_2[0] = -1;
            break;

        case 1:
            normal_1[0] = -1;
            normal_2[0] = 1;
            break;

        case 2:
            normal_1[1] = -1;
            normal_2[1] = 1;
            break;

        case 3:
            normal_1[1] = 1;
            normal_2[1] = -1;
            break;

        case 4:
            normal_1[2] = -1;
            normal_2[2] = 1;
            break;

        case 5:
            normal_1[2] = 1;
            normal_2[2] = -1;
            break;

        default:
            // Do nothing...
            break;
    }

    if(debugMode)
    {
        glBegin(GL_LINES);
            glColor3f(0.5f, 0.5f, 0.5f);
            glVertex3fv(coll_1->position);
            glVertex3f(coll_1->position[0] + normal_1[0] * 100, coll_1->position[1] + normal_1[1] * 100, coll_1->position[2] + normal_1[2] * 100);
        glEnd();

        glBegin(GL_LINES);
            glColor3f(0, 0, 0);
            glVertex3fv(coll_2->position);
            glVertex3f(coll_2->position[0] + normal_2[0] * 100, coll_2->position[1] + normal_2[1] * 100, coll_2->position[2] + normal_2[2] * 100);
        glEnd();
    }
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
