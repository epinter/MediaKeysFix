#pragma once

namespace mdkf {
    enum {
        FakeDeviceType_Keyboard = 1,
        FakeDeviceType_Mouse
    };
    static const GUID GUID_SysMouse = {0x6F1D2B60, 0xD5A0, 0x11CF, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
    static const GUID GUID_SysKeyboard = {0x6F1D2B61, 0xD5A0, 0x11CF, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};

    class FakeIDirectInputDevice8 : public IDirectInputDevice8 {
    private:
        IDirectInputDevice8* realDevice;
        DWORD realType;
        ULONG refs;

    public:
        FakeIDirectInputDevice8(IDirectInputDevice8* device, DWORD type) : realDevice(device), realType(type), refs(1) {
        }
        HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj);
        ULONG WINAPI AddRef(void);
        ULONG WINAPI Release(void);
        HRESULT WINAPI Acquire();
        HRESULT WINAPI BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags);
        HRESULT WINAPI CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter);
        HRESULT WINAPI EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl);
        HRESULT WINAPI EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType);
        HRESULT WINAPI EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags);
        HRESULT WINAPI EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
        HRESULT WINAPI Escape(LPDIEFFESCAPE pesc);
        HRESULT WINAPI GetCapabilities(LPDIDEVCAPS lpDIDevCaps);
        HRESULT WINAPI GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags);
        HRESULT WINAPI GetDeviceInfo(LPDIDEVICEINSTANCE pdidi);
        HRESULT WINAPI GetDeviceState(DWORD cbData, LPVOID lpvData);
        HRESULT WINAPI GetEffectInfo(LPDIEFFECTINFOA pdei, REFGUID rguid);
        HRESULT WINAPI GetForceFeedbackState(LPDWORD pdwOut);
        HRESULT WINAPI GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader);
        HRESULT WINAPI GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow);
        HRESULT WINAPI GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph);
        HRESULT WINAPI Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid);
        HRESULT WINAPI Poll();
        HRESULT WINAPI RunControlPanel(HWND hwndOwner, DWORD dwFlags);
        HRESULT WINAPI SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl);
        HRESULT WINAPI SendForceFeedbackCommand(DWORD dwFlags);
        HRESULT WINAPI SetActionMap(LPDIACTIONFORMATA lpdiActionFormat, LPCSTR lptszUserName, DWORD dwFlags);
        HRESULT WINAPI SetCooperativeLevel(HWND hwnd, DWORD dwFlags);
        HRESULT WINAPI SetDataFormat(LPCDIDATAFORMAT lpdf);
        HRESULT WINAPI SetEventNotification(HANDLE hEvent);
        HRESULT WINAPI SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph);
        HRESULT WINAPI Unacquire();
        HRESULT WINAPI WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags);
    };
}  // namespace mdkf
