#pragma once

/* MEMO
* XMLoadFloat() : XMFLOAT to XMVECTOR 
  XMStoreFloat() : XMVECTOR to XMFLOAT
*/

const XMVECTOR DEFAULT_EYE = { 0.0f, 0.0f, 0.0f };
const XMVECTOR DEFAULT_AT = { 0.0f, 0.0f, 1.0f };
const XMVECTOR DEFAULT_UP = { 0.0f, 1.0f, 0.0f };

const float DEFAULT_MOVE_SPEED = 0.1f;
const float DEFAULT_ROTATE_SPEED = 0.1f;

class Camera final
{
public:
	Camera();
	~Camera() = default;

	void Initialize(XMVECTOR position = XMVECTOR_ZERO, XMVECTOR rotation = XMVECTOR_ZERO);

	void SetPosition(XMFLOAT3 position);
	void SetPosition(XMVECTOR position);
	void SetRotation(XMFLOAT3 rotation);
	void SetRotation(XMVECTOR rotation);
	void SetProjectionValues(float fovY, float aspect, float nearZ, float farZ);

	float GetMoveSpeed() const;
	void SetMoveSpeed(float value);
	float GetRotateSpeed() const;
	void SetRotateSpeed(float value);

	const XMMATRIX GetRotationMatrix() const;
	const XMMATRIX GetViewMatrix() const;
	const XMMATRIX GetProjectionMatrix() const;

	// Input parameter¸¸Å­ transform update
	void Move(XMVECTOR inputPos);
	void Move(XMFLOAT3 inputPos);
	void Rotate(XMVECTOR inputRot);
	void Rotate(XMFLOAT3 inputRot);

private:
	XMFLOAT3 position;
	XMFLOAT3 rotation; // use radian

	XMVECTOR positionVector;
	XMVECTOR rotationVector;

	float moveSpeed;
	float rotateSpeed;

	// world space parameters
	XMVECTOR eye;
	XMVECTOR at;
	XMVECTOR up;

	// camera space parameters
	float fovY;
	float aspect; 
	float nearZ;
	float farZ;

	XMMATRIX rotationMatrix;
	XMMATRIX viewMatrix; // camera space basis matrix
	XMMATRIX projectionMatrix; // clip space basis matrix

	void UpdateRotationMatrix();
	void UpdateViewMatrix(); 
	void UpdateProjectionMatrix();
};