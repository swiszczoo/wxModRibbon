/////////////////////////////////////////////////////////////////////////////
// Name:        metroartprov.cpp
// Purpose:     wxModRibbonMetroArtProvider class implementation
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-26
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <wxmr/metroartprov.h>

#include <wxbf/system_buttons.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/frame.h>
#endif

wxModRibbonMetroArtProvider::wxModRibbonMetroArtProvider(wxFrame* frame)
{
    m_frame = frame;
    m_firstRowHeight = 30;
    m_secondRowHeight = 24;
}

void wxModRibbonMetroArtProvider::ResetMetrics(wxFrame* newFrame)
{
    if (newFrame) {
        m_frame = newFrame;
    }

    int baseFontHeight = m_frame->GetFont().GetPixelSize().y;

    m_firstRowHeight = baseFontHeight * 5 / 2;
    m_secondRowHeight = baseFontHeight * 2;
}

wxSystemButtonsBase*
wxModRibbonMetroArtProvider::CreateSystemButtons(wxBorderlessFrameBase* frame)
{
    return wxSystemButtonsFactory::CreateSystemButtons(frame);
}

int wxModRibbonMetroArtProvider::GetMetric(int id)
{
    switch (id) {
    case wxMR_ART_FIRST_ROW_HEIGHT:     return m_firstRowHeight;
    case wxMR_ART_SECOND_ROW_HEIGHT:    return m_secondRowHeight;
    default: wxFAIL_MSG(wxT("Invalid Metric Ordinal")); break;
    }

    return 0;
}

void wxModRibbonMetroArtProvider::SetMetric(int id, int newVal)
{
    switch (id) {
    case wxMR_ART_FIRST_ROW_HEIGHT:     m_firstRowHeight = newVal; break;
    case wxMR_ART_SECOND_ROW_HEIGHT:    m_secondRowHeight = newVal; break;
    default: wxFAIL_MSG(wxT("Invalid Metric Ordinal")); break;
    }
}
