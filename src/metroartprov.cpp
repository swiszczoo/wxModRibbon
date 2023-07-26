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

wxSystemButtonsBase*
wxModRibbonMetroArtProvider::CreateSystemButtons(wxBorderlessFrameBase* frame)
{
    return wxSystemButtonsFactory::CreateSystemButtons(frame);
}
