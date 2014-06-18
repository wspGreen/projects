#include "HelloWorldScene.h"
#include "CCSpriteFrameCache.h"
#include "grid.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
USING_NS_CC;
String cellcolour[]={
    "2048_red.png",
      "2048_bule.png",
    "2048_yellow.png",
    "2048_green.png"
};
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    srand( (unsigned)time( NULL ) );
//    memset(_pArrGrid,NULL,sizeof(_pArrGrid)*MAX_COL_GRID*MAX_ROW_GRID);
    for (int x=0; x < 6; x++) {
        for (int y=0; y<6; y++) {
            _pArrGrid[x][y]=NULL;
        }
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("2048ex.plist", "2048ex.png");
    auto sprite = Sprite::createWithSpriteFrameName("2048_bg.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
   
    for (int x = 4; x<6; x++) {
        for (int y=4; y<6; y++) {
            CGrid* g = CGrid::create();
            g->mPt = Point(x,y);
            Point pt=_toPos(x,y);
            g->setPosition(pt);
            int r = rand()%GRID_NUM;
            g->mType = r;
            g->setSp(cellcolour[r].getCString());
            addChild(g);
            _pArrGrid[x][y]=g;
        }
    }
    showInfo();
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event  *event)
{
    _Pt = touch->getLocation();
    return true;
}
Point HelloWorld::_toPos(int x,int y)
{
    int xx = 58 + 610/6 * (x);
    int yy = 206+ 658/6 * (y) +88;
    return CCPointMake(xx, yy);

}
void HelloWorld::onTouchEnded(Touch* touch, Event  *event)
{
    int tx=touch->getLocation().x-_Pt.x;
    int ty=touch->getLocation().y - _Pt.y;
    if (tx==0)
    {
        tx = tx+1;
        ty = ty+1;
        
    }
    int dis = tx*tx+ty*ty;
        if (dis<10)
        {
            return;
        }
    
    int dt = ty/tx;
    
            if (dt>=-1&&dt<=1)
            {
                if (tx>0)
                {
                    _moveDir("r");
                    CCLOG("right");
                }
                else
                {
                    _moveDir("l");
                    CCLOG("left");
                }
            }else
            {
                if (ty>0)
                {
                    _moveDir("t");
            
                    CCLOG("up");
                }
                else
                {
                    _moveDir("d");
                    CCLOG("dow");
                }
            }
}
void HelloWorld::_moveDir(String strDir)
{
    int x,y;
    x=y=0;
    int counter=0;
    for (int a = 6-1; a >= 0; a--) {
        //判断每个颜色单独在每一行的个数
        calcVal(1,strDir,a,x,y);
        for (int t=0; t < GRID_NUM; ++t) {
            //获取相同类型个数
            std::vector<CGrid*> vecLst;
            for (int b=0; b<6; b++) {
                calcVal(2,strDir,b,x,y);
                CGrid* p= _pArrGrid[x][y];
                if (p&&p->mType==t) {
                    vecLst.push_back(p);
                }
            }
            //判读个数
            if (vecLst.size() >= 3) {
                for (int i=0; i<vecLst.size(); ++i) {
                    CGrid* p = vecLst[i];
                    if (p) {
                        _pArrGrid[(int)p->mPt.x][(int)p->mPt.y] = NULL;
                        removeChild(p);
                    }
                }
            }
        }
        std::vector<CGrid*> vecTempLst;
        for (int b=0; b<6;b++) {
            calcVal(2,strDir,b,x,y);
            CGrid* p = _pArrGrid[x][y];
            if (p) {
                vecTempLst.push_back(p);
                _pArrGrid[x][y]=NULL;
            }
        }
        //重新设置位置
        if (strDir.compare("l")==0) {
            for (int i=0; i<vecTempLst.size(); ++i) {
                CGrid* g = vecTempLst[i];
                if (g) {
                    g->mPt=CCPoint(i,y);
                    g->setPosition(_toPos(g->mPt.x,g->mPt.y));
                    _pArrGrid[(int)g->mPt.x][(int)g->mPt.y]=g;
                }
            }
        }else if(strDir.compare("r")==0)
        {
            int nCounter=0;
            for (int i=vecTempLst.size()-1; i>=0; --i) {
                CGrid* g = vecTempLst[i];
                if (g) {
                    g->mPt=CCPoint(5-nCounter,y);
                    g->setPosition(_toPos(g->mPt.x,g->mPt.y));
                    _pArrGrid[(int)g->mPt.x][(int)g->mPt.y]=g;
                    nCounter++;
                }
            }
        }else if(strDir.compare("t")==0)
        {
            CCLOG("st:t------------------------");
            int nCounter=0;
            for (int i=vecTempLst.size()-1; i>=0; --i) {
                CGrid* g = vecTempLst[i];
                if (g) {
                    g->mPt=CCPoint(x,5-nCounter);
                    g->setPosition(_toPos(g->mPt.x,g->mPt.y));
                    _pArrGrid[(int)g->mPt.x][(int)g->mPt.y]=g;
                    CCLOG("%d",g->mType);
                    nCounter++;
                }
            }
            CCLOG("en:t------------------------");
        }else if(strDir.compare("d")==0)
        {
            for (int i=0; i<vecTempLst.size(); ++i) {
                CGrid* g = vecTempLst[i];
                if (g) {
                    g->mPt=CCPoint(x,i);
                    g->setPosition(_toPos(g->mPt.x,g->mPt.y));
                    _pArrGrid[(int)g->mPt.x][(int)g->mPt.y]=g;
                }
            }
        }
    }
    _randGrid();
    return;
}
void HelloWorld::_randGrid()
{
    for (int i=0; i < GRID_RAND_NUM; ++i) {
        std::vector<Point> vec;
        for (int x=0; x<6;x++) {
            for (int y=0; y<6;  y++) {
                CGrid* p= _pArrGrid[x][y];
                if (p==NULL) {
                    vec.push_back(CCPoint(x,y));
                }
            }
        }
        if (!vec.empty()) {
            int nRand = rand()%(vec.size());
             int nRandType=rand()%(GRID_NUM);
            Point& pt  = vec[nRand];
            CGrid* pNew =  CGrid::create();
            pNew->mPt=CCPoint(pt.x,pt.y);
            pNew->setPosition(_toPos(pt.x,pt.y));
            pNew->mType = nRandType;
            pNew->setSp(cellcolour[nRandType].getCString());
            _pArrGrid[(int)pt.x][(int)pt.y]=pNew;
            addChild(pNew);
        }
        
    }
    showInfo();
}
void HelloWorld::showInfo()
{
    //String str1;
    CCLOG("st----------------------------");
    for (int y=5; y>=0;y--) {
        std::string str;
        for (int x=0; x<6;  x++) {
            CGrid* p= _pArrGrid[x][y];
            if (p) {
                str += StringUtils::toString(p->mType);
                str += " ";
            }else{
                str +="- ";
            }
        }
        CCLOG(str.c_str());
    }
    CCLOG("en----------------------------");
}
void HelloWorld::calcVal(int nTimes,String& strDir,int val,int& x,int& y)
{
    if (nTimes==1) {
        if (strDir.compare("l") == 0 || strDir.compare("r") == 0)
            y=val;
        else if(strDir.compare("t")==0||strDir.compare("d")==0)
            x=val;
        
    }else if(nTimes==2)
    {
        if (strDir.compare("l") == 0 || strDir.compare("r") == 0)
            x=val;
        else if(strDir.compare("t")==0||strDir.compare("d")==0)
            y=val;
    }
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
