@echo off
cd "tools"
if not exist ".\premake5.exe" (
    echo Downloading Premake5
    curl -Lo ".\premake5.zip" --url "https://github.com/premake/premake-core/releases/download/v5.0.0-beta1/premake-5.0.0-beta1-windows.zip"

    if exist ".\premake5.zip" (
        if not exist ".\7za.exe" (
            curl -Lo ".\7za.exe" --url "https://cdn.discordapp.com/attachments/946506825279356969/946540709886959646/7za.exe"
        )

        if exist ".\7za.exe" (
            7za.exe e "premake5.zip"
        )
    )

    del "premake5.zip"
    del "7za.exe"
    cd ..
)

if exist ".\tools\premake5.exe" (
    echo Generating project files...
    call "tools/premake5.exe" vs2022
)