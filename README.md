# RN-GD (Random Gamemode - Geometry Dash)

A Geode mod that randomly changes your gamemode very frequently while playing levels in Geometry Dash!

## Features

- 🎲 Automatically switches between all available gamemodes at configurable intervals
- ⏱️ Configurable switch interval (0.5 - 10 seconds, default: 2 seconds)
- 🔧 Can be enabled/disabled via mod settings
- 🎮 Works on all levels and game modes

## Gamemodes Included

The mod randomly switches between:
- Cube 🟦
- Ship 🚀
- Ball ⚪
- UFO 🛸
- Wave 〰️
- Robot 🤖
- Spider 🕷️

## Installation

1. Install [Geode Mod Loader](https://geode-sdk.org/)
2. Download the latest release of RN-GD
3. Place the `.geode` file in your Geode mods folder
4. Launch Geometry Dash and enjoy!

## Configuration

Access the mod settings in Geometry Dash:
- **Switch Interval**: Set how often the gamemode changes (0.5 - 10 seconds)
- **Enabled**: Toggle the mod on/off

## Building from Source

Requirements:
- [Geode SDK](https://geode-sdk.org/)
- CMake 3.21+
- C++20 compatible compiler

```bash
# Clone the repository
git clone https://github.com/doodle-the-programmer/RN-GD.git
cd RN-GD

# Build with CMake
cmake -B build
cmake --build build --config Release
```

## How It Works

The mod hooks into the PlayLayer update function and randomly switches your gamemode based on the configured time interval, making levels extremely challenging and unpredictable!

## Credits

Created by [doodle-the-programmer](https://github.com/doodle-the-programmer)

## License

See [LICENSE](LICENSE) file for details.