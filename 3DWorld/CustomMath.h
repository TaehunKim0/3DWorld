#pragma once
#include"stdafx.h"

inline float Vector3Length(D3DXVECTOR3 vector) //길이, 크기
{
	auto fResult = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	return fResult;
}

inline void Vector3Normalize(D3DXVECTOR3* OutPut, D3DXVECTOR3 Input) //정규화
{
	float fLength = Vector3Length(Input);
	OutPut->x = Input.x / fLength;
	OutPut->y = Input.y / fLength;
	OutPut->z = Input.z / fLength;
}

inline float Vector3Dot(D3DXVECTOR3* vec1, D3DXVECTOR3* vec2) //내적
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

inline void MatrixIdentity(D3DXMATRIX* mat)
{
	mat->m[0][0] = mat->m[1][1] = mat->m[2][2] = mat->m[3][3] = 1.0f; //대각선 방향은 1

	mat->m[0][1] = mat->m[0][2] = mat->m[0][3] = 0.0f;
	mat->m[1][0] = mat->m[1][2] = mat->m[1][3] = 0.0f;
	mat->m[2][0] = mat->m[2][1] = mat->m[2][3] = 0.0f;
	mat->m[3][0] = mat->m[3][1] = mat->m[3][2] = 0.0f;
}

inline void MatrixTranslation(D3DXMATRIX* mat, float x, float y, float z) //행렬의 이동
{
	mat->_41 += x;
	mat->_42 += y;
	mat->_43 += z;
}

inline void MatrixScaling(D3DXMATRIX* mat, float x, float y, float z)
{
	//스케일 값이 0 이 되면 확대 축소가 안됨
	mat->_11 = x;
	mat->_22 = y;
	mat->_33 = z;
}

inline void MatrixRotationX(D3DXMATRIX* mat, float AngleX/*라디안 값*/) //X축 회전
{
	mat->_22 = cos(AngleX);
	mat->_23 = sin(AngleX);
	mat->_32 = -sin(AngleX);
	mat->_33 = cos(AngleX);

}

inline void MatrixRotationY(D3DXMATRIX* mat, float AngleY/*라디안 값*/) //Y축 회전
{
	mat->_11 = cos(AngleY);
	mat->_13 = -sin(AngleY);
	mat->_31 = sin(AngleY);
	mat->_33 = cos(AngleY);
}

inline void MatrixRotationZ(D3DXMATRIX* mat, float AngleZ/*라디안 값*/) //Z축 회저
{
	mat->_11 = cos(AngleZ);
	mat->_12 = sin(AngleZ);
	mat->_21 = -sin(AngleZ);
	mat->_22 = cos(AngleZ);
}

inline void MatrixRotationYawPitchRoll(D3DXMATRIX* mat, float Yaw, float Pitch, float Roll)
{
	D3DXMATRIX X, Y, Z;

	MatrixIdentity(&Z);
	MatrixIdentity(&Y);
	MatrixIdentity(&X);

	MatrixRotationZ(&Z, Roll);
	MatrixRotationX(&X, Pitch);
	MatrixRotationY(&Y, Yaw);

	*mat = Z * X * Y;

}

//벡터의 내적 
/*
벡터의 곱셈 
결과 값은 스칼라 값 
*/

//벡터의 외적
/*
벡터의 곱셈의 다른 형태
결과 값은 두 벡터에 모두 수직한 벡터


*/

