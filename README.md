# multiemu-c99

SteamID certificate generator for No-Steam games.

## What is this?

This project is a reimagination of the [MultiEmulator](https://github.com/2010kohtep/MultiEmulator) project. It still performs the same functions, namely generating a SteamID certificate for a list of emulators commonly used in the No-Steam version of the game Counter-Strike 1.6.

This project was created as part of a personal challenge and an attempt to try something new.

## What are the differences?

The main difference is that the project is written using the C99 standard and can be built with C compilers that support this standard, such as [Tiny C Compiler (TCC)](https://bellard.org/tcc/). The project also supports CMake for building in environments like Visual Studio.

Additionally, unlike the original, in this version, the example and the library itself are combined into a single project.

## How to use?

This project is primarily presented as a foundation for developers and individuals who understand what they are dealing with. If you simply want to inject a compiled DLL and spoof your SteamID on a server, this project is not for you.

The file `src\impl\emu_impl.c` contains the function `hk_initialize_game_connection()`, which is responsible for generating a certificate and setting a custom SteamID. This file also includes the function `generate_hwid()`, which returns a static HWID string as an example. You can implement your own HWID generation algorithm here if you wish.

All available certificate generators are located in the `src\features` folder. Typically, each of them provides a generation function by number and by string. If you use the generation function by number, the corresponding SteamID will be presented in the certificate. If you use the generation function by string, the hash value of this string will be represented in the certificate. Some generators, such as Setti, do not allow setting a custom SteamID at all, as this certificate was used in a program that sent a bot to game servers, which was not intended to act as a player.

## License

This project is licensed under the [MIT License](./LICENSE).