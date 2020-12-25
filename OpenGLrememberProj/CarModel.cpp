#include "CarModel.h"
#include "MyOGL.h"
#include "MyShaders.h"
#include "CMatrix.h"
#include "CVector.h"
#include <ctime>


#define POP glPopMatrix()
#define PUSH glPushMatrix()

inline void CarModel::NoneKey_ivent()
{
	if (!OpenGL::isKeyPressed('D') && !OpenGL::isKeyPressed('A') && AngleZWheel < AngleZ) 
	{
		if (AngleZWheel + AngleSpeedReverse > AngleZ)
		{
			AngleZWheel = AngleZ;
		}
		else
		{
			AngleZWheel += AngleSpeedReverse;
		}
	}

	if (!OpenGL::isKeyPressed('A') && !OpenGL::isKeyPressed('D') && AngleZWheel > AngleZ) 
	{
		if (AngleZWheel - AngleSpeedReverse < AngleZ)
		{
			AngleZWheel = AngleZ;
		}
		else
		{
			AngleZWheel -= AngleSpeedReverse;
		}
	}

	if ((!OpenGL::isKeyPressed('W') || SelectedTransmissionNow == 0) && !OpenGL::isKeyPressed('S') && KeyWDuration > 0) 
	{
		if (KeyWDuration - TimeFrame < 0)
			KeyWDuration = 0;
		else
		{
			KeyWDuration -= TimeFrame;
			KeyW_ivent_slowDown();
		}
		flagAccelerationAfterDec = true;
	}

	if ((!OpenGL::isKeyPressed('S') || SelectedTransmissionNow == 0) && !OpenGL::isKeyPressed('W') && KeyWDuration < 0)
	{
		if (KeyWDuration + TimeFrame > 0)
			KeyWDuration = 0;
		else
		{
			KeyWDuration += TimeFrame;
			KeyW_ivent_slowDown();
		}
	}
}

inline void CarModel::D_ivent()
{
	if (OpenGL::isKeyPressed('D'))
	{
		if (AngleZWheel - AngleSpeed < -MaxAngleWheel + AngleZ)
		{
			AngleZWheel = -MaxAngleWheel + AngleZ;
		}
		else
		{
			AngleZWheel -= AngleSpeed;
		}
		if (KeyWDuration != 0 && SelectedTransmissionNow > 0)
		{	
			if(KeyWDuration <= 1) 
				AngleZ -= AngleSpeed * KeyWDuration / 10;
			else
				AngleZ -= AngleSpeed / 10;
		}	
		if (KeyWDuration != 0 && SelectedTransmissionNow < 0)
		{
			if (KeyWDuration >= -1) 
				AngleZ -= AngleSpeed * KeyWDuration / 10;
			else
				AngleZ += AngleSpeed / 10;
		}
	}
}

inline void CarModel::A_ivent()
{
	if (OpenGL::isKeyPressed('A')) 
	{
		if (AngleZWheel + AngleSpeed > MaxAngleWheel + AngleZ)
		{
			AngleZWheel = MaxAngleWheel + AngleZ;
		}
		else
		{
			AngleZWheel += AngleSpeed;
		}
		if (KeyWDuration != 0 && SelectedTransmissionNow > 0)
		{
			if (KeyWDuration <= 1) 
				AngleZ += AngleSpeed * KeyWDuration / 10;
			else
				AngleZ += AngleSpeed / 10;
		}
		if (KeyWDuration != 0 && SelectedTransmissionNow < 0)
		{
			if (KeyWDuration >= -1) 
				AngleZ += AngleSpeed * KeyWDuration / 10;
			else
				AngleZ -= AngleSpeed / 10;
		}
	}
}

inline void CarModel::S_ivent()
{
	if (OpenGL::isKeyPressed('S') && !OpenGL::isKeyPressed('W') && KeyWDuration <= 0)
	{
		if (!flagDeceleration)
		{
			flagDeceleration = true;
		}
		else
		{
			CarPoint.SetCoordX(CarPoint.X() + Speed * cos(AngleZ * PI / 180) * (KeyWDuration / 5));
			CarPoint.SetCoordY(CarPoint.Y() + Speed * sin(AngleZ * PI / 180) * (KeyWDuration / 5));

			if (SelectedTransmissionNow != 0)
				KeyWDuration -= TimeFrame * TurboCoef() * GearRatio();

			if (KeyWDuration < -5 && SelectedTransmissionNow != 0)
			{
				KeyWDuration = -5;
			}
			if (SelectedTransmissionNow > -1)
			{
				KeyWDuration = 0;
			}
		}
	}

	if (OpenGL::isKeyPressed('S') && !OpenGL::isKeyPressed('W') && KeyWDuration > 0) 
	{
		if (KeyWDuration - RateSlow < 0)
			KeyWDuration = 0;
		else
		{
			KeyWDuration -= RateSlow;
			KeyW_ivent_slowDown();
		}
	}
}

