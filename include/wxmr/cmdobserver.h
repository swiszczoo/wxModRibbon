/////////////////////////////////////////////////////////////////////////////
// Name:        cmdobserver.h
// Purpose:     wxModRibbonCommandObserver interface definition
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-24
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
 * \file
 * \brief wxModRibbonCommandObserver interface definition.
 */

#ifndef _WXMR_CMDOBSERVER_H_
#define _WXMR_CMDOBSERVER_H_

class wxModRibbonCommandObserver
{
public:
    virtual void Notify() = 0;
};

#endif
