#ifndef _C_SPRITE_H_
#define _C_SPRITE_H_

#include "SDL2/SDL.h"
#include "CPT_component.h"
#include "C_rendereable2D.h"
#include "CPT_locator.h"
#include "CPT_resourceManager.h"
#include "CPT_graphic.h"
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"

using namespace rapidjson;

class CSprite : public CRendereable2D {
    friend class PSpriteRenderer;

private:
    Sprite              *m_pSprite;

public:
                        CSprite(Sprite *sprite, int order) : 
                            m_pSprite(sprite) {
                            
                            this->setOrder(order);
                        }

    virtual             ~CSprite() {}

    void                setSprite(Sprite *sprite) { m_pSprite = sprite; }

    SDL_Texture*        getTexture() const override { return m_pSprite->getTexture(); }
    SDL_Rect            getSource() const override { return m_pSprite->getSourceRect(); }
    int                 getWidth() const override { return m_pSprite->getWidth(); }
    int                 getHeight() const override { return m_pSprite->getHeight(); }

    static const char* getName(void) {
        return "CSprite";
    }

    IComponent* clone(void) const {
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