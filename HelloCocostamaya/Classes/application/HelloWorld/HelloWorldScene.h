#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

// #include "cocos2d.h"
#include "common.h"

class HelloWorldScene : public GameScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual void initialize() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorldScene);
};

#endif // __HELLOWORLD_SCENE_H__
