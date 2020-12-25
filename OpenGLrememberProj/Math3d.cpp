#include "Math3d.h"
#include <math.h>

// * ���������� ������� �������� * \\
 
// ����� ����� ������� ��������, ��� ����� ����� ��������� cross-a �� ����
// �������� ����� ��������. � �����, ��� ��, ��� ��� ����� ��� ��������� �����������
// ���� ������ ������������. � ����� ������, ������ - ��� ������ ����������� � ������.
// ������ ������� � ����� ������ �� �����. ��� ����� ������ ������ �����������.
// ����, ���� 2 ������� ������������, �� ����� ����� ������, ������� ���������������
// � ��������.
// ������, � ����������� �� ������� ���������� ������, ������� ����� ����������� �
// �����-�� �� ������ ��������. ��� ������� ������ ������, � ����� ������� ������������
// ������� - ������ ����������� ���.
// ������ �������� �������������� ������ � ����� �������. ������ �� ����� ������ ���
// ������������ �������, ������� �� �����. �����������, ���� � ��� ���� �����-������ 3�
// ������, ����� �� ��� ������������ ���������� ������� � ���������? ������� ���,
// ��� ������������.
//


/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� ������, ���������������� 2� ����������.
/////
/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vNormal;						// �������������� ������

	// ��� ���, ���� � ��� ���� 2 ������� (2 ������� ��������), � ��� ���� ���������.
	// cross ������� ������, ���������������� ���������, ������������ 2�� ���������.
	// ������� � �������� ������, �� ������ ��� �����������:

	// The X value for the vector is:  (V1.y * V2.z) - (V1.z * V2.y)
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

	// The Y value for the vector is:  (V1.z * V2.x) - (V1.x * V2.z)
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

	// The Z value for the vector is:  (V1.x * V2.y) - (V1.y * V2.x)
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vNormal;	 // ���������� ��������� (�����������, ���� ��������� ������� - �������)
}

/////////////////////////////////////// VECTOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� ������ ����� 2�� �������.
/////
/////////////////////////////////////// VECTOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector3 Vector(CVector3 vPoint1, CVector3 vPoint2)
{
	CVector3 vVector = { 0 };

	// ����� �������� ������ ����� 2 ������� (�����������), ����� ������� ������
	// ����� �� ������.

	vVector.x = vPoint1.x - vPoint2.x;
	vVector.y = vPoint1.y - vPoint2.y;
	vVector.z = vPoint1.z - vPoint2.z;

	// ������ ���������� ���������� ���������

	return vVector;
}

/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� �������� �������
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float Magnitude(CVector3 vNormal)
{
	return (float)sqrt((vNormal.x * vNormal.x) +
		(vNormal.y * vNormal.y) +
		(vNormal.z * vNormal.z));
}

/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� ��������������� ������ (� ������� 1)
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector3 Normalize(CVector3 vNormal)
{
	float magnitude = Magnitude(vNormal);

	vNormal.x /= magnitude;
	vNormal.y /= magnitude;
	vNormal.z /= magnitude;

	return vNormal;
}

/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� ������� ��������
/////
/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector3 Normal(CVector3 vTriangle[])
{
	CVector3 vVector1 = Vector(vTriangle[2], vTriangle[0]);
	CVector3 vVector2 = Vector(vTriangle[1], vTriangle[0]);

	// � ������� ���������� ��� ������� - �����������. �� �������� vVector1 � vVector2 - ���
	// �������. ������, ���� 2 ������� ������������, �� ����� �������� �� ��� cross().
	// (*���������*) �����: ������ �������� �� ������� ��� ������������, � ������ - �����
	// �������. ���� �� �������� �� �������, ������� ����� ��������� � ���������������
	// �������. � ����� ������ �� ������� ������� ������ �������� ������ �������.

	CVector3 vNormal = Cross(vVector1, vVector2);

	// ������, ���� ����������� �������, �������� ������� ��������� ����. ������ �
	// ������ ����������, ��� ����� ���� ����� �������. �� ������� � ������ 1, ���
	// ���������� ������������. ����� ������� ���, �� ����� ������� �� � ������.
	// �� � ��� ����� ������? �� ���������� ��� �������: magnitude = sqrt(x^2 + y^2 + z^2)

	vNormal = Normalize(vNormal);

	// ������ ������ "��������������� �������" =)
	// (*����������*) ���� �� ������ �������, ��� �������� ������������, ���������������
	// ���������� �����. �� �������, ��� ������ ������� �� ������������. � ����� ����������
	// ������ ������������ ��� �������. � ���������, �������, ������ ������ ������� 
	// (�������, ����� (0,0,0)), ���� �� � �����������, ��� ������ ����� ����� 1.

	return vNormal;
}

