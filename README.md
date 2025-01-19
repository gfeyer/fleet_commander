# Fleet Commander - A Space RTS Game

# Game Instructions

## Setup
### Download the Game
- [Itch.io](https://gfeyer.itch.io/fleet-commander): Download the latest version for your platform.
- [Releases](https://github.com/gfeyer/fleet_commander/releases): Download pre-built binaries for **Windows**, **Linux**, and **macOS**. Simply unzip the file for your platform.

### Build from Source
- If you'd prefer to compile the game yourself, follow the [Build Instructions](#build-instructions) below.

## Gameplay Basics
- **Factories**: Produce drones up to the maximum energy capacity.
- **Power Plants**: Increase maximum energy capacity.
- **Drones**: Use them to conquer other structures.

## Controls
- **Select a Structure**:
  - **Left Click**: Attack another target.
  - **Right Click**: Create a drone transfer route.
  - **Right Click Anywhere (not on a target)**: Cancel an existing route.
- **Movement**:
  - Use **W, A, S, D** to move around the world.



# Screenshots


![Screenshot1](docs/images/screenshot_010.png)
![Screenshot2](docs/images/screenshot_011.png)

# Build instructions

## Dependencies

```
# get the package manager
cd /opt
git clone git@github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh # linux, macos
bootstrap.bat  # windows

# install dependencies

./vcpkg install sfml
./vcpkg install tgui
./vcpkg install entt

```

## Build

Go to the root folder where the repository was cloned

```
mkdir build
cd build

cmake .. "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build . --parallel 4
```

# TODO (soon)

- Skin the game (sprites+animations)
- Improve map generation
- Increase map size
