#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <SFML/System/Time.hpp>
#include <string>
#include <sstream>  // For std::stringstream
#include <iomanip>  // For std::setw, std::setfill
#include <stdexcept> // For std::exception in catch block

#include "Game/GameEntityManager.hpp" // Assuming this provides access to the registry/view
#include "Components/AnimationComponent.hpp"
#include "Components/SpriteComponent.hpp"   // Assuming this exists and holds sf::Sprite
#include "Resources/Atlas.hpp"            // The Atlas resource manager
#include "Utils/Logger.hpp"               // Optional: for logging errors

namespace Systems {

    void AnimationSystem(Game::GameEntityManager& manager, float dt) {

        std::vector<EntityID> toRemoveEntities;

        //const Resource::Atlas& atlas
        static const auto& atlas = Resource::ResourceManager::getInstance().getAtlas(Resource::Paths::EXPLOSIONS_ATLAS);
        // auto atlas_texture = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_EXPLOSIONS_ATLAS);

        // Get a view of entities with both Animation and Sprite components
        auto view = manager.view<Components::AnimationComponent, Components::SpriteComponent>();

        for (auto&& [id, anim, spriteComp] : view.each()) {

            // --- Basic Checks ---
            if (!anim.isPlaying || anim.totalFrames == 0 || anim.animationName.empty()) {
                continue; // Animation is paused, finished, or not configured
            }

            // Reset completion flag at the start of the update for this entity
            anim.justCompleted = false;

            // --- Time Accumulation ---
            anim.elapsedTime += dt;

            // --- Frame Advancement Logic ---
            if (anim.elapsedTime >= anim.frameDuration) {

                // Consume the time for this frame step
                // Note: For simplicity, we only advance one frame even if elapsedTime > 2*frameDuration.
                // A more complex loop could handle skipping multiple frames if dt is very large.
                anim.elapsedTime -= anim.frameDuration;

                // Advance to the next frame index
                anim.currentFrame++;

                // Check if animation reached the end
                if (anim.currentFrame >= anim.totalFrames) {
                    anim.justCompleted = true; // Signal completion for this frame
                    toRemoveEntities.push_back(id);

                    if (anim.loop) {
                        anim.currentFrame = 0; // Wrap around for looping animations
                    } else {
                        anim.currentFrame = anim.totalFrames - 1; // Clamp to the last frame
                        anim.isPlaying = false; // Stop non-looping animations
                    }
                }

                // --- Atlas Interaction & Sprite Update ---

                // Construct the frame key based on convention (e.g., "basename_XXXX.png")
                std::stringstream ss;
                // Assumes frame numbers are 0-indexed and need 4 digits padding like in explosions.json
                ss << anim.animationName << "_"
                   << std::setw(4) << std::setfill('0') << anim.currentFrame
                   << ".png"; 
                std::string frameKey = ss.str();

                try {
                    // Get the rectangle from the shared atlas using the generated key
                    sf::IntRect newRect = atlas.getRect(frameKey);

                    // Update the sprite's texture and texture rect
                    spriteComp.sprite.setTextureRect(newRect);
                    spriteComp.sprite.setOrigin(newRect.width / 2, newRect.height / 2);

                } catch (const std::exception& e) {
                    // Handle cases where the generated frame key isn't found in the Atlas
                    // Log an error message (if logger is available)
                     log_err << "Animation frame key not found in atlas: '" << frameKey
                               << "' for animation '" << anim.animationName << "' on entity "
                               << static_cast<uint32_t>(id) << ". Error: " << e.what(); // Cast entity ID if needed for logging

                    // Stop the animation to prevent repeated errors for this entity
                    anim.isPlaying = false;
                }
            }
            // --- End Frame Advancement ---
        }
        // --- End Entity Loop ---

        for (EntityID id : toRemoveEntities) {
            manager.removeEntity(id);
        }
    
    }

} // namespace Systems

#endif // ANIMATION_SYSTEM_HPP