@echo off

tcc -std=c99 -m32 -shared -o multiemu.dll ^
    src\main.c ^
    src\features\gen_avsmp.c ^
    src\features\gen_oldrevemu.c ^
    src\features\gen_revemu.c ^
    src\features\gen_revemu2013.c ^
    src\features\gen_sc2009.c ^
    src\features\gen_setti.c ^
    src\features\gen_steamemu.c ^
    src\utils\rev_data.c ^
    src\utils\rev_spoofer.c ^
    src\utils\sse_hash.c ^
    src\impl\emu_impl.c ^
    vendor\rijndael-c99\rijndael_c99.c ^
    vendor\crypto-algorithms\sha256.c

if %ERRORLEVEL% equ 0 (
    echo Done.
) else (
    echo Compilation failed.
    exit /b %ERRORLEVEL%
)