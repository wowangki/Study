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
		case PIVOT_LT :
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
			return RectF(pos.x - (size.width * 0.5f), pos.y - size.height, pos.x + size.width, pos.y);
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

	inline D2D1_ELLIPSE MakeCircle(D2D_POINT_2F pos, D2D_SIZE_F size) {
		return Ellipse(pos, size.width, size.height);
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
}
