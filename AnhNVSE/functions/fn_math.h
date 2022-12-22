#pragma once

#include <math.h>
#include <algohol/algTypes.h>
#include <Algohol/algMath.h>

DEFINE_COMMAND_PLUGIN(V3NormalizeAlt, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(V3CrossproductAlt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QMultQuatQuatAlt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QMultQuatVector3Alt, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(QNormalizeAlt, "", 0, 1, kParams_OneArray);
DEFINE_COMMAND_PLUGIN(QFromAxisAngleAlt, "", 0, 2, kParams_OneArray_OneFloat);
DEFINE_COMMAND_PLUGIN(QInterpolateAlt, "", 0, 4, kParams_TwoArrays_OneFloat_OneInt);
DEFINE_COMMAND_PLUGIN(V3Dotproduct, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(DegToRad, "Converts degrees to radians", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(RadToDeg, "Converts radians to degrees", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(GetAngleQuadrant, "Returns the quadrant of an angle (radian)", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(Sinh, "Hyperbolic sin of angle", 0, 1, kParams_OneFloat)
DEFINE_COMMAND_PLUGIN(Cosh, "Hyperbolic cos of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(Tanh, "Hyperbolic tan of angle", 0, 1, kParams_OneDouble)
DEFINE_COMMAND_PLUGIN(V3Lerp, "", 0, 3, kParams_TwoArrays_OneFloat)
DEFINE_COMMAND_PLUGIN(GenerateBezierPoint, "", 0, 4, kParams_ThreeArrays_OneFloat);
DEFINE_COMMAND_PLUGIN(V3Mult, "", 0, 2, kParams_TwoArrays);
DEFINE_COMMAND_PLUGIN(V3MultByScalar, "", 0, 2, kParams_OneArray_OneFloat);

Vector3 V3Lerp(Vector3 vecA, Vector3 vecB, float t) {
	vecB.x *= t;
	vecB.y *= t;
	vecB.z *= t;

	vecA.x *= (1.f - t);
	vecA.y *= (1.f - t);
	vecA.z *= (1.f - t);

	return vecA + vecB;
};

inline float VDotproduct(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//#if RUNTIME
bool Cmd_RadToDeg_Execute(COMMAND_ARGS) {
	float rad;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &rad)) 
		*result = (rad * 57.2957795131);
	
	return true;
}

bool Cmd_DegToRad_Execute(COMMAND_ARGS) {
	float deg;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &deg)) 
		*result = (deg * 0.0174532925);
	
	return true;
}

bool Cmd_GetAngleQuadrant_Execute(COMMAND_ARGS) {
	*result = 0;
	float angle;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &angle)) return true;

	int tempAngle = (int)ceil(angle);
	tempAngle %= 360;
	if (tempAngle < 0) tempAngle += 360;
	*result = (tempAngle / 90) % 4 + 1;
	
	return true;
}

bool Cmd_Sinh_Execute(COMMAND_ARGS) {
	float angle;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &angle)) 
		*result = sinh(angle);
	
	return true;
}

bool Cmd_Cosh_Execute(COMMAND_ARGS) {
	double angle;
	int inRad;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &angle, &inRad)) 
		*result = cosh(angle);
	return true;
}

bool Cmd_Tanh_Execute(COMMAND_ARGS) {
	double angle;
	int inRad;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &angle, &inRad)) 
		*result = tanh(angle);

	return true;
}

void Vector3FromNVSEArray(const UInt32& arrID, Vector3& v) {
	NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(arrID);
	UInt32 srcArrSize = g_arrInterface->GetArraySize(srcArr);

	if (!srcArr || (srcArrSize != 3)) {
		v.x = 0;
		v.y = 0;
		v.z = 0;
		return;
	}

	NVSEArrayElement* elements = new NVSEArrayElement[srcArrSize];
	g_arrInterface->GetElements(srcArr, elements, NULL);
	v.x = elements[0].Number();
	v.y = elements[1].Number();
	v.z = elements[2].Number();

	delete[] elements;
}

void QuatFromNVSEArray(const UInt32& arrID, Quat& q) {
	NVSEArrayVar* srcArr = g_arrInterface->LookupArrayByID(arrID);
	UInt32 srcArrSize = g_arrInterface->GetArraySize(srcArr);

	if (!srcArr || (srcArrSize != 4)) {
		q.x = 0;
		q.y = 0;
		q.z = 0;
		q.w = 0;
		return;
	}

	NVSEArrayElement* elements = new NVSEArrayElement[srcArrSize];
	g_arrInterface->GetElements(srcArr, elements, NULL);
	q.x = elements[0].Number();
	q.y = elements[1].Number();
	q.z = elements[2].Number();
	q.w = elements[3].Number();

	delete[] elements;
}

