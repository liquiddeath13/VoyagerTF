DWORD_PTR Uworld;
DWORD_PTR Rootcomp;
DWORD_PTR Localplayer;
DWORD_PTR PlayerController;
#define PI 3.14159265358979323846f

struct _MATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

_MATRIX Matrix(Vector3 Vec4, Vector3 origin = Vector3(0, 0, 0))
{
	double radPitch = (Vec4.x * double(PI) / 180.f);
	double radYaw = (Vec4.y * double(PI) / 180.f);
	double radRoll = (Vec4.z * double(PI) / 180.f);
	double SP = sinf(radPitch);
	double CP = cosf(radPitch);
	double SY = sinf(radYaw);
	double CY = cosf(radYaw);
	double SR = sinf(radRoll);
	double CR = cosf(radRoll);
	_MATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;
	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;
	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;
	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;
	return matrix;
}

struct CamewaDescwipsion
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
	char Useless[0x18];
};
CamewaDescwipsion GetViewPoint()
{
	char v1; // r8
	CamewaDescwipsion ViewPoint = Memory.Read<CamewaDescwipsion>(Memory.BaseAddress + 0xF0E8BD0);
	BYTE* v2 = (BYTE*)&ViewPoint;
	int i; // edx
	__int64 result; // rax

	v1 = 0x40;
	for (i = 0; i < 0x40; ++i)
	{
		*v2 ^= v1;
		result = (unsigned int)(i + 0x17);
		v1 += i + 0x17;
		v2++;
	}

	return ViewPoint;
}
Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	CamewaDescwipsion vCamera = GetViewPoint();
	_MATRIX tempMatrix = Matrix(vCamera.Rotation, Vector3(0, 0, 0));
	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < 1.f) vTransformed.z = 1.f;
	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}
