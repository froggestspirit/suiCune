@echo off

cd "tools"
if not exist ".\premake5.exe" (
    echo [INFO] Premake5 doesn't exist
    echo [INFO] Downloading Premake5
    curl -Lo ".\premake5.zip" --url "https://github.com/premake/premake-core/releases/download/v5.0.0-beta1/premake-5.0.0-beta1-windows.zip"

    if exist ".\premake5.zip" (
        if not exist ".\7za.exe" (
            echo [INFO] Downloading 7za
            curl -Lo ".\7za.exe" --url "https://github.com/BttrDrgn/Utilities/raw/master/7za.exe"
        )

        if exist ".\7za.exe" (
            echo [INFO] Extracting premake5.zip
            7za.exe e "premake5.zip" -y -bsp0 -bso0
        )
    )

    echo [INFO] Finished. Deleting leftovers

    del "premake5.zip"
    del "7za.exe"
)
 cd ..

echo [INFO] Generating project files
call "tools/premake5.exe" vs2022