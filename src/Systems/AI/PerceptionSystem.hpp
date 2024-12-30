#ifndef AI_PERCEPTION_SYSTEM_HPP
#define AI_PERCEPTION_SYSTEM_HPP

#include "Game/GameEntityManager.hpp"

#include "Components/GarissonComponent.hpp"
#include "Components/FactionComponent.hpp"

#include "Utils/Logger.hpp"

namespace Systems::AI {
    
    void PerceptionSystem(Game::GameEntityManager& entityManager, float dt){
        Entity& aiEntity = entityManager.getAIEntity();
        auto* aiComp = aiEntity.getComponent<Components::AIComponent>();

        if(!aiComp){
            log_err << "Failed to get aiComponent";
        }

        log_info << "Running AI Perception System";

        auto& entities = entityManager.getAllEntities();

        for(auto& [id, entity] : entities){
            auto* garisson = entity.getComponent<Components::GarissonComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();

            // Get drone counts per faction
            if(garisson && faction && faction->faction != Components::Faction::NEUTRAL){
                if(garisson->getDroneCount() > 0 && faction->faction == Components::Faction::PLAYER_1){
                    aiComp->perception.playerTotalDrones += garisson->getDroneCount();
                }
                if(garisson->getDroneCount() > 0 && faction->faction == Components::Faction::PLAYER_2){
                    aiComp->perception.aiTotalDrones += garisson->getDroneCount();
                }
            }
        }


        // aiComp->perception.aiTotalDrones = entityManager.getDroneCount();
    }
}


#endif