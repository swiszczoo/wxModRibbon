/////////////////////////////////////////////////////////////////////////////
// Name:        ribbonframe.cpp
// Purpose:     wxModRibbonFrame class implementation
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-26
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


#include <wxmr/ribbonframe.h>

#include <wxbf/system_buttons.h>
#include <wxmr/artprov.h>
#include <wxmr/modribbon.h>

wxModRibbonFrame::~wxModRibbonFrame()
{
    delete m_ribbon;
}

bool wxModRibbonFrame::Create(wxModRibbon* ribbon, wxModRibbonArtProvider* artprov,
    wxWindow* parent, wxWindowID id, const wxString& title,
    const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    if (!wxBorderlessFrame::Create(parent, id, title, pos, size, style, name)) {
        return false;
    }

    m_sysBtns = artprov->CreateSystemButtons(this);

    m_ribbon = ribbon;
    m_ribbon->AttachUi(this, artprov);

    return true;
}

wxWindowPart wxModRibbonFrame::GetWindowPart(wxPoint mousePosition) const
{
    return m_sysBtns->GetWindowPart(mousePosition);
}

void wxModRibbonFrame::Init()
{
    m_ribbon = nullptr;
    m_sysBtns = nullptr;
}

