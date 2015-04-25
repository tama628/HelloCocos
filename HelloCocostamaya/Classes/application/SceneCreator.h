#pragma once

class GameScene;
class SceneCreator {

	SceneCreator();

public:

	enum class SceneID {

		HELLO_WORLD,
		LIFE_GAME,
		SHOOTING,

#ifndef NDEBUG
		DEBUG
#endif

	};

public:

	static GameScene *create( SceneID scene );

};

typedef SceneCreator::SceneID SceneID;
inline GameScene *CreateScene( SceneID scene )
{
	return SceneCreator::create( scene );
}
