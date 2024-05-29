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

Camera::Camera()
	: position(XMFLOAT3_ZERO), rotation(XMFLOAT3_ZERO)
	, positionVector(XMLoadFloat3(&position))
	, rotationVector(XMLoadFloat3(&rotation))
	, viewMatrix(XMMatrixIdentity())
	, rotationMatrix(XMMatrixIdentity())
{ }

void Camera::Initialize(XMVECTOR position, XMVECTOR rotation)
{
	SetPosition(position);
	SetRotation(rotation);
}

void Camera::Update()
{
	UpdateViewMatrix();
	UpdateRotationMatrix();
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

const XMMATRIX Camera::GetViewMatrix() const
{
	return viewMatrix;
}

const XMMATRIX Camera::GetRotationMatrix() const
{
	return rotationMatrix;
}

void Camera::Move(XMVECTOR inputPos)
{
	positionVector = XMVectorAdd(positionVector, inputPos);
	XMStoreFloat3(&position, positionVector);
	UpdateViewMatrix();
}

void Camera::Move(XMFLOAT3 inputPos)
{
	position = position + inputPos;
	positionVector = XMLoadFloat3(&inputPos);
	UpdateViewMatrix();
}

void Camera::Rotate(XMVECTOR inputRot)
{
	rotationVector = XMVectorAdd(rotationVector, inputRot);
	XMStoreFloat3(&rotation, rotationVector);
	UpdateRotationMatrix();
}

void Camera::Rotate(XMFLOAT3 inputRot)
{
	rotation = rotation + inputRot;
	rotationVector = XMLoadFloat3(&inputRot);
	UpdateRotationMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR eye = positionVector;
	XMVECTOR at = eye + XMVector3Transform(DEFAULT_AT, rotationMatrix);
	XMVECTOR up = DEFAULT_UP;

	viewMatrix = XMMatrixLookAtLH(eye, at, up);
}

void Camera::UpdateRotationMatrix()
{
	float pitch = rotation.x;
	float yaw = rotation.y;
	float roll = rotation.z;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
}

