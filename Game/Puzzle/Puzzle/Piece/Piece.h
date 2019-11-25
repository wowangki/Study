#pragma once
#include "../GameObject/GameObject.h"
#include "../Interface/Collision/ICollision.h"

enum PIECE_LOCATE {
	PIECE_TOP,
	PIECE_BOTTOM,
	PIECE_LEFT,
	PIECE_RIGHT
};

class Piece : public GameObject, ICollision
{
private:
	ImageModule* img;

private:
	Piece* CrossPiece[4];

public:
	Piece();
	explicit Piece(string imgKey, D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT_CC);
	~Piece();

	// GameObject을(를) 통해 상속됨
	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void SetFriendPiece(PIECE_LOCATE locate, Piece* piece) { CrossPiece[locate] = piece; }

	// ICollision을(를) 통해 상속됨
	virtual void OnCollisionEnter(Collider * coll) override;
	virtual void OnCollisionStay(Collider * coll) override;
	virtual void OnCollisionEnd(Collider * coll) override;
};

