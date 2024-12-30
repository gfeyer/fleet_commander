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

        aiComp->perception.reset();

        log_info << "Running AI Perception System";

        auto& entities = entityManager.getAllEntities();

        for(auto& [id, entity] : entities){
            auto* garisson = entity.getComponent<Components::GarissonComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();

            // Get drone counts per faction
            if(garisson && garisson->getDroneCount() > 0 && faction && faction->faction != Components::Faction::NEUTRAL){
                
                aiComp->perception.garissonByDroneCount[id] = garisson->getDroneCount();
                aiComp->perception.garissonByFaction[id] = faction->faction;

                if( faction->faction == Components::Faction::PLAYER_1){
                    aiComp->perception.playerTotalDrones += garisson->getDroneCount();
                }
                if(faction->faction == Components::Faction::PLAYER_2){
                    aiComp->perception.aiTotalDrones += garisson->getDroneCount();
                }
            }

            auto* powerPlant = entity.getComponent<Components::PowerPlantComponent>();
            if(powerPlant && powerPlant->capacity > 0 && faction && faction->faction != Components::Faction::NEUTRAL){

                if( faction->faction == Components::Faction::PLAYER_1){
                    aiComp->perception.playerTotalEnergy += powerPlant->capacity;
                }
                if(faction->faction == Components::Faction::PLAYER_2){
                    aiComp->perception.aiTotalEnergy += powerPlant->capacity;
                }
            }
        }

        
        log_info << "Perception data: " << aiComp->perception.playerTotalDrones << ", " << aiComp->perception.playerTotalEnergy << ", " << aiComp->perception.aiTotalDrones << ", " << aiComp->perception.aiTotalEnergy;
        log_info << "perception maps: " << aiComp->perception.garissonByDroneCount.size() << ", " << aiComp->perception.garissonByFaction.size();

    }
}


#endif