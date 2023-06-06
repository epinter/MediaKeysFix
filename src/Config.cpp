#include <Config.h>
/*
Copyright (c) 2023 Emerson Pinter

This file is part of Media Keys Fix SKSE.

Foobar is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

using namespace constants;

namespace mdkf {
    Config::Config() {
        CSimpleIniA ini;
        ini.SetQuotes(true);
        ini.SetAllowKeyOnly(false);
        ini.SetUnicode(true);
        ini.SetMultiKey(false);
        std::string fileName = std::string("Data\\SKSE\\Plugins\\").append(CONFIG_FILE);

        bool save = false;
        if (ini.LoadFile(fileName.c_str()) == 0) {
            disableWindowsKey = ini.GetBoolValue(INI_SECTION, OPT_INIDISWINKEY, disableWindowsKey);
            backgroundAccess = ini.GetBoolValue(INI_SECTION, OPT_INIBACKGN, backgroundAccess);
            disableDeadKeys = ini.GetBoolValue(INI_SECTION, OPT_INIDISDEADK, disableDeadKeys);
        } else {
            logger::error("Can't open config file '{}'. Trying to create a new.", CONFIG_FILE);
        }

        if (!ini.KeyExists(INI_SECTION, OPT_INIDISWINKEY)) {
            ini.SetBoolValue(INI_SECTION, OPT_INIDISWINKEY, disableWindowsKey, COMMENT_INIWINKEY, true);
            save = true;
        }
        if (!ini.KeyExists(INI_SECTION, OPT_INIDISDEADK)) {
            ini.SetBoolValue(INI_SECTION, OPT_INIDISDEADK, disableDeadKeys, COMMENT_INIDISDEADK, true);
            save = true;
        }
        if (!ini.KeyExists(INI_SECTION, OPT_INIBACKGN)) {
            ini.SetBoolValue(INI_SECTION, OPT_INIBACKGN, backgroundAccess, COMMENT_INIBACKGND, true);
            save = true;
        }

        if (save) {
            ini.SaveFile(fileName.c_str());
        }

        logger::info("Config: {}='{}'; {}='{}'; {}='{}';", OPT_INIDISWINKEY, disableWindowsKey, OPT_INIBACKGN, backgroundAccess,
                     OPT_INIDISDEADK, disableDeadKeys);
    }

    const Config& Config::getInstance() {
        static Config instance;
        return instance;
    }

    [[nodiscard]] bool Config::isDisableWindowsKey() const {
        return disableWindowsKey;
    }

    [[nodiscard]] bool Config::isBackgroundAccess() const {
        return backgroundAccess;
    }

    [[nodiscard]] bool Config::isDisableDeadKeys() const {
        return disableDeadKeys;
    }
}  // namespace mdkf
