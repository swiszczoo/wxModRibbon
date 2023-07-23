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

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
};

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show();
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "wxModRibbon sample")
{
    SetSize(FromDIP(wxSize(600, 400)));
}

wxIMPLEMENT_APP(MyApp);

