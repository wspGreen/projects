#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

static const int MAX_COL_GRID = 6;
static const int MAX_ROW_GRID = 6;
static const int GRID_NUM=4;
static const int GRID_RAND_NUM=2;
class CGrid;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    virtual bool onTouchBegan(Touch* touch, Event  *event);
    virtual void onTouchEnded(Touch* touch, Event  *event);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
public:
    void calcVal(int nTimes,String& strDir,int val,int& x,int& y);
    void showInfo();
protected:
    void _randGrid();
protected:
    void _moveDir(String strDir);
    Point _toPos(int x,int y);
    Point _Pt;
    CGrid* _pArrGrid[MAX_ROW_GRID][MAX_COL_GRID];
public:

};

#endif // __HELLOWORLD_SCENE_H__
