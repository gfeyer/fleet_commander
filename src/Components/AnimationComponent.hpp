#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <SFML/System/Time.hpp> // For sf::Time
#include <string>             // For animation name
#include <cstddef>            // For size_t

namespace Components {

    struct AnimationComponent {
       
        std::string animationName = "";
        size_t totalFrames = 0;
        float frameDuration = 0.1f; // Default to 10 FPS
        bool loop = true;
        size_t currentFrame = 0;
        float elapsedTime = 0.f;
        bool isPlaying = true;
        bool justCompleted = false;

        AnimationComponent(const std::string& newName, size_t numFrames,
                          float newFrameDuration = 0.1f,
                          bool shouldLoop = true, bool playImmediately = true)
        {
            if (animationName != newName || totalFrames != numFrames) { // Only reset if different
                animationName = newName;
                totalFrames = numFrames;
                frameDuration = newFrameDuration;
                loop = shouldLoop;
                currentFrame = 0;
                elapsedTime = 0.f;
                isPlaying = playImmediately;
                justCompleted = false;
            } else {
                 // If setting the same animation again, maybe just restart it?
                 currentFrame = 0;
                 elapsedTime = 0.f;
                 isPlaying = playImmediately;
                 justCompleted = false;
                 loop = shouldLoop; // Update loop status in case it changed
                 frameDuration = newFrameDuration; // Update duration
            }
        }
    };

} // namespace Components

#endif // ANIMATION_COMPONENT_HPP