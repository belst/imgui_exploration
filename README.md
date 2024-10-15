# ImGui Exploration tool

This is a tool to explore the ImGui API.

It can hotreload your code while keeping your state.

## Usage

see `src/testplug.cpp` for an example.

Basically, create a library which exposes the following functions:

```cpp
// Initial setup (does not get called again on reload)
__declspec(dllexport) extern "C" void plug_init(void);
// Called before reloading the library
// used to return a state object that will be passed to plug_post_reload
// and to clean up any additional resources you might have created
__declspec(dllexport) extern "C" void* plug_pre_reload(void);
// gets called after reloading the library with the state object returned by plug_pre_reload
__declspec(dllexport) extern "C" void plug_post_reload(void* state);
// Called every frame
__declspec(dllexport) extern "C" void plug_update(Env env);
// unused, but might be used to reset your state
__declspec(dllexport) extern "C" void plug_reset(void);
```

Call `imgui_exploration.exe` with the path to the library as the first argument.  
Eg: `./imgui_exploration.exe testplug.dll`

Pressing `SPACE` will reload the library.

## Building

Create a build directory, eg `build` and run `cmake -B build -S . -G Ninja` in the root directory.

You can of course also use a different generator.

## Rebuilding the library

If you used Ninja, you can just run `ninja testplug` in the build directory to rebuild the library.  
Pressing `SPACE` will then reload the new version.

For your own libraries (if you don't want to modify testplug instead), you can build them however you want, and then run `imgui_exploration.exe` with the path to the library as the first argument.

Also see `CMakeLists.txt` for an example of how to build a library.

## Misc

This library is heavily inspired by [panim](https://github.com/tsoding/panim)
