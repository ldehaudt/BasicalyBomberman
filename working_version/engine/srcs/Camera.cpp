#include "Camera.hpp"
#include <math.h>

Camera::Camera(){
	first = true;
	xRot = 0;
	yRot = PI / 2;
	projectionMat = (float*)calloc(16, sizeof(float));
	yawMat = (float*)calloc(16, sizeof(float));
	pitchMat = (float*)calloc(16, sizeof(float));
	viewMat = (float*)calloc(16, sizeof(float));

	pitchMat[0] = 1;
	pitchMat[5] = 1;
	pitchMat[10] = 1;
	pitchMat[15] = 1;

	yawMat[0] = 1;
	yawMat[5] = 1;
	yawMat[10] = 1;
	yawMat[15] = 1;

	pos[0] = -5;
	pos[1] = 0;
	pos[2] = -5;

	viewMat[0] = 1;
	viewMat[5] = 1;
	viewMat[10] = 1;
	viewMat[15] = 1;
	projectionMat[0] = 1.0 / tan(FOV / 2 * PI / 180);
	projectionMat[5] = projectionMat[0];
	projectionMat[10] = -FAR / (FAR - NEAR);
	projectionMat[11] = -1;
	projectionMat[14] = -FAR * NEAR / (FAR - NEAR);
	
	reload();
	reloadCameraAngle();
}

void	Camera::reloadCameraAngle(){
	pitchMat[0] = cos(xRot);
	pitchMat[2] = -sin(xRot);
	pitchMat[8] = sin(xRot);
	pitchMat[10] = cos(xRot);

	yawMat[5] = cos(yRot);
	yawMat[6] = sin(yRot);
	yawMat[9] = -sin(yRot);
	yawMat[10] = cos(yRot);
}

void	Camera::lookHoriz(float amount){
	xRot += amount / 200.0f;
	if (xRot > PI)
		xRot = -PI + 0.0001;
	if (xRot < -PI)
		xRot = PI;
	reloadCameraAngle();
}

void	Camera::lookVert(float amount){
	yRot += amount / 200.0f;
	if (yRot > PI / 2)
		yRot =  PI / 2;
	if (yRot < -PI / 2)
		yRot = -PI / 2;
	reloadCameraAngle();
}

void	Camera::reload(){

	viewMat[12] = pos[0];
	viewMat[14] = pos[2];
}

float	Camera::getRotation(){
	return xRot;
}
