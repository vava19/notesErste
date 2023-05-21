
#include "App.hpp"
#include <wx/wx.h>
#include "MainFrame.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
  MainFrame* mainFrame = new MainFrame("Quick Notes");
  mainFrame->SetClientSize(800, 600);
  mainFrame->Center();
  mainFrame->Show();
  return true;
}


