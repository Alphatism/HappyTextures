#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../Callbacks.h"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {

    static void onModify(auto& self) {
        (void) self.setHookPriority("MenuLayer::init", INT_MIN/2-1);
    }

    void onPlay(CCObject* obj) {
        if (static_cast<CCNode*>(obj)->getUserObject("dummy"_spr)) {
            CCDirector::get()->pushScene(CCTransitionFade::create(0.5, LevelSelectLayer::scene(0)));
        }
        else {
            MenuLayer::onPlay(obj);
        }
    }

    bool init() {
        UIModding::get()->finishedLoad = true;
        if (!MenuLayer::init()) return false;
        UIModding::get()->doModify = Mod::get()->getSettingValue<bool>("ui-modifications");
        Callbacks::get()->generateAll();

        if (UIModding::get()->doModify) {
            if (Mod::get()->getSettingValue<bool>("hot-reload")) {
                UIModding::get()->startFileListeners();
            }
            UIModding::get()->doUICheck(this);
        }
        return true;
    }
};