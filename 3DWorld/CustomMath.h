#pragma once
#include"stdafx.h"

inline float Vector3Length(D3DXVECTOR3 vector)
{
	auto fResult = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	return fResult;
}

inline void Vector3Normalize(D3DXVECTOR3* OutPut, D3DXVECTOR3 Input)
{
	float fLength = Vector3Length(Input);
	OutPut->x = Input.x / fLength;
	OutPut->y = Input.y / fLength;
	OutPut->z = Input.z / fLength;
}

inline float Vector3Dot(D3DXVECTOR3* vec1, D3DXVECTOR3* vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}