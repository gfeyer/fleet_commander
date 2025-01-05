#ifndef DEBUG_OVERLAY_SYSTEM_HPP
#define DEBUG_OVERLAY_SYSTEM_HPP

namespace Systems {
    
    void DebugOverlaySystem(Game::GameEntityManager& manager, float dt) {

        if(Config::ENABLE_DEBUG_SYMBOLS == false) return;

        // Calcualte FPS
        for(auto&& [id, debug] : manager.view<Components::DebugOverlayComponent>().each()) {
            
            debug.fpsTimer += dt;
            debug.frameCount++;

            // Update FPS every second
            if (debug.fpsTimer >= 1.0f) {
                debug.fps = debug.frameCount / debug.fpsTimer;
                debug.frameCount = 0;
                debug.fpsTimer = 0.f;
            }
        }
    }
}

#endif // DEBUG_OVERLAY_SYSTEM_HPP