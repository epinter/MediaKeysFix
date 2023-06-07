#pragma once
/*
Copyright (c) 2023 Emerson Pinter

This file is part of Media Keys Fix SKSE.

Foobar is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#include <SimpleIni.h>

namespace constants {
    static constexpr const char* CONFIG_FILE = "MediaKeysFix.ini";
    static constexpr const char* INI_SECTION = "General";
    static constexpr const char* OPT_INIDISWINKEY = "DisableWindowsKey";
    static constexpr const char* OPT_INIBACKGN = "BackgroundAccess";
    static constexpr const char* OPT_INIDISDEADK = "DisableDeadKeys";
    static constexpr const char* OPT_INIDEBUG = "Debug";
    static constexpr const char* COMMENT_INIDEBUG = ";; Hooks DirectInput to log the keyboard and mouse cooperativeLevel dwFlags.";
    static constexpr const char* COMMENT_INIWINKEY = ";; Disable Windows key. Set to true to disable windows key.";
    static constexpr const char* COMMENT_INIBACKGND =
        ";; Allow background access. STRONGLY RECOMMENDED TO BE SET = false, only useful for DEBUGGING.\n"
        ";;   If background access is granted, the device can be acquired at any time,\n"
        ";;   even when the associated window is not the active window.\n"
        ";;   The game will receive input even if not active window!!\n"
        ";; Set to true to allow background (replaces DISCL_FOREGROUND with DISCL_BACKGROUND)";
    const static constexpr char* COMMENT_INIDISDEADK =
        ";; Disable dead keys. When Skyrim doesn't have exclusive access to keyboard, dead keys stops working.\n"
        ";;   Users with keyboards layout like US-International or any other that uses dead keys may experience\n"
        ";;   difficulties to type characters like quotes in console. A way to fix this is effectively disable\n"
        ";;   dead keys in game.\n"
        ";; Set to true to disable dead keys.";
}  // namespace constants

namespace mdkf {
    class Config {
    private:
        explicit Config();
        bool disableWindowsKey = true;
        bool backgroundAccess = false;
        bool disableDeadKeys = false;
        bool debug = false;

    public:
        Config(Config&) = delete;
        Config& operator=(Config&&) = delete;
        void operator=(Config&) = delete;

        [[nodiscard]] static const Config& getInstance();

        [[nodiscard]] bool isDisableWindowsKey() const;

        [[nodiscard]] bool isBackgroundAccess() const;

        [[nodiscard]] bool isDisableDeadKeys() const;

        [[nodiscard]] bool isDebug() const;
    };
}  // namespace mdkf
