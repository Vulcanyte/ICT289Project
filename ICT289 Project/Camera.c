#include <gl/freeglut.h>
#include <stdio.h>

#include "Camera.h"

void cameraInit(Camera* newCamera, float lPlane, float rPlane, float bPlane, float tPlane, float nPlane, float fPlane, float fov, float zoom, Camera_Type typeOfCamera)
{
    newCamera->leftPlane = lPlane;
    newCamera->rightPlane = rPlane;
    newCamera->topPlane = tPlane;
    newCamera->bottomPlane = bPlane;
    newCamera->nearPlane = nPlane;
    newCamera->farPlane = fPlane;
    newCamera->perspective_fov = fov;

    float width = (rPlane - lPlane);
    if(width <= 0)
        width = 1;

    newCamera->perspective_aspect = width * 1.0 / (tPlane - bPlane);

    cameraOrientate_f(newCamera, 1, 1, 1, 0, 0, -1);

    newCamera->rotation[0] = 0;
    newCamera->rotation[1] = 0;
    newCamera->rotation[2] = 0;

    newCamera->mouseOrigin[0] = -1;
    newCamera->mouseOrigin[1] = -1;
    newCamera->mouseOriginDelta[0] = 0.0f;
    newCamera->mouseOriginDelta[1] = 0.0f;
    newCamera->mouseCentre[0] = 0;
    newCamera->mouseCentre[1] = 0;

    if(zoom <= 1)
        newCamera->zoomLevel = 1;
    else
        newCamera->zoomLevel = zoom;

    newCamera->CamType = typeOfCamera;

    return;
}

void cameraSetType(Camera* cam, Camera_Type typeOfCamera)
{
    if(cam->CamType != typeOfCamera)
    {
        cam->CamType = typeOfCamera;

        printf("Camera set to: %d\n", cam->CamType);

        cameraProject(cam);
    }
    else
        printf("Camera is already type %d\n", cam->CamType);
}

void cameraOrientate_f(Camera* cam, float posX, float posY, float posZ, float lookX, float lookY, float lookZ)
{
    // Place the camera at the world origin.
    cam->position[0] = posX;
    cam->position[1] = posY;
    cam->position[2] = posZ;

    // Point the camera at an arbitrary point in space.
    cam->lookAt[0] = lookX;
    cam->lookAt[1] = lookY;
    cam->lookAt[2] = lookZ;
}

void cameraOrientate_p(Camera* cam, point3 pos, point3 look)
{
    cameraOrientate_f(cam, pos[0], pos[1], pos[2], look[0], look[1], look[2]);
}

void cameraProject(Camera* cam)
{
    // Ensure that the OpenGl Projection matrix is currently active.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    switch(cam->CamType)
    {
        case ORTHO_2D:
            gluOrtho2D(cam->leftPlane + cam->position[0], cam->rightPlane + cam->position[0], cam->bottomPlane + cam->position[1], cam->topPlane + cam->position[1]);
            break;

        case ORTHOGONAL:
            glOrtho(cam->leftPlane, cam->rightPlane, cam->bottomPlane, cam->topPlane, cam->nearPlane, cam->farPlane);
            break;

        case PERSPECTIVE:
            gluPerspective(cam->perspective_fov, cam->perspective_aspect, cam->nearPlane, cam->farPlane);
            break;

        case FRUSTUM:
            glFrustum(cam->leftPlane, cam->rightPlane, cam->bottomPlane, cam->topPlane, cam->nearPlane, cam->farPlane);
            break;

        default:
            printf("Error applying camera settings: Invalid camera type specified");
            break;
    }
}

void cameraUpdateFPS(Camera* cam)
{
    // Ensure that the OpenGl ModelView matrix is currently active.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(cam->CamType == ORTHOGONAL || cam->CamType == PERSPECTIVE)
    {
        point3 rot = {cam->lookAt[0] + cam->position[0], cam->lookAt[1] + cam->position[1], cam->lookAt[2] + cam->position[2]};
        gluLookAt(cam->position[0], cam->position[1], cam->position[2], rot[0], rot[1], rot[2], 0,1,0);
        return;
    }
}

void cameraUpdateTPS(Camera* cam)
{
    // Ensure that the OpenGl ModelView matrix is currently active.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(cam->CamType == ORTHOGONAL || cam->CamType == PERSPECTIVE)
    {
        point3 rot = {cam->position[0] - cam->lookAt[0] * 100, cam->position[1] - cam->lookAt[1] * 100, cam->position[2] - cam->lookAt[2] * 100};
        gluLookAt(rot[0], rot[1], rot[2], cam->position[0], cam->position[1], cam->position[2], 0,1,0);
        return;
    }
}

void cameraSetZoom(Camera* cam, float zoomLevel)
{
    if(zoomLevel >= 1.0f)
    {
        cam->zoomLevel = zoomLevel;

        // Automatically update the OpenGl projection matrix with the new settings.
        cameraProject(cam);
    }
}