inline void CarModel::W_ivent()
{
	if (OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && KeyWDuration >= 0)
	{

		if (!flagAcceleration)
		{
			flagAcceleration = true;
		}
		else
		{
			CarPoint.SetCoordX(CarPoint.X() + Speed * cos(AngleZ * PI / 180) * (KeyWDuration / 5));
			CarPoint.SetCoordY(CarPoint.Y() + Speed * sin(AngleZ * PI / 180) * (KeyWDuration / 5));

			if (SelectedTransmissionNow != 0) 
				KeyWDuration += TimeFrame * TurboCoef() * GearRatio();

			if (KeyWDuration > 5 * SelectedTransmissionNow && SelectedTransmissionNow != 0)
			{
				KeyWDuration = 5 * SelectedTransmissionNow;
			}
			if (SelectedTransmissionNow == -1)
			{
				KeyWDuration = 0;
			}
		}
	}

	if (OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && KeyWDuration < 0) 
	{
		if (KeyWDuration + RateSlow > 0)
			KeyWDuration = 0;
		else
		{
			KeyWDuration += RateSlow;
			KeyW_ivent_slowDown();
		}
	}
}

inline void CarModel::KeyW_ivent_slowDown()
{
	CarPoint.SetCoordX(CarPoint.X() + Speed * cos(AngleZ * PI / 180) * (KeyWDuration / 5));
	CarPoint.SetCoordY(CarPoint.Y() + Speed * sin(AngleZ * PI / 180) * (KeyWDuration / 5));
}

void CarModel::DrawCar()
{
	PointKolesL.setCoords(CarPoint.X() + 2.7 * cos(AngleZ * PI / 180) - 1.37 * sin(AngleZ * PI / 180), CarPoint.Y() + 1.37 * cos(AngleZ * PI / 180) + 2.7 * sin(AngleZ * PI / 180), CarPoint.Z() + 0.62);
	PointKolesR.setCoords(CarPoint.X() + 2.7 * cos(AngleZ * PI / 180) + 1.37 * sin(AngleZ * PI / 180), CarPoint.Y() - 1.37 * cos(AngleZ * PI / 180) + 2.7 * sin(AngleZ * PI / 180), CarPoint.Z() + 0.62);
	PointKolesLBack.setCoords(CarPoint.X() - 1.9 * cos(AngleZ * PI / 180) - 1.37 * sin(AngleZ * PI / 180), CarPoint.Y() + 1.37 * cos(AngleZ * PI / 180) - 1.9 * sin(AngleZ * PI / 180), CarPoint.Z() + 0.62);
	PointKolesRBack.setCoords(CarPoint.X() - 1.9 * cos(AngleZ * PI / 180) + 1.37 * sin(AngleZ * PI / 180), CarPoint.Y() - 1.37 * cos(AngleZ * PI / 180) - 1.9 * sin(AngleZ * PI / 180), CarPoint.Z() + 0.62);

	glPushMatrix();
	carTex->bindTexture();
	
	glTranslated(CarPoint.X(), CarPoint.Y(), CarPoint.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZ, 0, 1, 0);

	Car->DrawObj();
	glPopMatrix();

	Shader::DontUseShaders();

	AngleWheelNow += KeyWDuration * Speed * 40;
	if (((long long)AngleWheelNow % 360 > -1 || (long long)AngleWheelNow % 360 < 1) && (AngleWheelNow > 2160 || AngleWheelNow < -2160))
		AngleWheelNow = 0;
	glPushMatrix();
	WheelLeftTex->bindTexture();
	glTranslated(PointKolesL.X(), PointKolesL.Y(), PointKolesL.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZWheel, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0);
	KolesL->DrawObj();
	glPopMatrix();

	glPushMatrix();
	glTranslated(PointKolesR.X(), PointKolesR.Y(), PointKolesR.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZWheel, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0); 
	KolesR->DrawObj();
	glPopMatrix();

	glPushMatrix();
	glTranslated(PointKolesLBack.X(), PointKolesLBack.Y(), PointKolesLBack.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZ, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0); 
	KolesL->DrawObj();
	glPopMatrix();

	glPushMatrix();
	glTranslated(PointKolesRBack.X(), PointKolesRBack.Y(), PointKolesRBack.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZ, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0);
	KolesR->DrawObj();
	glPopMatrix();
}

