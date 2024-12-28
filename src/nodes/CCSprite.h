#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/CCSpriteWithHue.hpp>
#include "../Macros.h"

class $modify(MyCCSpriteWithHue, CCSpriteWithHue) {

    static void onModify(auto& self) {
        (void) self.setHookPriority("cocos2d::CCSpriteWithHue::initWithSpriteFrame", Priority::VeryEarly);
    }

    bool initWithSpriteFrame(cocos2d::CCSpriteFrame* p0) {
        std::string frameName = Utils::getSpriteName(p0);

        if (Utils::spriteExistsInPacks(frameName)) {
            CCSprite* spr = CCSprite::create(frameName.c_str());
            auto spriteFrame = CCSpriteFrame::createWithTexture(spr->getTexture(), spr->getTextureRect());
            CCSpriteFrameCache::get()->addSpriteFrame(spriteFrame, frameName.c_str());
            return CCSpriteWithHue::initWithSpriteFrame(spriteFrame);
        }

        return CCSpriteWithHue::initWithSpriteFrame(p0);
    }
};

class $modify(MyCCSprite, CCSprite) {

    static void onModify(auto& self) {
        (void) self.setHookPriority("cocos2d::CCSprite::initWithSpriteFrameName", Priority::VeryEarly);
        (void) self.setHookPriority("cocos2d::CCSprite::createWithSpriteFrameName", Priority::VeryEarly);
    }

    bool initWithSpriteFrameName(const char *pszSpriteFrameName) {
        if (Utils::spriteExistsInPacks(pszSpriteFrameName)) {

            CCSprite* spr = CCSprite::create(pszSpriteFrameName);
            auto spriteFrame = CCSpriteFrame::createWithTexture(spr->getTexture(), spr->getTextureRect());
            CCSpriteFrameCache::get()->addSpriteFrame(spriteFrame, pszSpriteFrameName);
        }
        return CCSprite::initWithSpriteFrameName(pszSpriteFrameName);
    }

    static CCSprite* createWithSpriteFrameName(const char *pszSpriteFrameName) {
        if (Utils::spriteExistsInPacks(pszSpriteFrameName)) {

            CCSprite* spr = CCSprite::create(pszSpriteFrameName);
            auto spriteFrame = CCSpriteFrame::createWithTexture(spr->getTexture(), spr->getTextureRect());
            CCSpriteFrameCache::get()->addSpriteFrame(spriteFrame, pszSpriteFrameName);
        }

        return CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
    }
};
