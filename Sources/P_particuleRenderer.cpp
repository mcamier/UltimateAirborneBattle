#include "P_particuleRenderer.h"

#include <iostream>
#include "C_particuleEmitter.h"
#include "C_transform.h"

ComponentType o[] = { CParticuleEmitter::sk_componentType };
const std::vector<ComponentType> PParticuleRenderer::sk_requirements(o, o + 1);

const unsigned int PParticuleRenderer::getID() const {
    return 10010; 
}

void PParticuleRenderer::v_processRender(entityID id, const GameTime& gameTime) {
    CParticuleEmitter *emitter = getEntityAs<CParticuleEmitter>(id);
    
    for (auto& particule : emitter->m_particulesEmitted) {
            SDL_Rect dest;
            dest.x = particule.x;
            dest.y = particule.y;
            dest.w = particule.sprite->getWidth();
            dest.h = particule.sprite->getHeight();

            RendererManager::get()->renderSpriteEx2(
                particule.sprite,
                &dest,
                particule.angle,
                particule.lifetime / emitter->m_lifetime);
     
    }
}

void PParticuleRenderer::v_destroy() {}