# multiemu-c99

SteamID certificate generator for No-Steam games.

## What is this?

This project is a reimagination of the [MultiEmulator](https://github.com/2010kohtep/MultiEmulator) project. It still performs the same functions, namely generating a SteamID certificate for a list of emulators commonly used in the No-Steam version of the game Counter-Strike 1.6.

This project was created as part of a personal challenge and an attempt to try something new.

## What are the differences?

The main difference is that the project is written using the C99 standard and can be built with C compilers that support this standard, such as [Tiny C Compiler (TCC)](https://bellard.org/tcc/). The project also supports CMake for building in environments like Visual Studio.

Additionally, unlike the original, in this version, the example and the library itself are combined into a single project.

## How to use?

The compiled library is injected into the No-Steam Counter-Strike 1.6 process using any preferred method. Once injected, the library intercepts the `SteamUser` interface, embedding a custom SteamID certificate generator for the string produced by the `generate_hwid()` function. You can implement your own string generation algorithms if desired or use functions that accept specific SteamID values directly.

## License

This project is licensed under the [MIT License](./LICENSE).