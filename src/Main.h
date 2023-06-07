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

namespace constants {
    // cooperativelevel
    static constexpr SKSE::stl::nttp::string PATTERN_CHECK_DWFLAGS = "41 B8 15 00 00 00 48 8B D0 FF";
    static constexpr int INITDINPUT_SE = 67471;  // 1.5.97 = C1A060
    static constexpr int INITDINPUT_AE = 68781;  // 1.6.640 = C52D00
    static constexpr int DWFLAGS_INST_OFFSET_SE = 0x55;
    static constexpr int DWFLAGS_INST_OFFSET_AE = 0x55;
    static constexpr uint32_t DIFLAGS_DEFAULT = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
    static constexpr uint32_t DIFLAGS_BACKGROUND = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
    // tounicode
    static constexpr SKSE::stl::nttp::string PATTERN_CHECK_TOUNICODE = "FF 15 ?? ?? ?? ?? 83 F8 01 75";
    static constexpr int PROCESSINPUT_SE = 67472;  // 1.5.97 = C1A130
    static constexpr int PROCESSINPUT_AE = 68782;  // 1.6.640 = C52DD0
    static constexpr int TOUNICODECALL_OFFSET_SE = 0x20D;
    static constexpr int TOUNICODECALL_OFFSET_AE = 0x2CB;
}  // namespace constants

namespace mdkf {
    void load();
    void patchCooperativeLevel();
    void writeDwFlags(int dwFlags);
    void initializeTounicodeHook();
    void hookDInputCreate();

    int toUnicode(UINT wVirtKey, UINT wScanCode, const BYTE *lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags);
}  // namespace mdkf
