# ***Media Keys Fix***
[![C++20](https://img.shields.io/static/v1?label=standard&message=C%2B%2B20&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Latest Release](https://img.shields.io/github/release/epinter/MediaKeysFix.svg)](https://github.com/epinter/MediaKeysFix/releases/latest)
[![Downloads](https://img.shields.io/github/downloads/epinter/MediaKeysFix/total.svg)](https://github.com/epinter/MediaKeysFix/releases/latest)
[![Release Date](https://img.shields.io/github/release-date/epinter/MediaKeysFix.svg)](https://github.com/epinter/MediaKeysFix/releases/latest)
[![License](https://img.shields.io/github/license/epinter/MediaKeysFix.svg)](https://github.com/epinter/MediaKeysFix/blob/main/LICENSE)
[![Site](https://img.shields.io/static/v1?label=site&message=NexusMods&color=blue)](https://www.nexusmods.com/skyrimspecialedition)

## The problem
Skyrim starts with exclusive access to keyboard and mouse, in a way that media keys, Windows key or any other key not handled by DirectInput are ignored. This makes the user life harder, to change volume you need to ALT+TAB or use an overlay.

## The solution
This mod changes DirectInput flags so the game doesn't starts with exclusive access anymore. This leads to another problem, dead keys (for diacritics) are ignored, so some users with keyboard layouts that has accents (US-international, for example) wouldn't be able to type single-quotes or double-quotes in console. This mod fixes this side effect too, but the option must be enabled in .INI (DisableDeadKeys). More details about the exclusive/non-exclusive access of DirectInput can be found [here](https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ee417921%28v=vs.85%29).

## ***Runtime requirements***

- [Skyrim Script Extender (SKSE)](https://skse.silverlock.org/)
- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

## ***Configuration***

The MediaKeysFix.ini has the following options:
~~~
[General]
;; Disable Windows key. Set to true to disable windows key.
DisableWindowsKey = true

;; Disable dead keys. When Skyrim doesn't have exclusive access to keyboard, dead keys stops working.
;;   Users with keyboards layout like US-International or any other that uses dead keys may experience
;;   difficulties to type characters like quotes in console. A way to fix this is effectively disable
;;   dead keys in game.
;; Set to true to disable dead keys.
DisableDeadKeys = false

;; Allow background access. STRONGLY RECOMMENDED TO BE SET = false, only useful for DEBUGGING.
;;   If background access is granted, the device can be acquired at any time,
;;   even when the associated window is not the active window.
;;   The game will receive input even if not active window!!
;; Set to true to allow background (replaces DISCL_FOREGROUND with DISCL_BACKGROUND)
BackgroundAccess = false
~~~
## ***Build requirements***

- [CMake](https://cmake.org/)
- [vcpkg](https://vcpkg.io/en/)
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/)
- [CommonLibSSE-NG](https://github.com/CharmedBaryon/CommonLibSSE-NG)
- [SimpleIni](https://github.com/brofield/simpleini)

## ***Building***

In `Developer Command Prompt for VS 2022` or `Developer PowerShell for VS 2022`, run:

~~~
git clone https://github.com/epinter/MediaKeysFix.git
cd MediaKeysFix
~~~

then

~~~
cmake\build-release.ps1
~~~

or

~~~
cmake -B build -S . --preset ALL --fresh
cmake --build build --config Release
~~~

Then get the .dll in build/Release, or the .7z (ready to install using mod manager) in build.
