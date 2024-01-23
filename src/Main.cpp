/*
Copyright (c) 2023 Emerson Pinter

This file is part of Media Keys Fix. Licensed under LGPL-3.0-or-later <https://www.gnu.org/licenses/lgpl-3.0.txt>.
*/

#include "Main.h"

#include "Config.h"

using namespace constants;

namespace mdkf {
    void load() {
        patchCooperativeLevel();
        if (Config::getInstance().isDisableDeadKeys()) {
            initializeTounicodeHook();
        }
    }

    void patchCooperativeLevel() {
        uint32_t newFlags = Config::getInstance().isBackgroundAccess() ? DIFLAGS_BACKGROUND : DIFLAGS_DEFAULT;

        if (Config::getInstance().isDisableWindowsKey()) {
            newFlags |= DISCL_NOWINKEY;  // disable windows key
        }
        writeDwFlags(newFlags);
    }

    void writeDwFlags(int newFlags) {
        REL::RelocationID initDirectInputDevice = REL::RelocationID(INITDINPUT_SE, INITDINPUT_AE);
        int instructionOffset = REL::Relocate(DWFLAGS_INST_OFFSET_SE, DWFLAGS_INST_OFFSET_AE);

        if (REL::make_pattern<PATTERN_CHECK_DWFLAGS>().match(initDirectInputDevice.address() + instructionOffset)) {
            int dwFlagsOffset = instructionOffset + 2;  // instruction len = 2 bytes

            logger::info("SetCooperativeLevel dwFlags found at address 0x{:08X}, setting to 0x{:02X}",
                         initDirectInputDevice.offset() + dwFlagsOffset, newFlags);
            REL::safe_write(initDirectInputDevice.address() + dwFlagsOffset, newFlags);
        } else {
            logger::info("DwFlags patch failed, address didn't match. Fix not applied.");
        }
    }

    REL::Relocation<decltype(toUnicode)> originalToUnicode;

    void initializeTounicodeHook() {
        uintptr_t call = REL::RelocationID(PROCESSINPUT_SE, PROCESSINPUT_AE).address() +
                         REL::Relocate(TOUNICODECALL_OFFSET_SE, TOUNICODECALL_OFFSET_AE);

        if (REL::make_pattern<PATTERN_CHECK_TOUNICODE>().match(call)) {
            logger::info("Disabling dead keys.");
            auto& trampoline = SKSE::GetTrampoline();
            trampoline.create(64);

            originalToUnicode = *reinterpret_cast<uintptr_t*>(trampoline.write_call<6>(call, toUnicode));
        } else {
            logger::info("Unable to write trampoline, address didn't match. Dead keys not disabled.");
        }
    }

    int toUnicode(UINT wVirtKey, UINT wScanCode, const BYTE* lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags) {
        int ret = originalToUnicode(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags);
        return ret > 0 ? 1 : ret;
    }
}  // namespace mdkf
