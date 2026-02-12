#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <random>

using namespace geode::prelude;

class $modify(RNGDPlayLayer, PlayLayer) {
    struct Fields {
        float m_timeSinceLastSwitch = 0.0f;
        float m_switchInterval = 2.0f;
        bool m_enabled = true;
        std::mt19937 m_rng;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        // Initialize random number generator with a proper seed
        std::random_device rd;
        m_fields->m_rng.seed(rd());

        // Load settings
        m_fields->m_switchInterval = Mod::get()->getSettingValue<double>("switch-interval");
        m_fields->m_enabled = Mod::get()->getSettingValue<bool>("enabled");
        m_fields->m_timeSinceLastSwitch = 0.0f;

        log::info("RN-GD initialized! Interval: {}s, Enabled: {}", 
                  m_fields->m_switchInterval, m_fields->m_enabled);

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        // Only switch if enabled and level is playing
        if (!m_fields->m_enabled || !m_player1 || m_isPaused) {
            return;
        }

        // Update timer
        m_fields->m_timeSinceLastSwitch += dt;

        // Check if it's time to switch
        if (m_fields->m_timeSinceLastSwitch >= m_fields->m_switchInterval) {
            m_fields->m_timeSinceLastSwitch = 0.0f;
            switchGamemode();
        }
    }

    void switchGamemode() {
        if (!m_player1) return;

        // All available gamemodes in GD (using PlayerObject IconType enum)
        std::vector<int> gamemodes = {
            0,  // Cube
            1,  // Ship
            2,  // Ball
            3,  // UFO
            4,  // Wave
            5,  // Robot
            6   // Spider
        };

        // Get random gamemode
        std::uniform_int_distribution<> dis(0, gamemodes.size() - 1);
        int randomMode = gamemodes[dis(m_fields->m_rng)];

        // Get current gamemode to avoid switching to same mode
        bool isCurrentlyShip = m_player1->m_isShip;
        bool isCurrentlyBall = m_player1->m_isBall;
        bool isCurrentlyUFO = m_player1->m_isBird;
        bool isCurrentlyWave = m_player1->m_isDart;
        bool isCurrentlyRobot = m_player1->m_isRobot;
        bool isCurrentlySpider = m_player1->m_isSpider;
        
        int currentMode = 0;  // Default to cube
        if (isCurrentlyShip) currentMode = 1;
        else if (isCurrentlyBall) currentMode = 2;
        else if (isCurrentlyUFO) currentMode = 3;
        else if (isCurrentlyWave) currentMode = 4;
        else if (isCurrentlyRobot) currentMode = 5;
        else if (isCurrentlySpider) currentMode = 6;
        
        // Try to get a different gamemode (max 3 attempts to avoid infinite loop)
        for (int i = 0; i < 3 && randomMode == currentMode; i++) {
            randomMode = gamemodes[dis(m_fields->m_rng)];
        }

        // Switch the gamemode using appropriate method
        // toggleFlyMode switches between different vehicle types
        m_player1->toggleFlyMode(randomMode, false);

        log::debug("Switched from mode {} to gamemode: {}", currentMode, randomMode);
    }
};

$execute {
    log::info("RN-GD mod loaded!");
}
