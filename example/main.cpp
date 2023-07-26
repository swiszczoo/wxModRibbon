/////////////////////////////////////////////////////////////////////////////
// Name:        example/main.cpp
// Purpose:     wxModRibbon usage sample
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-24
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/wxprec.h>
#ifndef WXPREC
#include <wx/wx.h>
#endif

#include <wx/dynlib.h>

#include <wxmr/wxmr.h>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxModRibbonFrame
{
public:
    MyFrame();
};

static void EnableHiDpi()
{
#if (defined _WIN32 && WINVER >= 0x0605)
    typedef BOOL(WINAPI* PGNSI)(DPI_AWARENESS_CONTEXT);

    wxDynamicLibrary dll("user32.dll");
    PGNSI spdac = (PGNSI)dll.GetSymbol("SetProcessDpiAwarenessContext");
    if (spdac) {
        spdac(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    }
#endif
}

bool MyApp::OnInit()
{
    EnableHiDpi();
    wxInitAllImageHandlers();

    MyFrame* frame = new MyFrame();
    frame->Show();
    return true;
}

MyFrame::MyFrame()
    : wxModRibbonFrame(new wxModRibbon(), new wxModRibbonMetroArtProvider(),
        nullptr, wxID_ANY, "wxModRibbon sample")
{
    SetBackgroundColour(wxColour(255, 255, 255));
    SetSize(FromDIP(wxSize(1000, 800)));

    // You can also use wxBorderlessFrame calls here:
    SetBorderColour(wxColour(31, 29, 161));
    SetBorderThickness(1);

    CenterOnScreen();
}

wxIMPLEMENT_APP(MyApp);

