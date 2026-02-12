#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <random>

using namespace geode::prelude;

// Random number generator
static std::random_device rd;
static std::mt19937 gen(rd());

class $modify(RNGDPlayLayer, PlayLayer) {
    struct Fields {
        float m_timeSinceLastSwitch = 0.0f;
        float m_switchInterval = 2.0f;
        bool m_enabled = true;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

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

        // All available gamemodes in GD
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
        int randomMode = gamemodes[dis(gen)];

        // Get current gamemode to avoid switching to same mode
        int currentMode = static_cast<int>(m_player1->m_vehicleSize);
        
        // Try to get a different gamemode (max 3 attempts to avoid infinite loop)
        for (int i = 0; i < 3 && randomMode == currentMode; i++) {
            randomMode = gamemodes[dis(gen)];
        }

        // Switch the gamemode
        m_player1->toggleFlyMode(randomMode, false);

        log::debug("Switched to gamemode: {}", randomMode);
    }
};

$execute {
    log::info("RN-GD mod loaded!");
}