float PlaneDistance(CVector3 Normal, CVector3 Point)
{
	float distance = 0;	// ���������� ������ ��������� ��������� �� ������ ���������

	// ���������� ��������� ��������� ��� ���������� ��������� (Ax + By + Cz + D = 0).
	// ��� ����� ����� D. ������ ���������� �� ��������� ��������� ����� ���� (� IntersectedPlane()).
	// ��������: A B C - ��� �������� X Y Z ����� �������, � x y z - ��� x y z ����� �����.
	// D - ��������� �� ������ ���������. ����, ��� ����� ��������������� ���� ����������, ����� ����� D.
	distance = -((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));

	return distance;	// ��������� ���������
}


// � �������� ����� �� ������� ��� 2 ��������� ��� ������� � ��������� � ������� IntersectedPlane().
// ��� ��������, ����� �� ������������� �� ��� ���� � IntersectionPoint() � IntersectedPolygon().
// ����� ���� ����� �� ���� ������� ������ �������, ����� ��������, ����� �� �� ���������� ������
// ������� � ���������. � ����� ������� vTriangle �� "vPoly", ��� ��� ��� �� ����������� ������ ����
// �����������.
// ����, �������� ������� IntersectedPlane():

bool IntersectedPlane(CVector3 vPoly[], CVector3 vLine[], CVector3& vNormal, float& originDistance)
{
	float distance1 = 0, distance2 = 0;		// ��������� 2� ����� �����

	vNormal = Normal(vPoly);		// ������������ ������� ���������

	// ������ ��������� ��������� �� ������ ���������:
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	// ������� ��������� �� ������ � ������ �����:
	distance1 = ((vNormal.x * vLine[0].x) +					// Ax +
		(vNormal.y * vLine[0].y) +					// Bx +
		(vNormal.z * vLine[0].z)) + originDistance;	// Cz + D

	distance2 = ((vNormal.x * vLine[1].x) +					// Ax +
		(vNormal.y * vLine[1].y) +					// Bx +
		(vNormal.z * vLine[1].z)) + originDistance;	// Cz + D


// �������� �� �����������

	if (distance1 * distance2 >= 0)
		return false;

	return true;
}



// ��������� ������� ���������� "������� ��������� �����" (Dot product):
float Dot(CVector3 vVector1, CVector3 vVector2)
{
	// ��� ������� Dot product: V1.V2 = (V1.x * V2.x  +  V1.y * V2.y  +  V1.z * V2.z)
	// � �������������� ������������� ��� �������� ���: V1.V2 = ||V1|| ||V2|| cos(theta)
	// '.' ���������� DOT. || || - ��������, ��� ������ ������������. �� ���� �������� V1
	// �������� �� �������� V2 �������� �� ������� ����. �������� ����������, �� ����� ������
	// �����. ��� ������� ������������ �� ��������� ��������, ������� ����� ������� � ������
	// ������. � ���� ����� � � ������� �� ����� �������� ���� ����� ����� ���������.
	// ���� ������� �������������, dot product ������ ������� ���� ����� 2�� ���������.
	// ��� ��� ������? ��� ������, ��� �� ����� ���� ������������ �� ��� ����, � cos(angle).
	// �� � ��� ���� �� ����� �������� ��� ����? ����� �� ���������� ���������. 
	// ������ �� ���� ����� �������� � ������� AngleBetweenVectors(). ������� ����������
	// ������ ������������� dot product. ��� ��������� ���� ����� ����������������� ���������?
	// ���� �� ����������� ������, �� ����� �������� ��������� ||V1|| * ||V2||, ��������� ������
	// ����� cos(theta). ���� ������ ������������, ��� �������� - 1, ��� ��� ��������� 1*1*cos(theta),
	// ��� ������������, ��� ��� �� ����������� ��� ����� �������. ����, ��� ����� ������� 90?
	// ���� �� �������� �����������, �� ������, ��� ��� 0. � ����������, ��� ���� ��������� Dot()
	// ����� ����, ������� ���������������. �� ��� �� ������ - �������� ��������� ����, �������
	// ����� 90.

		 //    (V1.x * V2.x        +        V1.y * V2.y        +        V1.z * V2.z)
	return ((vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z));
}

////////////////////////////////////////////////////////////////////////////////
//
// ��������� ������� ���������� ���� ����� ���������
//
////////////////////////////////////////////////////////////////////////////////

