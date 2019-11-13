#pragma once

//트랜스폼은 오브젝트에 무조건 하나만 생성하므로 유니티 처럼 일대일매치시켜두 되니까
//오브젝트 생성시 무조건 하나 생성하고 메인 컴포넌트로 ~
//friend로 gameobject랑 서로 묶어주면 유니티처럼 만들 수 있음
//

class Transform 
{
private:
	D2D_POINT_2F pos;		// POSITION
	D2D_SIZE_F size;		// SIZE
	float angle;			// ANGLE

public:
	Transform();
	~Transform();
	
	//Getter & Setter

	inline D2D_POINT_2F GetPos(void) const { return pos; }
	inline D2D_SIZE_F GetSize(void) const { return size; }
	inline float GetAngle(void) const { return angle; }

	inline float GetDistance(Transform* other) const {
		return sqrtf(pow(pos.x - other->GetPos().x, 2) + pow(pos.y - other->GetPos().y, 2));
	}

	void SetPos(D2D_POINT_2F pos) { this->pos = pos; }
	void SetPos(float x = 0, float y = 0) { 
		this->pos.x = x; 
		this->pos.y = y; 
	}

	void SetSize(D2D_SIZE_F size) { this->size = size; }
	void SetSize(float scaleX, float scaleY) { 
		this->size.width *= scaleX; 
		this->size.height *= scaleY; 
	}

	void SetDegree(float degree) { this->angle = DegreeToRadian(degree); }
	void SetAngle(float radian) { this->angle = radian; }

};

