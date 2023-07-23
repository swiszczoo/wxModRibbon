/////////////////////////////////////////////////////////////////////////////
// Name:        modribbon.cpp
// Purpose:     Main wxModRibbon implementation file
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-24
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


#include <wxmr/modribbon.h>

#include <wx/log.h>

wxModRibbon::wxModRibbon()
    : m_lastId(0)
{
}

wxUint16 wxModRibbon::RegisterCommand(const wxModRibbonCommand& command)
{
    auto copy = std::make_unique<wxModRibbonCommand>(command);

    if (!command.GetId()) {
        wxUint16 id = AllocNextCommandId();
        copy->SetId(id);
    }

    wxUint16 id = copy->GetId();
    if (!m_commands[id]) {
        m_commands[id] = std::move(copy);
        return id;
    }

    return wxMR_INVALID_COMMAND;
}

wxUint16 wxModRibbon::AllocNextCommandId()
{
    while (m_commands[++m_lastId]) {
        if (!m_lastId) {
            wxLogError("wxModRibbon: cannot allocate a new id for command!");
            break;
        }
    }
    return m_lastId;
}
