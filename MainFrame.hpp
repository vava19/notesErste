#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/dataview.h>
//#include "SetupMainMenu.hpp"
#include "drawingcanvas.h"


class MainFrame : public wxFrame 

{
    public: 
      MainFrame(const wxString& title);

      private:
      void CreateControls();
      void BindEventHandlers();
      void AddSavedTasks();

      void OnAddButtonClicked(wxCommandEvent& event);
      void OnInputEnter(wxCommandEvent& event);
      void OnListKeyDown(wxKeyEvent& event);
      void OnClearButtonClicked(wxCommandEvent& event);  // why not keyEvent  ??
      void OnWindowClosed(wxCloseEvent& event); // is called when window is closed
      void DeleteNote(wxCommandEvent& event);  // added
      void OnListItemClicked(wxCommandEvent &event);  // added  file.txt , not works
      void OnMouseEvent(wxMouseEvent& event);

      void SetupMainMenu();   // added   --> za menu
      void OnSomeAction(wxCommandEvent &);  // added   --> za menu

     



      // helper method
      void AddTaskFromInput();
      void DeleteSelectedTask();
      void MoveSelectedTask(int offset);  // either -1   or +1   => depends task moved up/down
      void SwapTasks(int i, int j);  // index i  , index j
      

      void AddDrawingfromDrawing();
      void OnButtonSecond(wxCommandEvent& event);


      wxPanel* panel;
      wxStaticText* headlineText;
      wxTextCtrl* inputField;
      wxCheckListBox* checkListBox;
      wxButton* clearButton;
      wxButton* addButton;
      wxButton* deleteButton;
      wxDataViewCtrl* dataViewCtrl;
      //--------menu bar
      wxMenuBar* menuBar;
      wxMenu* fileMenu;
      wxMenu* editMenu;
      wxMenu* customMenu;

      wxStatusBar* statusBar;
       wxButton* drawButton;
       wxButton* secondFrame;   // second frame
       
      //  DrawingCanvas* canvas;
      




      
      //wxButton* deleteButton;  -> zamijeniti umjesto  delete keybutton or ALT
      // button for deleting all (reset)


        

};


#endif  // MAINFRAME_HPP