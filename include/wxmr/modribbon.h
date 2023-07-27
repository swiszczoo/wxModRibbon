/////////////////////////////////////////////////////////////////////////////
// Name:        wxmr/modribbon.h
// Purpose:     Main wxModRibbon header file
// Author:      Łukasz Świszcz
// Modified by:
// Created:     2023-07-24
// Copyright:   (c) Łukasz Świszcz
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

/**
 * \file
 * \brief Main wxModRibbon header file.
 */

#ifndef _WXMR_MODRIBBON_H_
#define _WXMR_MODRIBBON_H_

#include "artprov.h"
#include "cmdobserver.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <unordered_set>

 // Forward declarations
class wxModRibbon;
class wxModRibbonFrame;

#define wxMR_INVALID_COMMAND 0

class wxModRibbonCommand {
    friend class wxModRibbon;

public:
    template <typename T>
    wxModRibbonCommand(T id, const wxString& labelTitle, const wxString& labelDescription,
        const wxString& tooltipTitle, const wxString& tooltipDescription,
        const wxString& keytip)
    {
        m_id = static_cast<wxUint16>(id);
        m_labelTitle = labelDescription;
        m_tooltipTitle = tooltipTitle;
        m_tooltipDescription = tooltipDescription;
        m_keytip = keytip;
        m_enabled = true;
    }

    wxModRibbonCommand(const wxString& labelTitle, const wxString& labelDescription,
        const wxString& tooltipTitle, const wxString& tooltipDescription,
        const wxString& keytip)
        : wxModRibbonCommand(0, labelTitle, labelDescription,
            tooltipTitle, tooltipDescription, keytip) {}

    wxUint16 GetId() const
    {
        return m_id;
    }

    const wxString& GetLabelTitle() const
    {
        return m_labelTitle;
    }

    const wxString& GetLabelDescription() const
    {
        return m_labelDescription;
    }

    const wxString& GetTooltipTitle() const
    {
        return m_tooltipTitle;
    }

    const wxString& GetTooltipDescription() const
    {
        return m_tooltipDescription;
    }

    const wxString& GetKeytip() const
    {
        return m_keytip;
    }

    void SetLabelTitle(const wxString& newLabelTitle)
    {
        m_labelTitle = newLabelTitle;
        NotifyAll();
    }

    void SetLabelDescription(const wxString& newLabelDescription)
    {
        m_labelDescription = newLabelDescription;
        NotifyAll();
    }

    void SetTooltipTitle(const wxString& newTooltipTitle)
    {
        m_tooltipTitle = newTooltipTitle;
        NotifyAll();
    }

    void SetTooltipDescription(const wxString& newTooltipDescription)
    {
        m_tooltipDescription = newTooltipDescription;
        NotifyAll();
    }

    void SetKeytip(const wxString& newKeytip)
    {
        m_keytip = newKeytip;
        NotifyAll();
    }

    void Enable(bool enable = true)
    {
        m_enabled = enable;
        NotifyAll();
    }

    void Disable()
    {
        m_enabled = false;
        NotifyAll();
    }

    bool IsEnabled() const
    {
        return m_enabled;
    }


private:
    wxUint16 m_id;
    wxString m_labelTitle;
    wxString m_labelDescription;
    wxString m_tooltipTitle;
    wxString m_tooltipDescription;
    wxString m_keytip;
    bool m_enabled;

    std::unordered_set<wxModRibbonCommandObserver*> m_observers;

    void SetId(wxUint16 newId)
    {
        m_id = newId;
    }

    void NotifyAll()
    {
        if (m_observers.empty()) {
            return;
        }

        for (wxModRibbonCommandObserver* observerPtr : m_observers) {
            observerPtr->Notify();
        }
    }
};

class wxModRibbon {
public:
    wxModRibbon();

    wxUint16 RegisterCommand(const wxModRibbonCommand& command);

    wxModRibbonCommand* GetCommand(wxUint16 commandId) const
    {
        return m_commands[commandId].get();
    }

    wxModRibbonArtProvider* GetArtProvider() const { return m_artprov.get(); }

    void AttachUi(wxModRibbonFrame* frame, wxModRibbonArtProvider* artprov);

private:
    wxUint16 m_lastId;
    std::unique_ptr<wxModRibbonCommand> m_commands[1 << 16];
    wxModRibbonFrame* m_frame;
    std::unique_ptr<wxModRibbonArtProvider> m_artprov;

    wxUint16 AllocNextCommandId();
};

#endif
