/////////////////////////////////////////////////////////////////////////////
// Name:        wxmr/artprov.h
// Purpose:     wxModRibbonArtProvider interface definition
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-26
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
 * \file
 * \brief wxModRibbonArtProvider interface definition.
 */


#ifndef _WXMR_ARTPROV_H_
#define _WXMR_ARTPROV_H_

// Forward declarations
class wxBorderlessFrameBase;
class wxFrame;
class wxSystemButtonsBase;

enum wxModRibbonArtSetting {
    wxMR_ART_FIRST_ROW_HEIGHT,
    wxMR_ART_SECOND_ROW_HEIGHT,
};

class wxModRibbonArtProvider {
public:
    virtual wxSystemButtonsBase* CreateSystemButtons(wxBorderlessFrameBase* frame) = 0;
    virtual void ResetMetrics(wxFrame* newFrame = nullptr) = 0;
    virtual int GetMetric(int id) = 0;
    virtual void SetMetric(int id, int newVal) = 0;
};

#endif
