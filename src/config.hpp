#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace Config {
    const unsigned int SCREEN_WIDTH = 1920; 
    const unsigned int SCREEN_HEIGHT = 1080;

    const unsigned int MAP_WIDTH = 1920;
    const unsigned int MAP_HEIGHT = 1080;

    const unsigned int FACTORY_SIZE = 50;
    const unsigned int POWER_PLANT_RADIUS = 25;
    const float DRONE_LENGTH = 10.f;

    constexpr float RAD_TO_DEG = 180.f / 3.14159265358979323846f;

    // GUI consts
    constexpr float GUI_TEXT_SIZE = 18.f;
    const bool ENABLE_DEBUG_SYMBOLS = false;

    // Game consts
    const float DRONE_SPEED = 800.f;
    
    // Game Difficulty
    struct Difficulty {
        inline static float AI_DECISION_INTERVAL_SEC = 5.f;
        inline static unsigned int AI_MAX_EXECUTIONS_PER_TURN = 10;
        inline static float AI_MAX_DISTANCE_TO_ATTACK = 500.f;
    };
}


#endif // CONFIG_HPP