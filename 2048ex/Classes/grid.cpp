//
//  grid.cpp
//  2048ex
//
//  Created by 王少培 on 14-6-16.
//
//

#include "grid.h"
#include "cocos2d.h"
USING_NS_CC;
CGrid::CGrid()
:mPt(ccp(0,0)),mType(-1),mpSp(NULL)
{
}
void CGrid::onEnter()
{
    Node::onEnter();
    
}
bool CGrid::init()
{
    if(!Node::init())
        return false;
   
    mpSp = Sprite::create();
    this->addChild(mpSp);
    return true;
}
void CGrid::setSp(const char *szName)
{
    SpriteFrame* f= SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
    mpSp->setDisplayFrame(f);
}