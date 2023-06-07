/*
Copyright (c) 2023 Emerson Pinter

This file is part of Media Keys Fix SKSE.

Foobar is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/

#include "Main.h"

#include "Config.h"
#include "dinput/FakeIDirectInput8.h"

using namespace constants;

typedef HRESULT(__stdcall* CreateDInputProc)(HINSTANCE, DWORD, REFIID, LPVOID, LPUNKNOWN);
static CreateDInputProc directInputCreateReal;

namespace mdkf {
    void load() {
        if (Config::getInstance().isDebug()) { //hooks DirectInput8Create to log SetCooperativeLevel dwFlags for keyboard and mouse
            hookDInputCreate();
        }

        patchCooperativeLevel();

        if (Config::getInstance().isDisableDeadKeys()) {
            initializeTounicodeHook();
        }
    }

    static HRESULT WINAPI directInput8CreateInstance(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut,
                                                       LPUNKNOWN punkOuter) {
        IDirectInput8A* directInput;
        HRESULT result = directInputCreateReal(hinst, dwVersion, riidltf, &directInput, punkOuter);
        if (result != DI_OK)
            return result;

        *((IDirectInput8A**)ppvOut) = new FakeIDirectInput8(directInput);

        return DI_OK;
    }

    void hookDInputCreate() {
        uintptr_t iatAddress = (uintptr_t)SKSE::GetIATAddr("dinput8.dll", "DirectInput8Create");

        directInputCreateReal = (CreateDInputProc) * (uintptr_t*)iatAddress;

        REL::safe_write(iatAddress, (uintptr_t)directInput8CreateInstance);

        logger::info("DirectInput8Create hooked");
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
