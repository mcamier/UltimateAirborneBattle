#ifndef _C_SPRITE_H_
#define _C_SPRITE_H_

#include "SDL2/SDL.h"
#include "entity/CPT_component.h"
#include "C_rendereable2D.h"
#include "core/core.h"
#include "graphic/graphic.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include "resource/resourceManager.h"

using namespace rapidjson;
using Compote::Core::Locator;
using Compote::Graphic::Sprite;
using Compote::Resource::ResourceManager;

class CSprite : public CRendereable2D {
    friend class PSpriteRenderer;

private:
    ResHandler<Sprite>  *m_pSprite;

public:
                        CSprite(ResHandler<Sprite> *sprite, int order) :
                            m_pSprite(sprite) {
                            
                            this->setOrder(order);
                        }

    virtual             ~CSprite() {}

    SDL_Texture*        getTexture() const override { return m_pSprite->get()->getTexture(); }
    SDL_Rect            getSource() const override { return m_pSprite->get()->getSourceRect(); }
    int                 getWidth() const override { return m_pSprite->get()->getWidth(); }
    int                 getHeight() const override { return m_pSprite->get()->getHeight(); }

    static const char* getName(void) {
        return "CSprite";
    }

    IComponent* clone(void) const {
        // TODO clone ResHandler
        CSprite *clone = new CSprite(this->m_pSprite, this->m_order);
        clone->m_flip = this->m_flip;
        clone->m_alpha = this->m_alpha;
        return clone;
    }
};


class CSpriteCreator :
    public BaseCreator<IComponent> {

public:
    IComponent* create(const rapidjson::Value& node) {
        
        CSprite *component = new CSprite(nullptr, 0);

        if (node.HasMember("resourceSpriteID")) {
            Locator::getResourceManager()->get<Sprite>(node["resourceSpriteID"].GetInt());
        }
        if (node.HasMember("order")) {
            component->setOrder(node["order"].GetInt());
        }
        if (node.HasMember("alpha")) {
            component->setAlpha(node["alpha"].GetInt());
        }
    
        return component;
    }
};

#endif