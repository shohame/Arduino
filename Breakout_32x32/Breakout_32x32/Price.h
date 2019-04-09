#ifndef __PRICE_H
#define __PRICE_H

#include "Brick.h"
#include "Ball.h"

#define PRICE_DEFAULT_WIDTH		3
#define	PRICE_DEFAULT_HEIGHT	4
#define	PRICE_DEFAULT_SPEED		3		// 3 Pixel / Sec

#define	PRICE_TYPE_COUNT		5		

enum ePriceType 
{
	eLarge	= 10,
	eSmall,
	eThree,
	eBall,
	eFire
};

class Price : public Ball

{
public:
	ePriceType m_eType;

	Price(void);
	~Price(void);

	void MarkBrickOnMatrix();


};




#endif	//	#ifndef __PRICE_H


