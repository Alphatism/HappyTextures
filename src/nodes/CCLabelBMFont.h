#pragma once

#ifndef MYCCLABELBMFONT_H
#define MYCCLABELBMFONT_H

#include <Geode/Geode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>
#include "../Utils.h"

using namespace geode::prelude;

class $modify(MyCCLabelBMFont, CCLabelBMFont){

    struct Fields {
        float m_limitWidth = 1;
        float m_limitDefaultScale = 1;
        float m_limitMinScale = 1;
        bool m_isLimited = false;
        SEL_SCHEDULE m_schedule;
    };
    
    void limitLabelWidth(float width, float defaultScale, float minScale){

        m_fields->m_limitWidth = width;
        m_fields->m_limitDefaultScale = defaultScale;
        m_fields->m_limitMinScale = minScale;
        m_fields->m_isLimited = true;

        CCLabelBMFont::limitLabelWidth(width, defaultScale, minScale);
    }

    static CCLabelBMFont* create(const char *str, const char *fntFile, float width, CCTextAlignment alignment, CCPoint imageOffset){
        auto ret = CCLabelBMFont::create(str, fntFile, width, alignment, imageOffset);

        auto myRet = static_cast<MyCCLabelBMFont*>(ret);
        myRet->m_fields->m_schedule = schedule_selector(MyCCLabelBMFont::checkParent);
        ret->schedule(myRet->m_fields->m_schedule);
        return ret;
    }

    void checkParent(float dt){
        
        if(auto parent = this->getParent()){
            if(typeinfo_cast<LabelGameObject*>(parent)){
                if(strcmp(this->getFntFile(), "bigFont.fnt") == 0){
                    this->setFntFile("bigFont.fnt"_spr);
                }
            }
            this->unschedule(m_fields->m_schedule);
        }
    }
};

#endif