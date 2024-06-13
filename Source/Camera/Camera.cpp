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
	: positionVector(XMVECTOR_ZERO)
	, rotationVector(XMVECTOR_ZERO)
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

void Camera::SetPosition(XMVECTOR position) // World position
{
	positionVector = position;
	UpdateViewMatrix();
}

void Camera::SetRotation(XMVECTOR rotation)
{
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

float Camera::GetMoveSpeed() const
{
	return moveSpeed;
}

void Camera::SetMoveSpeed(float value)
{
	moveSpeed = value;
}

float Camera::GetRotateSpeed() const
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
	positionVector = XMVectorAdd(positionVector, inputPos * moveSpeed);

	UpdateViewMatrix();
}

void Camera::Rotate(XMVECTOR inputRot)
{
	rotationVector = XMVectorAdd(rotationVector, inputRot * rotateSpeed);
	UpdateRotationMatrix();
}

void Camera::UpdateRotationMatrix()
{
	//float pitch = rotation.x; // (+up -down)
	//float yaw = rotation.y; // (+left -right)
	//float roll = rotation.z; // (+clockwise -counterClockwise)(Usually not used (except. FPS peeking))
	//
	//rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	rotationMatrix = XMMatrixRotationRollPitchYawFromVector(rotationVector);
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// View Matrix = SRT(matrix)
	eye = positionVector;
	at = eye + XMVector3Transform(DEFAULT_AT, rotationMatrix);
	up = XMVector3Transform(DEFAULT_UP, rotationMatrix);

	cout << "EYE : (" << eye.m128_f32[0] << "," << eye.m128_f32[1] << "," << eye.m128_f32[2]
		<< ") , AT : (" << at.m128_f32[0] << "," << at.m128_f32[1] << "," << at.m128_f32[2] <<")\n";
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

