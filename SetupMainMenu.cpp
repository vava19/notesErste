#include "App.hpp"
#include "MainFrame.hpp"


void MainFrame::OnSomeAction(wxCommandEvent &)
{
    wxMessageBox("Some Action!");
}

void MainFrame::SetupMainMenu()
    
    
{
    wxMenuBar* menuBar = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW);
    fileMenu->Append(wxID_OPEN);
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_SAVEAS);

    wxMenu* editMenu = new wxMenu();

    editMenu->Append(wxID_UNDO);
    editMenu->Append(wxID_REDO);
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT);
    editMenu->Append(wxID_COPY);
    editMenu->Append(wxID_PASTE);

    wxMenu* customMenu = new wxMenu();

    this->Bind(wxEVT_MENU, &MainFrame::OnSomeAction, this,
               customMenu->Append(wxID_ANY, "Some &Action...\tCtrl-Alt-A")->GetId());

    customMenu->AppendSeparator();
    customMenu->AppendCheckItem(wxID_ANY, "Check Item &One\tCtrl-1");
    customMenu->AppendCheckItem(wxID_ANY, "Check Item &Two\tCtrl-2");
    customMenu->AppendSeparator();

    wxMenu *customMenuOptionsSubmenu = new wxMenu();

    customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option One");
    customMenuOptionsSubmenu->Check(
        customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option Two")->GetId(),
        true);
    customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option Three");

    customMenu->AppendSubMenu(customMenuOptionsSubmenu, "&Options");

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(customMenu, "&Custom");

    SetMenuBar(menuBar);
}


