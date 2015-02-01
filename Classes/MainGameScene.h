#ifndef __MainGameScene_SCENE_H__
#define __MainGameScene_SCENE_H__

#include "cocos2d.h"
#include "SugoiEnemy.h"

class MainGameScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void initTimeCounter(float frame);

    void gameSetting(float frame);
    void gameStart(float frame);
    void timeUp(float frame);
    void gameOver(float frame);

    void updateScore(float frame);

    // enemys
    std::vector<SugoiEnemy*> mEnemys;

    // implement the "static create()" method manually
    CREATE_FUNC(MainGameScene);

private:
    cocos2d::Label* mScoreLabel;
};

#endif // __MainGameScene_SCENE_H__