double AngleBetweenVectors(CVector3 Vector1, CVector3 Vector2)
{
	// �������, ���� �� ��������, ��� Dot product ���������� ������� ���� ����� 
	// ����� ���������? ���������������, ��� ������� �������������. �, ���� � ��� ��� 
	// ���������������� �������, �� ������ ������ arcCos(DotProduct(A, B))
	// ��� ����� ��������� dot product �� �������� ���� ���������� ���� �� �����
	// ��������. ��� �������: arc cosine of (V . W / || V || * || W || )
	// ||V|| - ��� �������� V. ��� "�������" �������� dot product.
	// �� ���� �� ��� ������������� �������, �� ������ ������ � ���������.

	// �������� Dot �� ����� ��������
	float dotProduct = Dot(Vector1, Vector2);

	// �������� ��������� ������� ����� ��������
	float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2);


	// �������� ��������� �� (dotProduct / vectorsMagnitude), ��� ���� ���� � ��������.
	double angle = acos(dotProduct / vectorsMagnitude);


	// ������ ��������, ��� ���� �� -1.#IND0000000, ��� �������� "����������". acos() ������
	// ������� ���������� ���������� -1.#IND0000000. ���� �� �� ������� ���� ��������, ���������
	// �������� ����������� ����� ������ ���������� true, ����� �� ����� ���� ����������� ���.
	// � ������� ��� ���� ������ ������ ����� ������ ����� � ��� ���������� �������� ������ ;)
	// ������ ��� �������� ������������, ����� dot product � �������� ����� ���������� ��������.
	// �� ������ 0 ���� ��� ���������.

	if (_isnan(angle))
		return 0;

	// ������ ���� � ��������
	return(angle);
}



/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� ����� ����������� ����� � ���������
/////
/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector3 IntersectionPoint(CVector3 vNormal, CVector3 vLine[], double distance)
{
	CVector3 vPoint = { 0 }, vLineDir = { 0 };		// ���������� ��� ����� ����������� � ����������� �����
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;


	// ����� ������� ������� �����. ��� ����� ����� 3� �����, ����������� �� ���������.
	// ��� ���� ��� ���������� �����:

	// 1) ������� ��� ����� �������� ������ ����� �����, ����� ������������� ���, ����� ������ ���� 1
	vLineDir = Vector(vLine[1], vLine[0]);		// ������� ������ �����
	vLineDir = Normalize(vLineDir);			// ����������� ���


	// 2) ���������� ������� ��������� (��������� = Ax + By + Cz + D) ����� ����� ��������� �� ����� ��
	// ����� �� ���������. ������ ��������� �������������, �.�. ��� ����� ���� ����� �� ����� �����
	// � ���������. ��� �������� ������ ���������� ����� � ���������, ����� ����� ����� �����������.

	Numerator = -(vNormal.x * vLine[0].x +		// ���������� ������� ��������� � �������� � ������
		vNormal.y * vLine[0].y +
		vNormal.z * vLine[0].z + distance);

	// 3) ���� �� ������� Dot product ����� �������� ����� ����� � �������� ��������,
	// ��� ���� ��� ������� ���� ����� 2�� (�.�. ��� ��� ������������� - ������ 1).
	// ����� �� �������� Numerator �� ��� �������� ����� ����� ��������� ��������� �� ��������� �����.

	Denominator = Dot(vNormal, vLineDir);	// �������� Dot pruduct ����� ������ � ��������

	// ��� ��� �� ���������� �������, ����� ��������� �� ������ ������� �� ����. ���� �� ������� 0, 
	// ��� ������, ��� ������������ �����, �.�. ����� ��������� �� ��������� (������� ���������������
	// � ����� - (Normal.Vector = 0)).
	// � ���� ������ ������ ������ ����� ����� �� �����.

	if (Denominator == 0.0)		// ��������, �� ����� �� �� �� ����
		return vLine[0];	// ������ ����� ����� �����


	// �� ����� (��������� �� ����� �� ���������) �� (dot product), ����� �������� ���������
	// (dist), ������� ����� ��� ��� �������� �� ��������� ����� �����. ��� ����� �������� ��� ��������� (dist)
	// �� ������ ����� (�����������). ����� �� ��������� scalar �� �����, �� ���������� �����
	// ����� �������. ��� � ���� ��, ��� �� ������. �� ��������� �� ����� ��������� �����, ���������
	// �� �����, ����� � ��������� ����� ������� �����. ������� ���� �� ������ �������� Numerator,
	// ������� �������� ���������� �� ����� �� �����, � ����� ������ �������� ����� ����� ������� �����.
	// ��������� �� ��������� - ������� � ���� ����� �������� ���������. ��� ���� ����� ����� �����������
	// ��������, � �� ������������ � ��� �� ���������� ����� ������? ���������� �� ��������� ����, �� 
	// ���������� �� ����� ����������� ������� ����� � ���������� ����� ������. ���� �� ��������
	// ��������� �� dot product �� ������� ����� � ������� ���������, �� ������� ���������� ������.

	dist = Numerator / Denominator;

	// ������, ��� � ���������� ����, ����� ��������� �� ������, ����� ��������� ����� �����.
	// ��� ���������� ����� ����� ������� �� ����� ���������. ��� � ���� ������� ����
	// ��� ����� �����������.

	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;			// ������ ����� �����������.
}