void CarModel::CheckPosition(double TimeLastFrame)
{
	double end = clock();
	TimeFrame = (end - TimeLastFrame) / CLOCKS_PER_SEC;
	if (TimeFrame == 0)
		TimeFrame = 0.001;
	
	if (TimeFrame > 2 || TimeFrame < 0)
		return;

	if (SelectedTransmissionNow == 4)
	{
		int asdaf = 0;
	}
	
	W_ivent();
	A_ivent();
	S_ivent();
	D_ivent();
	NoneKey_ivent();

	if (AutoTransmission) 
	{
		if (RevsNowGlob > 7500 && SelectedTransmissionNow != TransmissionCount && SelectedTransmissionNow != -1)
		{
			SelectedTransmissionNow = (SelectedTransmission)(SelectedTransmissionNow + 1);
		}

		if (RevsNowGlob < 4000 && SelectedTransmissionNow > 1)
		{
			SelectedTransmissionNow = (SelectedTransmission)(SelectedTransmissionNow - 1);
		}

		if (KeyWDuration == 0 && OpenGL::isKeyPressed('S')) 
			SelectedTransmissionNow = Reverse;

		if (KeyWDuration == 0 && OpenGL::isKeyPressed('W') && SelectedTransmissionNow == -1)
			SelectedTransmissionNow = First;
	}
	else
	{
		if (OpenGL::isKeyPressed(17))
		{
			if (SelectedTransmissionNow > 0 && KeyWDuration >= 0)
			{
				if (SelectedTransmissionNow != 0 && SelectTransmissionEnable)
				{
					SelectedTransmissionNow = (SelectedTransmission)(SelectedTransmissionNow - 1);
				}
			}
			if (SelectedTransmissionNow == 0 && KeyWDuration == 0)
			{
				SelectedTransmissionNow = (SelectedTransmission)(SelectedTransmissionNow - 1);
			}
			SelectTransmissionEnable = false;
		}

		if (OpenGL::isKeyPressed(16))
		{
			if (KeyWDuration < 0 && SelectedTransmissionNow != -1) 
			{

			}
			else
			{
				if (SelectedTransmissionNow != TransmissionCount && SelectTransmissionEnable && !AutoTransmission) 
				{
					SelectedTransmissionNow = (SelectedTransmission)(SelectedTransmissionNow + 1);
				}
				SelectTransmissionEnable = false;
			}
		}
	}

	RevsNowGlob = RevNow(); 
}

