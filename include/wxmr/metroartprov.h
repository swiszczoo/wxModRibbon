/////////////////////////////////////////////////////////////////////////////
// Name:        wxmr/metroartprov.h
// Purpose:     wxModRibbonMetroArtProvider class
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-26
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
 * \file
 * \brief wxModRibbonMetroArtProvider class.
 */


#ifndef _WXMR_METROARTPROV_H_
#define _WXMR_METROARTPROV_H_

#include "artprov.h"

class wxModRibbonMetroArtProvider : public wxModRibbonArtProvider {
public:
    wxSystemButtonsBase* CreateSystemButtons(wxBorderlessFrameBase* frame) override;
};

#endif
