#pragma once
/*
Copyright (c) 2023 Emerson Pinter

This file is part of Media Keys Fix. Licensed under LGPL-3.0-or-later <https://www.gnu.org/licenses/lgpl-3.0.txt>.
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

    int toUnicode(UINT wVirtKey, UINT wScanCode, const BYTE *lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags);
}  // namespace mdkf
