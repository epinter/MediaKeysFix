#include "FakeIDirectInput8.h"
#include "FakeIDirectInputDevice8.h"

namespace mdkf {
    HRESULT WINAPI FakeIDirectInput8::QueryInterface(REFIID riid, LPVOID *ppvObj) noexcept {
        return real->QueryInterface(riid, ppvObj);
    }

    ULONG WINAPI FakeIDirectInput8::AddRef(void) noexcept {
        refs++;
        return refs;
    }

    ULONG WINAPI FakeIDirectInput8::Release(void) noexcept {
        refs--;

        if (!refs) {
            real->Release();
            delete this;
            return 0;
        } else {
            return refs;
        }
    }

    HRESULT WINAPI FakeIDirectInput8::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback,
                                                          LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags,
                                                          LPVOID pvRefData) noexcept {
        return real->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
    }

    HRESULT WINAPI FakeIDirectInput8::CreateDevice(REFGUID rguid, IDirectInputDevice8A **lpDirectInputDevice,
                                                      LPUNKNOWN pUnkOuter) noexcept {

        if (rguid != GUID_SysKeyboard && rguid != GUID_SysMouse) {
            return real->CreateDevice(rguid, lpDirectInputDevice, pUnkOuter);
        } else {
            IDirectInputDevice8A *dev;

            HRESULT hr = real->CreateDevice(rguid, &dev, pUnkOuter);
            if (hr != DI_OK)
                return hr;

            *lpDirectInputDevice =
                new FakeIDirectInputDevice8(dev, (rguid == GUID_SysKeyboard) ? FakeDeviceType_Keyboard : FakeDeviceType_Mouse);

            return hr;
        }
    }

    HRESULT WINAPI FakeIDirectInput8::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef,
                                                     DWORD dwFlags) noexcept {
        return real->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInput8::EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat,
                                                                LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef,
                                                                DWORD dwFlags) noexcept {
        return real->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInput8::FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance) noexcept {
        return real->FindDevice(rguidClass, ptszName, pguidInstance);
    }

    HRESULT WINAPI FakeIDirectInput8::GetDeviceStatus(REFGUID rguidInstance) noexcept {
        return real->GetDeviceStatus(rguidInstance);
    }

    HRESULT WINAPI FakeIDirectInput8::Initialize(HINSTANCE hinst, DWORD dwVersion) noexcept {
        return real->Initialize(hinst, dwVersion);
    }

    HRESULT WINAPI FakeIDirectInput8::RunControlPanel(HWND hwndOwner, DWORD dwFlags) noexcept {
        return real->RunControlPanel(hwndOwner, dwFlags);
    }
}  // namespace mdkf