bool Cmd_V3NormalizeAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID)) return true;

	Vector3 v;
	Vector3FromNVSEArray(arrID, v);

	V3Normalize(v);
	ArrayElementL newElem[3] = { v.x, v.y, v.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);
	
	return true;
}

bool Cmd_V3CrossproductAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) return true;

	Vector3 v1, v2;
	Vector3FromNVSEArray(srcID1, v1);
	Vector3FromNVSEArray(srcID2, v2);

	Vector3 out = V3Crossproduct(v1, v2);
	ArrayElementL newElem[3] = { out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);
		
	return true;
}

bool Cmd_QMultQuatQuatAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) return true;

	Quat q1, q2;
	QuatFromNVSEArray(srcID1, q1);
	QuatFromNVSEArray(srcID2, q2);

	Quat out = q1 * q2;
	ArrayElementL newElem[4] = { out.w, out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_QMultQuatVector3Alt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) return true;

	Quat q; Vector3 v;

	QuatFromNVSEArray(srcID1, q);
	Vector3FromNVSEArray(srcID2, v);

	Vector3 out = q * v;
	ArrayElementL newElem[3] = { out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_QNormalizeAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcID)) return true;

	Quat q;
	QuatFromNVSEArray(srcID, q);

	q.normalize();
	ArrayElementL newElem[4] = { q.w, q.x, q.y, q.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_QFromAxisAngleAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID;
	float angle;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcID, &angle)) return true;

	Vector3 axis;
	Vector3FromNVSEArray(srcID, axis);

	Quat out = fromAxisAngle(axis, angle);
	ArrayElementL newElem[4] = { out.w, out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_QInterpolateAlt_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	float t;
	int slerpFlag;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2, &t, &slerpFlag)) return true;

	Quat q1, q2, out;
	QuatFromNVSEArray(srcID1, q1);
	QuatFromNVSEArray(srcID2, q2);

	out = (slerpFlag) ? slerp(q1, q2, t) : nlerp(q1, q2, t);

	ArrayElementL newElem[4] = { out.w, out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 4, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_V3Dotproduct_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 srcID1, srcID2;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &srcID1, &srcID2)) return true;

	Vector3 v1, v2;
	Vector3FromNVSEArray(srcID1, v1);
	Vector3FromNVSEArray(srcID2, v2);

	*result = VDotproduct(v1, v2);

	return true;
}

bool Cmd_GenerateBezierPoint_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID1, arrID2, arrID3;
	float t;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID1, &arrID2, &arrID3, &t)) return true;

	Vector3 v1, v2, v3, newVec;
	Vector3FromNVSEArray(arrID1, v1);
	Vector3FromNVSEArray(arrID2, v2);
	Vector3FromNVSEArray(arrID3, v3);

	newVec = V3Lerp((V3Lerp(v1, v2, t)), (V3Lerp(v2, v3, t)), t);
	ArrayElementL newElem[3] = { newVec.x, newVec.y, newVec.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_V3Lerp_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID1, arrID2;
	float t;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID1, &arrID2, &t)) return true;

	Vector3 v1, v2, out;
	Vector3FromNVSEArray(arrID1, v1);
	Vector3FromNVSEArray(arrID2, v2);

	out = V3Lerp(v1, v2, t);

	ArrayElementL newElem[3] = { out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_V3Mult_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID1, arrID2;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID1, &arrID2)) return true;

	Vector3 v1, v2, out;
	Vector3FromNVSEArray(arrID1, v1);
	Vector3FromNVSEArray(arrID2, v2);

	out = v1 * v2;
	ArrayElementL newElem[3] = { out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

bool Cmd_V3MultByScalar_Execute(COMMAND_ARGS) {
	*result = 0;
	UInt32 arrID;
	float t;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &arrID, &t)) return true;

	Vector3 v, out;
	Vector3FromNVSEArray(arrID, v);

	out = v * t;
	ArrayElementL newElem[3] = { out.x, out.y, out.z };
	NVSEArrayVar* newArr = g_arrInterface->CreateArray(newElem, 3, scriptObj);
	g_arrInterface->AssignCommandResult(newArr, result);

	return true;
}

//#endif 


