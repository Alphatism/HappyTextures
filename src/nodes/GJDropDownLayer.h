#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/GJDropDownLayer.hpp>

using namespace geode::prelude;

class $modify(MyGJDropDownLayer, GJDropDownLayer) {

    static void onModify(auto& self) {
        HOOK_LATEST("GJDropDownLayer::showLayer");
    }

    void showLayer(bool p0) {
        
        if (UIModding::get()->doModify) {
            setVisible(true);
            removeFromParentAndCleanup(false);
            CCScene* currentScene = CCDirector::get()->getRunningScene();
            currentScene->addChild(this);

            if (p0) {
                m_mainLayer->setPosition(m_endPosition);
                setOpacity(125);
            }
            else {
                CCMoveTo* moveTo = CCMoveTo::create(0.5, m_endPosition);
                CCEaseInOut* easeInOut = CCEaseInOut::create(moveTo, 2.0);
                CCSequence* sequence = CCSequence::create(easeInOut, 0);

                m_mainLayer->runAction(sequence);

                CCFadeTo* fadeTo = CCFadeTo::create(0.5, 125);
                runAction(fadeTo);
            }
            UIModding::get()->doUICheck(this);
        }
        else {
            GJDropDownLayer::showLayer(p0);
        }
    }
};