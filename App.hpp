

#ifndef APP_HPP
#define APP_HPP

#include <wx/wx.h>   // need for ineritance App from wxApp

class App : public wxApp {
public:
  virtual bool OnInit();  //ili bez virtual
};

#endif  // APP_HPP
