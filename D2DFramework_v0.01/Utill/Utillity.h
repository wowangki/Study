#pragma once
#define PI (float) 3.14159265359f

//FigureMake
namespace nFigure {
	enum PIVOT {
		PIVOT_LT,
		PIVOT_LC,
		PIVOT_LB,
		PIVOT_CT,
		PIVOT_CC,
		PIVOT_CB,
		PIVOT_RT,
		PIVOT_RC,
		PIVOT_RB
	};

	inline D2D_RECT_F MakeRect(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT::PIVOT_LT) {

		switch (pivot) {
		case PIVOT_LT :default:
			return RectF(pos.x, pos.y, pos.x + size.width, pos.y + size.height);
			break;
		case PIVOT_LC:
			return RectF(pos.x, pos.y - (size.height * 0.5f), pos.x + size.width, pos.y + (size.height * 0.5f));
			break;
		case PIVOT_LB :
			return RectF(pos.x, pos.y - size.height, pos.x + size.width, pos.y);
			break;
		case PIVOT_CT :
			return RectF(pos.x - (size.width * 0.5f), pos.y, pos.x + (size.width * 0.5f), pos.y + size.height);
			break;
		case PIVOT_CC :
			return RectF(pos.x - (size.width * 0.5f), pos.y - (size.height * 0.5f), pos.x + (size.width * 0.5f), pos.y + (size.height * 0.5f));
			break;
		case PIVOT_CB :
			return RectF(pos.x - (size.width * 0.5f), pos.y - size.height, (pos.x + size.width * 0.5f), pos.y);
			break;
		case PIVOT_RT :
			return RectF(pos.x - size.width, pos.y, pos.x, pos.y + size.height);
			break;
		case PIVOT_RC :
			return RectF(pos.x - size.width, pos.y - (size.height * 0.5f), pos.x, pos.y + (size.height * 0.5f));
			break;
		case PIVOT_RB :
			return RectF(pos.x - size.width, pos.y - size.height, pos.x, pos.y);
			break;
		}
	}

	inline D2D1_ROUNDED_RECT MakeRoundRect(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT::PIVOT_LT, float radiusX = 0, float radiusY = 0) {

		return RoundedRect(MakeRect(pos, size, pivot), radiusX, radiusY);
	}

	inline D2D1_ELLIPSE MakeCircle(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT::PIVOT_LT) {
		switch (pivot) {
		case PIVOT_LT:default:
			return Ellipse({ pos.x + size.width * 0.5f, pos.y + size.height * 0.5f }, size.width, size.height);
			break;
		case PIVOT_LC:
			return Ellipse({ pos.x + size.width * 0.5f, pos.y }, size.width, size.height);
			break;
		case PIVOT_LB:
			return Ellipse({ pos.x + size.width * 0.5f, pos.y - size.height * 0.5f }, size.width, size.height);
			break;
		case PIVOT_CT:
			return Ellipse({ pos.x, pos.y + size.height * 0.5f }, size.width, size.height);
			break;
		case PIVOT_CC:
			return Ellipse(pos, size.width, size.height);
			break;
		case PIVOT_CB:
			return Ellipse({ pos.x, pos.y - size.height * 0.5f }, size.width, size.height);
			break;
		case PIVOT_RT:
			return Ellipse({ pos.x - size.width * 0.5f, pos.y + size.height * 0.5f }, size.width, size.height);
			break;
		case PIVOT_RC:
			return Ellipse({ pos.x - size.width * 0.5f, pos.y}, size.width, size.height);
			break;
		case PIVOT_RB:
			return Ellipse({ pos.x - size.width * 0.5f, pos.y - size.height * 0.5f }, size.width, size.height);
			break;
		}
	}

	inline D2D_POINT_2F VectorNormalized(D2D_POINT_2F pos) {
		D2D_POINT_2F temp = { 0,0 };
		
		if (pos.x != 0) {
			temp.x = pos.x / (sqrt(pow(pos.x, 2) + pow(pos.y, 2)));
		}
		
		if (pos.y != 0) {
			temp.y = pos.y / (sqrt(pow(pos.x, 2) + pow(pos.y, 2)));
		}

		return temp;
	}
}

// String
namespace nString {
	inline wstring StringToWstring(const string& str) {
		int len = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), nullptr, 0);
		wstring temp(len, 0);

		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &temp[0], len);
		return temp;
	}

	inline string WstringToString(const wstring& str) {
		string temp;
		temp.assign(str.begin(), str.end());
		return temp;
	}
}


// RADIAN & DEGREE
namespace nRadian {
	inline float RadianToDegree(float radian) {
		return radian * (180.0f / PI);
	}

	inline float DegreeToRadian(float degree) {
		return degree * (PI / 180.0f);
	}

	inline float RevisionRadian(float radian)
	{
		float temp = radian;

		while (true) {
			if ((temp >= 0.0f || fabsf(temp - 1.0f) <= FLT_EPSILON) && temp < 2 * PI) break;

			if (temp > 0) {
				temp -= 2 * PI;
			}
			else {
				temp += 2 * PI;
			}
		}

		return temp;
	}

	inline float RevisionDegree(float degree)
	{
		float temp = degree;

		while (true) {
			if ((temp >= 0.0f || fabsf(temp - 1.0f) <= FLT_EPSILON) && temp < 360.0f) break;

			if (temp > 0) {
				temp -= 360.0f;
			}
			else {
				temp += 360.0f;
			}
		}

		return temp;
	}
}

//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== ERRORFINDMETHOD =======================//

namespace nErrorFind {

	template<typename T>
	HRESULT PopErrorBox(T* ptr) {
		if (!ptr) {
			TCHAR errorStr[256];
			WCHAR errorText[] = L"초기화에 실패 했습니다.\nClassName: %s";
			_stprintf_s(errorStr, errorText, typeid(ptr).name());
			MessageBox(AppDesc._hWnd, errorStr, NULL, MB_OK);
			return E_FAIL;
		}
		return S_OK;
	}

}