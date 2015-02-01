//
//  SugoiEnemy.h
//  sugoi-td
//
//  Created by Isao Kono on 2015/01/31.
//
//

#ifndef __sugoi_td__SugoiEnemy__
#define __sugoi_td__SugoiEnemy__

#include <stdio.h>

class SugoiEnemy : public cocos2d::Sprite {
public:
    SugoiEnemy();
    ~SugoiEnemy();
    static SugoiEnemy* create();

    void initOptions();
    void addEvents();
    void touchEvent(cocos2d::Touch* touch);

    void timeUp();

private:
    void update(float frame);

    int mSpeed;
    int mLifeCount;
};

#endif /* defined(__sugoi_td__SugoiEnemy__) */
