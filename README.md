# Fleet Dominion

### Space strategy game

### TODO


### Screenshots

![Screenshot1](docs/images/screenshot_007.png)


![Screenshot2](docs/images/screenshot_010.png)

### Build from source


#### Dependencies

```
# get the package manager
cd /opt
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh # linux, macos
bootstrap.bat  # windows

# install dependencies

./vcpkg install sfml
./vcpkg install tgui

```

#### Build

Go to the root folder where the repository was cloned

```
mkdir build
cd build

cmake .. "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build . --parallel 4
```