#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace Config {
    const unsigned int SCREEN_WIDTH = 1920; 
    const unsigned int SCREEN_HEIGHT = 1080;

    const unsigned int MAP_WIDTH = 1920;
    const unsigned int MAP_HEIGHT = 1080;

    const unsigned int FACTORY_SIZE = 50;
    const unsigned int OUTPOST_RADIUS = 25;
    const float DRONE_LENGTH = 10.f;

    constexpr float RAD_TO_DEG = 180.f / 3.14159265358979323846f;

    // GUI consts
    constexpr float GUI_TEXT_SIZE = 18.f;
}


#endif // CONFIG_HPP