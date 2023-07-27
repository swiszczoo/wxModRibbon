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
    m_sysBtns->SetButtonSize(
        wxSize(-1, ToDIP(artprov->GetMetric(wxMR_ART_FIRST_ROW_HEIGHT))));

    m_ribbon = ribbon;
    m_ribbon->AttachUi(this, artprov);

    Bind(wxEVT_NC_RIGHT_DOWN, &wxModRibbonFrame::OnNcMouse, this);
    Bind(wxEVT_NC_RIGHT_UP, &wxModRibbonFrame::OnNcMouse, this);
    Bind(wxEVT_RIGHT_UP, &wxModRibbonFrame::OnNcMouse, this);
    Bind(wxEVT_MOUSE_CAPTURE_LOST, &wxModRibbonFrame::OnMouseCaptureLost, this);
    return true;
}

void wxModRibbonFrame::LayoutRibbon()
{
    wxModRibbonArtProvider* artprov = m_ribbon->GetArtProvider();
    m_sysBtns->SetButtonSize(
        wxSize(-1, ToDIP(artprov->GetMetric(wxMR_ART_FIRST_ROW_HEIGHT))));
    m_titlebarHeight = artprov->GetMetric(wxMR_ART_FIRST_ROW_HEIGHT)
        + artprov->GetMetric(wxMR_ART_SECOND_ROW_HEIGHT);
}

wxWindowPart wxModRibbonFrame::GetWindowPart(wxPoint mousePosition) const
{
    wxWindowPart part = m_sysBtns->GetWindowPart(mousePosition);
    if (part != wxWP_CLIENT_AREA) {
        return part;
    }

    wxPoint windowPosition = ScreenToClient(mousePosition);
    if (windowPosition.y < m_titlebarHeight && GetRect().Contains(mousePosition)) {
        return wxWP_TITLEBAR;
    }

    return wxWP_CLIENT_AREA;
}

void wxModRibbonFrame::OnNcMouse(wxMouseEvent& event)
{
    if (event.GetEventType() == wxEVT_NC_RIGHT_DOWN) {
        wxWindowPart part = GetWindowPart(wxGetMousePosition());
        if (part == wxWP_TITLEBAR) {
            m_titlebarRightDown = true;
            CaptureMouse();
        }
    }
    else if (event.GetEventType() == wxEVT_NC_RIGHT_UP || event.RightUp()) {
        wxWindowPart part = GetWindowPart(wxGetMousePosition());
        bool hasCapture = HasCapture();
        if (hasCapture) {
            ReleaseMouse();
        }

        if (part == wxWP_TITLEBAR && hasCapture) {
            PopupSystemMenu();
            m_titlebarRightDown = false;
        }
    }

    event.Skip();
}

void wxModRibbonFrame::OnMouseCaptureLost(wxMouseCaptureLostEvent&)
{
    m_titlebarRightDown = false;
}

void wxModRibbonFrame::Init()
{
    m_ribbon = nullptr;
    m_sysBtns = nullptr;
    m_titlebarHeight = 30;
    m_titlebarRightDown = false;
}

