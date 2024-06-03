#include <stdafx.h>
#include "Camera.h"

XMFLOAT3 operator+(const XMFLOAT3 lhs, const XMFLOAT3 rhs)
{
	XMFLOAT3 ret(XMFLOAT3_ZERO);

	ret.x = lhs.x + rhs.x;
	ret.y = lhs.y + rhs.y;
	ret.z = lhs.z + rhs.z;

	return ret;
}

XMFLOAT3 operator*(const XMFLOAT3 lhs, const float rhs)
{
	XMFLOAT3 ret(XMFLOAT3_ZERO);

	ret.x = lhs.x * rhs;
	ret.y = lhs.y * rhs;
	ret.z = lhs.z * rhs;

	return ret;
}

Camera::Camera()
	: position(XMFLOAT3_ZERO), rotation(XMFLOAT3_ZERO)
	, positionVector(XMLoadFloat3(&position))
	, rotationVector(XMLoadFloat3(&rotation))
	, moveSpeed(DEFAULT_MOVE_SPEED)
	, rotateSpeed(DEFAULT_ROTATE_SPEED)
	, eye(DEFAULT_EYE)
	, at(DEFAULT_AT)
	, up(DEFAULT_UP)
	, fovY(XM_PIDIV2)
	, aspect(0.75f)
	, nearZ(0.1f)
	, farZ(1000.0f)
	, viewMatrix(XMMatrixIdentity())
	, rotationMatrix(XMMatrixIdentity())
	, projectionMatrix(XMMatrixIdentity())
{ }

void Camera::Initialize(XMVECTOR position, XMVECTOR rotation)
{
	SetPosition(position);
	SetRotation(rotation);
}

void Camera::SetPosition(XMFLOAT3 position)
{
	this->position = position;
	positionVector = XMLoadFloat3(&this->position);
	UpdateViewMatrix();
}

void Camera::SetPosition(XMVECTOR position) // World position
{
	XMStoreFloat3(&this->position, position);
	positionVector = position;
	UpdateViewMatrix();
}

void Camera::SetRotation(XMFLOAT3 rotation)
{
	this->rotation = rotation;
	rotationVector = XMLoadFloat3(&this->rotation);
	UpdateRotationMatrix();
}

void Camera::SetRotation(XMVECTOR rotation)
{
	XMStoreFloat3(&this->rotation, rotation);
	rotationVector = rotation;
	UpdateRotationMatrix();
}

void Camera::SetProjectionValues(float fovY, float aspect, float nearZ, float farZ)
{
	this->fovY = fovY;
	this->aspect = aspect;
	this->nearZ = nearZ;
	this->farZ = farZ;
	UpdateProjectionMatrix();
}

float Camera::GetMoveSpeed()
{
	return moveSpeed;
}

void Camera::SetMoveSpeed(float value)
{
	moveSpeed = value;
}

float Camera::GetRotateSpeed()
{
	return rotateSpeed;
}

void Camera::SetRotateSpeed(float value)
{
	rotateSpeed = value;
}

const XMMATRIX Camera::GetRotationMatrix() const
{
	return rotationMatrix;
}

const XMMATRIX Camera::GetViewMatrix() const
{
	return viewMatrix;
}

const XMMATRIX Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

void Camera::Move(XMVECTOR inputPos)
{
	positionVector = XMVectorAdd(positionVector, XMVector3Transform(inputPos * moveSpeed, rotationMatrix));
	XMStoreFloat3(&position, positionVector);

	//positionVector = XMVectorAdd(positionVector, inputPos * moveSpeed);
	UpdateViewMatrix();
}

void Camera::Move(XMFLOAT3 inputPos)
{
	positionVector = XMVectorAdd(positionVector, XMVector3Transform(XMLoadFloat3(&inputPos) * moveSpeed, rotationMatrix));
	XMStoreFloat3(&position, positionVector);

	//position = position + inputPos * moveSpeed;
	//positionVector = XMLoadFloat3(&position);
	UpdateViewMatrix();
}

void Camera::Rotate(XMVECTOR inputRot)
{
	rotationVector = XMVectorAdd(rotationVector, inputRot * rotateSpeed);
	XMStoreFloat3(&rotation, rotationVector);
	UpdateRotationMatrix();
}

void Camera::Rotate(XMFLOAT3 inputRot)
{
	//cout << inputRot.x << "," << inputRot.y << "," << inputRot.z << "\n";
	rotation = rotation + inputRot * rotateSpeed;
	rotationVector = XMLoadFloat3(&rotation);
	UpdateRotationMatrix();
}

void Camera::UpdateRotationMatrix()
{
	/*float pitch = rotation.x; (+up -down)
	float yaw = rotation.y; (+left -right)
	float roll = rotation.z; (+clockwise -counterClockwise)(Usually not used (except. FPS peeking))
	
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);*/
	rotationMatrix = XMMatrixRotationRollPitchYawFromVector(rotationVector);
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// View Matrix = SRT(matrix)
	eye = positionVector;
	at = eye + XMVector3Transform(DEFAULT_AT, rotationMatrix);
	up = XMVector3Transform(DEFAULT_UP, rotationMatrix);

	// Set Camera coordinates { camLookAt, camUp, camRight } 
	// Same as normalized { at-eye , up X camLookAt , camLookAt X camRight }
	// So the output viewMatrix is orthonormal
	viewMatrix = XMMatrixLookAtLH(eye, at, up);
}

void Camera::UpdateProjectionMatrix()
{
	// Same as (fovY / 360.0f) * XM_2PI;
	float fovYRadian = XMConvertToRadians(fovY);

	// Matrix used to convert view frustum into clip space
	projectionMatrix = XMMatrixPerspectiveFovLH(fovYRadian, aspect, nearZ, farZ);
}

