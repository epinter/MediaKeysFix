#pragma once

namespace mdkf {
    class FakeIDirectInput8 : public IDirectInput8A {
    private:
        IDirectInput8A *real;
        ULONG refs;

    public:
        FakeIDirectInput8(IDirectInput8A *realDirectInput) : real(realDirectInput), refs(1) {};
        HRESULT WINAPI QueryInterface(REFIID riid, LPVOID *ppvObj) noexcept;
        ULONG WINAPI AddRef(void) noexcept;
        ULONG WINAPI Release(void) noexcept;
        HRESULT WINAPI ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams,
                                           DWORD dwFlags, LPVOID pvRefData) noexcept;
        HRESULT WINAPI CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lpDirectInputDevice, LPUNKNOWN pUnkOuter) noexcept;
        HRESULT WINAPI EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags) noexcept;
        HRESULT WINAPI EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat,
                                                 LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags) noexcept;
        HRESULT WINAPI FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance) noexcept;
        HRESULT WINAPI GetDeviceStatus(REFGUID rguidInstance) noexcept;
        HRESULT WINAPI Initialize(HINSTANCE hinst, DWORD dwVersion) noexcept;
        HRESULT WINAPI RunControlPanel(HWND hwndOwner, DWORD dwFlags) noexcept;
    };
}
