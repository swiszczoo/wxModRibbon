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
class wxSystemButtonsBase;

class wxModRibbonArtProvider {
public:
    virtual wxSystemButtonsBase* CreateSystemButtons(wxBorderlessFrameBase* frame) = 0;
};

#endif
