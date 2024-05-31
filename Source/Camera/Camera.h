#pragma once

/* MEMO
* XMLoadFloat() : XMFLOAT to XMVECTOR 
  XMStoreFloat() : XMVECTOR to XMFLOAT
*/

const XMFLOAT3 XMFLOAT3_ZERO= XMFLOAT3(0.0f, 0.0f, 0.0f);
const XMVECTOR XMVECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
const XMVECTOR DEFAULT_EYE = { 0.0f, 0.0f, 0.0f };
const XMVECTOR DEFAULT_AT = { 0.0f, 0.0f, 1.0f };
const XMVECTOR DEFAULT_UP = { 0.0f, 1.0f, 0.0f };

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

	const XMMATRIX GetRotationMatrix() const;
	const XMMATRIX GetViewMatrix() const;
	const XMMATRIX GetProjectionMatrix() const;

	// Input parameter��ŭ transform update
	void Move(XMVECTOR inputPos);
	void Move(XMFLOAT3 inputPos);
	void Rotate(XMVECTOR inputRot);
	void Rotate(XMFLOAT3 inputRot);

private:
	XMFLOAT3 position;
	XMFLOAT3 rotation; // use radian

	XMVECTOR positionVector;
	XMVECTOR rotationVector;

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