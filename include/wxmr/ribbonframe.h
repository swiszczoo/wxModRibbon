/////////////////////////////////////////////////////////////////////////////
// Name:        wxmr/ribbonframe.h
// Purpose:     wxModRibbonFrame class
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-26
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
 * \file
 * \brief wxModRibbonFrame class.
 */

#ifndef _WXMR_RIBBONFRAME_H_
#define _WXMR_RIBBONFRAME_H_

#include <wxbf/borderless_frame.h>

 // Forward declarations
class wxModRibbonArtProvider;
class wxModRibbon;
class wxSystemButtonsBase;

class wxModRibbonFrame : public wxBorderlessFrame
{
public:
    wxModRibbonFrame() : wxBorderlessFrame() { Init(); }

    wxModRibbonFrame(wxModRibbon* ribbon,
        wxModRibbonArtProvider* artprov,
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxASCII_STR(wxFrameNameStr))
        : wxBorderlessFrame()
    {
        Init();
        Create(ribbon, artprov, parent, id, title, pos, size, style, name);
    }

    ~wxModRibbonFrame();

    bool Create(wxModRibbon* ribbon,
        wxModRibbonArtProvider* artprov,
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxASCII_STR(wxFrameNameStr));

    wxModRibbon* GetRibbon() const { return m_ribbon; }

    void LayoutRibbon();

protected:
    wxWindowPart GetWindowPart(wxPoint mousePosition) const override;
    void OnNcMouse(wxMouseEvent& event);
    void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);

private:
    wxModRibbon* m_ribbon;
    wxSystemButtonsBase* m_sysBtns;
    int m_titlebarHeight;
    bool m_titlebarRightDown;

    void Init();
};

#endif