void CarModel::DrawShadow(Vector3 lightPosVec)
{
	
	CMatrix4x4 ShadowMatrix;


	CVector4 lightPos(lightPosVec.X(), lightPosVec.Y(), lightPosVec.Z(), 1.0f);
	CVector4 planeNormal(0.0f, 0.0f, 1.0f, 0.0f);

	
	ShadowMatrix.CreateShadowMatrix(planeNormal, lightPos);

	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glColor3d(0.4, 0.4, 0.4);

	glMultMatrixf(ShadowMatrix.matrix);
	glTranslated(CarPoint.X(), CarPoint.Y(), CarPoint.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZ, 0, 1, 0);
	Car->DrawObj();
	POP;
	PUSH;
	glMultMatrixf(ShadowMatrix.matrix);
	glTranslated(PointKolesL.X(), PointKolesL.Y(), PointKolesL.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZWheel, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0);
	KolesL->DrawObj();
	POP;
	PUSH;
	glMultMatrixf(ShadowMatrix.matrix);
	glTranslated(PointKolesR.X(), PointKolesR.Y(), PointKolesR.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZWheel, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0);
	KolesR->DrawObj();
	POP;
	PUSH;
	glMultMatrixf(ShadowMatrix.matrix);
	glTranslated(PointKolesLBack.X(), PointKolesLBack.Y(), PointKolesLBack.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZ, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0);
	KolesL->DrawObj();
	POP;
	PUSH;
	glMultMatrixf(ShadowMatrix.matrix);
	glTranslated(PointKolesRBack.X(), PointKolesRBack.Y(), PointKolesRBack.Z());
	glRotated(-90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glRotated(180, 0, 1, 0);
	glRotated(AngleZ, 0, 1, 0);
	glRotated(AngleWheelNow, 1, 0, 0); 
	KolesR->DrawObj();

	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

inline double CarModel::RevNow()
{
	double rev;
	if (SelectedTransmissionNow == SelectedTransmission::Neutral)
	{
		rev = KeyWDuration * 1600 / 1;
		return rev;
	}
	if (KeyWDuration < 0.625 && KeyWDuration >= 0) // 800 - 1000 оборотов
	{
		rev = 800 + KeyWDuration / SelectedTransmissionNow * 320;
		return rev;
	}
	if (KeyWDuration > -0.625 && KeyWDuration <= 0) // 800 - 1000 оборотов
	{
		rev = -800 - KeyWDuration / SelectedTransmissionNow * 320;
		return -rev;
	}
	if (SelectedTransmissionNow == -1 || KeyWDuration < 0)
	{
		rev = KeyWDuration * 1600 / 1;
		return -rev;
	}
	rev = KeyWDuration * 1600 / SelectedTransmissionNow;
	return rev;
}

inline double CarModel::GearRatio()
{
	switch (SelectedTransmissionNow)
	{
	case Reverse:
		return 2.5;
		break;
	case Neutral:
		return 6;
		break;
	case 1:
		return 2.5;
		break;
	case 2:
		return 2.2;
		break;
	case 3:
		return 1.9;
		break;
	case 4:
		return 1.5;
		break;
	case 5:
		return 1.3;
		break;
	case 6:
		return 1.1;
		break;
	default:
		return 1;
	}
}

inline double CarModel::TurboCoef()
{
	double rev = RevNow();
	double turbo;
	if (rev < 3000)
	{
		turbo = 0.3 + rev / 10000;
		return turbo;
	}
	if (rev >= 3000 && rev < 6000)
	{
		turbo = 0.45 + rev / 8000;
		return turbo;
	}
	if (rev >= 6000)
	{
		turbo = 1.1 + rev / 80000;
		return turbo;
	}
}

inline void CarModel::setLeftFrontWheel(double x, double y)
{
	dist_x_left_wheel_front = x;
	dist_y_left_wheel_front = y;
}

inline void CarModel::setRightFrontWheel(double x, double y)
{
	dist_x_right_wheel_front = x;
	dist_y_right_wheel_front = y;
}

inline void CarModel::setLeftRearWheel(double x, double y)
{
	dist_x_left_wheel_rear = x;
	dist_y_left_wheel_rear = y;
}

int CarModel::ReturnSelectedGear()
{
	return SelectedTransmissionNow;
}

Vector3 CarModel::ReturnPosition()
{
	return CarPoint;
}

double CarModel::ReturnRevNow()
{
	return RevsNowGlob;
}

double CarModel::ReturnSpeed()
{
	return KeyWDuration * Speed * 100;
}

double CarModel::ReturnAngleZ()
{
	return AngleZ;
}

void CarModel::SetPoint(double x, double y, double z)
{
	CarPoint.setCoords(x, y, z);
}

void CarModel::SetPoint(Vector3 vec)
{
	CarPoint = vec;
}

void CarModel::SetAngleZ(double angle)
{
	AngleZ = angle;
	AngleZWheel = angle;
}

void CarModel::SetKeyWDuration(double k)
{
	KeyWDuration = k;
}

void CarModel::SetGearNow(int n)
{
	SelectedTransmissionNow = (SelectedTransmission)(n);
}

inline void CarModel::setRightRearWheel(double x, double y)
{
	dist_x_right_wheel_rear = x;
	dist_y_right_wheel_rear = y;
}

Vector3 CarModel::LookAtCar()
{
	Vector3 tmp{
		CarPoint.X() - DistanceFromObj * cos(AngleZ * PI / 180),
		CarPoint.Y() - DistanceFromObj * sin(AngleZ * PI / 180),
		CarPoint.Z() + HeightFromObj
	};
	return tmp;
}