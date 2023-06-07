#include "FakeIDirectInputDevice8.h"

namespace mdkf {
    HRESULT WINAPI FakeIDirectInputDevice8::QueryInterface(REFIID riid, LPVOID* ppvObj) {
        return realDevice->QueryInterface(riid, ppvObj);
    }

    ULONG WINAPI FakeIDirectInputDevice8::AddRef(void) {
        refs++;
        return refs;
    }

    ULONG WINAPI FakeIDirectInputDevice8::Release(void) {
        refs--;

        if (!refs) {
            realDevice->Release();
            delete this;
            return 0;
        } else {
            return refs;
        }
    }

    HRESULT WINAPI FakeIDirectInputDevice8::Acquire() {
        return realDevice->Acquire();
    }

    HRESULT WINAPI FakeIDirectInputDevice8::BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags) {
        return realDevice->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff,
                                                            LPUNKNOWN punkOuter) {
        return realDevice->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback,
                                                                        LPVOID pvRef, DWORD fl) {
        return realDevice->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType) {
        return realDevice->EnumEffects(lpCallback, pvRef, dwEffType);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec,
                                                                 LPVOID pvRef, DWORD dwFlags) {
        return realDevice->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef,
                                                           DWORD dwFlags) {
        return realDevice->EnumObjects(lpCallback, pvRef, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::Escape(LPDIEFFESCAPE pesc) {
        return realDevice->Escape(pesc);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
        return realDevice->GetCapabilities(lpDIDevCaps);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut,
                                                             DWORD dwFlags) {
        return realDevice->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetDeviceInfo(LPDIDEVICEINSTANCE pdidi) {
        return realDevice->GetDeviceInfo(pdidi);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetDeviceState(DWORD cbData, LPVOID lpvData) {
        return realDevice->GetDeviceState(cbData, lpvData);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetEffectInfo(LPDIEFFECTINFOA pdei, REFGUID rguid) {
        return realDevice->GetEffectInfo(pdei, rguid);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetForceFeedbackState(LPDWORD pdwOut) {
        return realDevice->GetForceFeedbackState(pdwOut);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader) {
        return realDevice->GetImageInfo(lpdiDevImageInfoHeader);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow) {
        return realDevice->GetObjectInfo(pdidoi, dwObj, dwHow);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph) {
        return realDevice->GetProperty(rguidProp, pdiph);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid) {
        return realDevice->Initialize(hinst, dwVersion, rguid);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::Poll() {
        return realDevice->Poll();
    }

    HRESULT WINAPI FakeIDirectInputDevice8::RunControlPanel(HWND hwndOwner, DWORD dwFlags) {
        return realDevice->RunControlPanel(hwndOwner, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut,
                                                              DWORD fl) {
        return realDevice->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::SendForceFeedbackCommand(DWORD dwFlags) {
        return realDevice->SendForceFeedbackCommand(dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::SetActionMap(LPDIACTIONFORMATA lpdiActionFormat, LPCSTR lptszUserName,
                                                            DWORD dwFlags) {
        return realDevice->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::SetCooperativeLevel(HWND hwnd, DWORD dwFlags) {
        std::string deviceTypeStr;
        if (realType == FakeDeviceType_Keyboard) {
            deviceTypeStr = "keyboard";
        } else if (realType == FakeDeviceType_Mouse) {
            deviceTypeStr = "mouse";
        } else {
            deviceTypeStr = "other";
        }
        logger::info("setcooperativelevel called deviceType:'{}'(0x{:08X}), dwFlags:0x{:02X}, ", deviceTypeStr, realType,
                     dwFlags);
        return realDevice->SetCooperativeLevel(hwnd, dwFlags);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::SetDataFormat(LPCDIDATAFORMAT lpdf) {
        return realDevice->SetDataFormat(lpdf);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::SetEventNotification(HANDLE hEvent) {
        return realDevice->SetEventNotification(hEvent);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph) {
        return realDevice->SetProperty(rguidProp, pdiph);
    }

    HRESULT WINAPI FakeIDirectInputDevice8::Unacquire() {
        return realDevice->Unacquire();
    }

    HRESULT WINAPI FakeIDirectInputDevice8::WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft,
                                                                 DWORD dwFlags) {
        return realDevice->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
    }
}  // namespace mdkf