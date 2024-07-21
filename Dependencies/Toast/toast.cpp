/*
    A last minute implementation of mohabouje's WinToast library. 
    I took the link below, and changed a bit to make the function makeToastNotif
    https://github.com/mohabouje/WinToast/blob/master/example/console-example/main.cpp
    All credit for this goes to Mohammed Boujemaoui (github.com/mohabouje)
*/



#include "../../MU.h"

using namespace WinToastLib;

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const {
    }

    void toastActivated(int actionIndex) const {
    }

    void toastDismissed(WinToastDismissalReason state) const {
        
    }

    void toastFailed() const {

    }
};

INT makeToastNotif
    (LPWSTR Head, LPWSTR Body) 
{

    int argc = 0;
    LPWSTR* argv;

    LPWSTR appName = L"wtf",
        appUserModelID = L"stwtf",
        text = NULL,
        imagePath = L"%userprofile%\\Downloads\\a.png",
        attribute = Body;

    std::vector<std::wstring> actions;
    INT64 expiration = 0;

    bool onlyCreateShortcut = false;
    WinToastTemplate::AudioOption audioOption = WinToastTemplate::AudioOption::Default;

    WinToast::instance()->setAppName(appName);
    WinToast::instance()->setAppUserModelId(appUserModelID);

    if (onlyCreateShortcut) {
        if (imagePath || text || actions.size() > 0 || expiration) {
            return 9;
        }
        enum WinToast::ShortcutResult result = WinToast::instance()->createShortcut();
        return result ? 16 + result : 0;
    }

    if (!text)
        text = Head;

    WinToast::instance()->initialize();

    bool withImage = (imagePath != NULL);
    WinToastTemplate templ(withImage ? WinToastTemplate::ImageAndText02 : WinToastTemplate::Text02);
    templ.setTextField(text, WinToastTemplate::FirstLine);
    templ.setAudioOption(audioOption);
    templ.setAttributionText(attribute);

    for (auto const& action : actions)
        templ.addAction(action);
    if (expiration)
        templ.setExpiration(expiration);
    if (withImage)
        templ.setImagePath(imagePath);


    WinToast::instance()->showToast(templ, new CustomHandler());
    

    Sleep(expiration ? (DWORD)expiration + 1000 : 2000);
}

