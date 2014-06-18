//
//  grid.h
//  2048ex
//
//  Created by 王少培 on 14-6-16.
//
//

#ifndef ___048ex__grid__
#define ___048ex__grid__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class CGrid:public Node
{
public:
    CGrid();
public:
    virtual bool init();
    virtual void onEnter();
    void setSp(const char* szName);
    CREATE_FUNC(CGrid)
public:
    CCPoint mPt;
    int mType;
    CCSprite* mpSp;
    
};
#endif /* defined(___048ex__grid__) */
