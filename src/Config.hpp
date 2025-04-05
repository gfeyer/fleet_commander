#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace Config {
    const unsigned int SCREEN_WIDTH = 1920; 
    const unsigned int SCREEN_HEIGHT = 1080;

    const unsigned int MAP_WIDTH = 1920;
    const unsigned int MAP_HEIGHT = 1080;

    const unsigned int FACTORY_SIZE = 95;
    const unsigned int POWER_PLANT_RADIUS = 50;
    const float DRONE_LENGTH = 10.f;
    const float SCALE_FACTOR = 0.20f;

    constexpr float RAD_TO_DEG = 180.f / 3.14159265358979323846f;

    // GUI consts
    constexpr float GUI_TEXT_SIZE = 18.f;

    // Game consts
    const float DRONE_SPEED = 100.f;
    
    // Game Difficulty
    struct Difficulty {
        inline static float AI_DECISION_INTERVAL_SEC = 5.f;
        inline static unsigned int AI_MAX_EXECUTIONS_PER_TURN = 10;
        inline static float AI_MAX_DISTANCE_TO_ATTACK = 2000.f;
    };

    // Debug Symbols
    const bool ENABLE_DEBUG_SYMBOLS = false;
}


#endif // CONFIG_HPP