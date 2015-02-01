#ifndef __MainGameScene_SCENE_H__
#define __MainGameScene_SCENE_H__

#include "cocos2d.h"
#include "SugoiEnemy.h"

class MainGameScene : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // init
    void initScoreCounter(float frame);
    void initJijin();

    void gameSetting(float frame);
    void gameStart(float frame);
    void gameOver(float frame);
    void gameClear(float frame);
    void timeUp(float frame);
    void judgeUpdate(float frame);
    void updateScore(float frame);

    void myCallback(cocos2d::Ref* pSender);

    // enemys
    std::vector<SugoiEnemy*> mEnemys;
    std::vector<SugoiEnemy*> getEnemys();

    // flag
    std::map<std::string, bool> getFlags();

    CREATE_FUNC(MainGameScene);

private:
    cocos2d::Label* mTimeScoreLabel;
    cocos2d::Label* mEnemyScoreLabel;

    //flag
    void initFlag();
    bool fg_playing;
    bool fg_gameover;
    bool fg_timeup;
};

#endif // __MainGameScene_SCENE_H__