/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������, ��������� �� ����� ������ ��������
/////
/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool InsidePolygon(CVector3 vIntersection, CVector3 Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.9999;		// ���. ��� �������� ������ ��������� �����
	double Angle = 0.0;				// �������������� ����
	CVector3 vA, vB;				// ��������� �������

	// ���� ��, ��� ����� ���������� ���������, ��� �� ������, ��� ��� ���������� ������� � 
	// ���� ���������. ��� ������� ��������� ����� ����������� �� ������� ����, ��������� ��
	// ��� ������ ��������. 
	// �� ����� ���� �� ���������� ������������� �����. �� ������� ������������ ������
	// �������� �� ����� �����������, ������� ����� � ������ ������� ��������. ����� ��� ���� 
	// ��������� ������������� ������������. � ���� ����� ����� ����� 360, �� �� ������! 
	// ���� �� �������� ������ 360, �� ������� ��������. 
	// ����� ����� ������, ��� ��� ��������, �������� �������� � ���������
	// �������������� �����������. ��������� ����� � ��� ������. ������ �� ���� ����� ��������� �����
	// � ������ ������� ������������. ����� ������� � ��� ���������� 3 ������������ ������ ��������, �����?
	// ������. �� �����, ��� ���� ������ ��� ���� ������������, �� ������� 180, �����?
	// ����� � �������� ��� �� � ������. 

	for (int i = 0; i < verticeCount; i++)		// �������� ������ �� ������ ������� � ���������� �� ����
	{
		vA = Vector(Poly[i], vIntersection);	// �������� ����� ����������� �� ������� �������

		// �������� ����� ����������� �� ��������� �������:
		vB = Vector(Poly[(i + 1) % verticeCount], vIntersection);

		// ������� ���� ����� 2�� ��������� � ���������� �� ���
		Angle += AngleBetweenVectors(vA, vB);
	}

	// ������ ���� ����� �����, ��� ����� ���������, ����� �� ��� 360. ��� ��� �� ����������
	// Dot product, �� �������� � ��������, ��� ��� ��������, ����� �� ���� 2*PI. PI �� �������� � 3dmath.h.
	// �� ��������, ��� �� ���������� MATH_FACTOR. �� ���������� ��� ��-�� ���������� � ��������� 
	// � ��������� ������. ������ ��������� �� ����� ����� 2*PI, ��� ��� ����� ������ ���������
	// �����������. � ����������� .9999, �� �� ������ �������� ��� �� �� �����������, ������� ��� 
	// �������.

	if (Angle >= (MATCH_FACTOR * (2.0 * PI)))	// ���� ���� >= 2PI (360 ��������)
		return true;				// ����� ��������� ������ ��������

	return false;		// ����� - �������
}


/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������, ������������ �� ����� � ���������
/////
/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool IntersectedPolygon(CVector3 vPoly[], CVector3 vLine[], int verticeCount)
{
	CVector3 vNormal = { 0 };
	float originDistance = 0;

	// ������� ���������, ���������� �� ���� ����� ���������. ���� ��� - �� �� �����
	// ����������, ������� �� ��������� ��� ���� �� ����������.
	// �������� � ������� ����� vNormal � originDistance, IntersectedPlane �������� �� ��� ���.

					   // ���������   // ���������
	if (!IntersectedPlane(vPoly, vLine, vNormal, originDistance))
		return false;

	// ������, ���� ������� � ���������, �� ����� ������������ �� ��� ���������� �����
	// �����������. ����� ����������� - ��� �����, ����������� �� ��������� � �� �����.
	// ����� ����� ����� �����������, �������� � ������� ������� ���������, ����� ����� � 
	// ��������� ��������� �� ���������.

	CVector3 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	// ������, ���� ����� �����������, ����� ���������, ����� �� ��� ������ ��������.
	// ����� ������� ���, �������:
	// (����� �����������, �������, ���������� ������ ��������).

	if (InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;			// ���� �����������! ������ true


	// ���� �� ����� ������, ����������� ���, ������ false

	return false;
}
