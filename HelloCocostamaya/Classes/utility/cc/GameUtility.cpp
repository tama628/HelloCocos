#include "GameUtility.h"

USING_NS_CC;

namespace GameUtility {

Vec2 localToWorldPosition( const cocos2d::Node *pNode )
{
	// pos = parent.pos + child.pos*parent.scale...
	Vec2 position = Vec2::ZERO;
	{
		const Node *pParent = nullptr;
		const Node *pChild = pNode;
		while( pParent = pChild->getParent() )
		{
			const Vec2 &pos = pChild->getPosition();
			position.x += pos.x * pParent->getScaleX();
			position.y += pos.y * pParent->getScaleY();
			pChild = pParent;
		}
		const Vec2 &pos = pChild->getPosition();
		position.x += pos.x;
		position.y += pos.y;
	}
	return position;
}

clock_t getTimeByMilliSecond()
{
    int mmsec = CLOCKS_PER_SEC / 1000;
    return clock() / mmsec;
}

void grep( std::string &str, const char *src, const char *dst )
{
	int srcLength = strlen(src);
	int dstLength = strlen(dst);

	std::string::size_type pos( str.find( src ) );
	while( pos != std::string::npos )
	{
		str.replace( pos, srcLength, dst );
		pos = str.find( src, pos+dstLength );
	}
}

bool isHit( const Vec2 &point, const Node *pNode )
{
	if( !pNode ) return false;

	// pos = parent.pos + child.pos*parent.scale...
	Vec2 position = localToWorldPosition(pNode);
	const Vec2 &anchor = pNode->getAnchorPoint();
	const Size &size = pNode->getContentSize();
	float scaleX = pNode->getScaleX();
	float scaleY = pNode->getScaleY();

	// size
	Size size2(
		size.width*scaleX,
		size.height*scaleY
	);

	// position
	Vec2 Position2( 
		position.x - size2.width*anchor.x,
		position.y - size2.height*anchor.y
	);

	return isHit( point.x, point.y, Position2.x, Position2.y, size2.width, size2.height );
}

bool isHit( float pointX, float pointY, float x, float y, float width, float height )
{
	return x <= pointX && pointX < x+width && y <= pointY && pointY < y+height;
}

} // namespace GameUtility
