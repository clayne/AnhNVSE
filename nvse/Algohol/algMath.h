#include "algTypes.h"


void V3Normalize(Vector3& v)
{
	float len = v.Magnitude();
	if (len > 0.0f)
		len = 1.0f / len;
	else
		len = 0.0f;
	v.x *= len;
	v.y *= len;
	v.z *= len;
}

Vector3 V3Crossproduct(Vector3 va, Vector3 vb)
{
	Vector3 out;
	out.x = vb.y * va.z - vb.z * va.y;
	out.y = vb.z * va.x - vb.x * va.z;
	out.z = vb.x * va.y - vb.y * va.x;
	return out;
}

float QDotproduct(Quat q1, Quat q2)
{
	return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

Quat fromEuler( Euler e, int flag );
Quat fromAxisAngle(Vector3 axis, float angle)
{
	V3Normalize(axis);
	angle /= 2 * 57.2957795131;
	float s = sinf(angle);
	return Quat(cosf(angle),
		axis.x * s,
		axis.y * s,
		axis.z * s);
}
Quat nlerp(Quat q1, Quat q2, float t)
{
	float cosHalfTheta = QDotproduct(q1, q2);
	if (cosHalfTheta < 0)
	{
		q1.w = -q1.w;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
	}

	Quat out = q1 + (q2 - q1) * t;
	out.normalize();
	return out;
}

Quat slerp(Quat q1, Quat q2, float t)
{
	q1.normalize();
	q2.normalize();
	float cosHalfTheta = QDotproduct(q1, q2);

	if (fabs(cosHalfTheta) >= 1.0f)
		return q1;

	if (cosHalfTheta < 0)
	{
		q1.w = -q1.w;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
	}

	float halfTheta = acosf(cosHalfTheta);
	float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);

	if (fabs(sinHalfTheta) < 0.001f)
		return q1 * 0.5f + q2 * 0.5f;

	float ratioA = sinf((1.0f - t) * halfTheta) / sinHalfTheta;
	float ratioB = sinf(t * halfTheta) / sinHalfTheta;
	return q1 * ratioA + q2 * ratioB;
}

Euler fromQuat( Quat q, int flag );