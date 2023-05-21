#include "MainFrame.hpp"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Task.hpp"
#include "SetupMainMenu.cpp"
// #include "drawingcanvas.cpp"
// #include "drawingcanvas.h"
#include <chrono>
#include <ctime>


MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)  // constructor
{
    CreateControls();
    BindEventHandlers();
    AddSavedTasks();  // important to be called  -> after CreateControls()
    SetupMainMenu();

}

void MainFrame::CreateControls()
{
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 24)));
    // maybe here can i style my notes-box 

    panel = new wxPanel(this);
    panel->SetFont(mainFont);   // set font to parent and all children
    //wxColour color("#F0F0F0");

    headlineText = new wxStaticText(panel, wxID_ANY, "Quick Notes", wxPoint(0, 22), wxSize(800, 45), wxALIGN_CENTER_HORIZONTAL);
    headlineText->SetFont(headlineFont);
    headlineText->SetBackgroundColour(*wxLIGHT_GREY);

    inputField = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(100,80), wxSize(495,35), wxTE_PROCESS_ENTER);  // a moze i sa bilo kojim drugim
    addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(600, 80), wxSize(100, 35));
    checkListBox = new wxCheckListBox(panel,wxID_ANY, wxPoint(100,120), wxSize(600, 400));
    clearButton = new wxButton(panel, wxID_ANY,"Clear All", wxPoint(100, 525), wxSize(100,35));
    deleteButton = new wxButton(panel,wxID_ANY,"Delete Note", wxPoint(600,525),wxSize(100,35));
   // menuBar = new wxMenuBar(panel,wxID_ANY,)
   
   //drawButton = new wxButton(panel, wxID_ANY, "draw", wxPoint(500, 525),wxSize(100,35));
    secondFrame = new wxButton(panel, wxID_ANY, "second frame", wxPoint(450, 525),wxSize(120,35));
    // canvas = new DrawingCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);


 statusBar = new wxStatusBar(panel,wxID_ANY);
 SetStatusBar(statusBar);
 statusBar->SetStatusText("Mouse coordinates"); //
 //  wxStatusBar* statusBar=CreateStatusBar();
statusBar->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE)); 
   
  
    
   
}


void MainFrame::BindEventHandlers()
{
     addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);  // pointer to the member function that will handle the event
     inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter,this);
     checkListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown,this);
     clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
     this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);    // ovo je event for closing window
     deleteButton->Bind(wxEVT_BUTTON, &MainFrame::DeleteNote, this); 
    panel->Bind(wxEVT_MOTION, &MainFrame::OnMouseEvent, this);    // mouse bewegung(xy axe), hereis  trick: panel->Bind  (if i put panel means for all element on the panel)
     // drawButton->Bind(wxEVT_BUTTON, &MainFrame::OnMouseEvent, this);
     //AddDrawingfromDrawing
     secondFrame->Bind(wxEVT_BUTTON, &MainFrame::OnButtonSecond, this);
}

void MainFrame::AddSavedTasks()
{
    std::vector<Task> tasks = LoadTasksFromFile("tasks.txt");   // koristimo ovako jer "LoadTasksFromFile" vraca nam "vector"

    for(const Task& task: tasks) {
        int index = checkListBox->GetCount();
        checkListBox->Insert(task.description, index);
        checkListBox->Check(index, task.done);
    }
}


void MainFrame::OnAddButtonClicked(wxCommandEvent& event) 
{
   AddTaskFromInput();  // i ponovo weiterleiten .

}

// 2nd option --> with Enter
void MainFrame::OnInputEnter(wxCommandEvent& event)
{
    AddTaskFromInput();
}
// delete note
void MainFrame::OnListKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode()) {
        case WXK_DELETE:
           DeleteSelectedTask();
           break;
        case WXK_ALT:
            DeleteSelectedTask();
           break;
        case WXK_UP:
            MoveSelectedTask(-1);
            break;
        case WXK_DOWN:
            MoveSelectedTask(1);
            break;
        //  case WXK_ALT:
        //     OnListItemClicked();
        //     break;
  
    }
}

//----- second frame  -=----------------



class SecondFrame : public wxFrame
{
public:
    SecondFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};


SecondFrame::SecondFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Add controls and layout for the second window frame here
    wxPanel* panel = new wxPanel(this);
  wxButton* button = new wxButton(panel, wxID_ANY, "GUI", wxPoint(150, 50),
                                  wxSize(100, 35));
wxCheckBox* check_box = new wxCheckBox(panel, wxID_ANY, "Checkbox",  wxPoint(550, 55));
   wxStaticText* label = new wxStaticText(panel, wxID_ANY, "this is static", wxPoint (550,150));
  wxTextCtrl* text = new wxTextCtrl(panel, wxID_ANY," some text goes heere", wxPoint(120, 120), wxSize(200, 50),wxTE_PASSWORD);
  wxTextCtrl* text2 = new wxTextCtrl(panel, wxID_ANY," ohne passwort", wxPoint(160, 170), wxSize(100, 35));
  wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0,100, wxPoint(20, 200), wxSize(-1, 200), wxSL_VALUE_LABEL);  // 200 od gore na dole    val, min, max
  wxGauge* gauge = new wxGauge(panel, wxID_ANY,  100, wxPoint(500, 200), wxSize(200, 90));   // wxSL_VERTICAL
    gauge->SetValue(75);

}



void MainFrame::OnButtonSecond(wxCommandEvent& event)
{
    SecondFrame* secondFrame = new SecondFrame("Second Window", wxDefaultPosition, wxSize(800, 600));
    secondFrame->Show(true);
}


////-------------


void MainFrame::OnClearButtonClicked(wxCommandEvent& event)
{
    if (checkListBox->IsEmpty()) {
        return;
    }
    wxMessageDialog dialog(this, "Are you sure want to delete all tasks", "Delete All", wxYES_NO | wxCANCEL);     // dialog has "Yes" and "No" button
    int result = dialog.ShowModal();

     if (result == wxID_YES) {
            checkListBox->Clear();
        }
}
 // added
void MainFrame::DeleteNote(wxCommandEvent& event)
{
    DeleteSelectedTask();
}



   // turning all items in the checkListBox into task and save it into textfile
void MainFrame::OnWindowClosed(wxCloseEvent& event)
{
      if (checkListBox->IsEmpty()) {
        return;
    }
    //  ---------------  added MessageDialog  --  EXIT
    wxMessageDialog dialog(this, "Do you want to save changes?", "Save", wxYES_NO | wxCANCEL);     // dialog has "Yes" and "No" button
    int result = dialog.ShowModal();

     if (result == wxID_YES) {  //do following

         std::vector<Task>tasks;       // why created again object Task, if already have
      for (int i = 0; i < checkListBox->GetCount(); i++) {
            Task task;  // creating object
            task.description = checkListBox->GetString(i);
            task.done = checkListBox->IsChecked(i);
            tasks.push_back(task);  // -> he created task, but not tasks, we have list of tasks in Task.cpp

      }
        SaveTasksToFile(tasks,"tasks.txt"); // if file exist, will be overriden
        event.Skip();   //   is useful when you want to let other event handlers modify or respond to the same event           
        }

        if (result == wxID_NO) { 
            event.Skip();
        }
    
}


void MainFrame::AddTaskFromInput()
{
   
    wxString description = inputField->GetValue(); // method retrives the current value of the inputField(wxTextCtrl), saved in string called "description"
    // added  counter
    // int count = description.length();
    // if (count > 20) {
    //     // Truncate the text if it exceeds 20 characters
    //     description.Truncate(20);
    //     inputField->SetValue(description);
    //     count = 20;
    //      wxString message = wxString::Format("Mouse geht (x=%d", count);
    //     wxLogStatus(message);
    // }
//  ---------END counter---------

    if (!description.IsEmpty()) {
        checkListBox->Insert(description, checkListBox->GetCount());  // position where the item should be inserted in the list. In this case, GetCount() is used to insert the new item at the end of the list.
            //               checkListBox->Insert(description, 0);   // new item insert on top
        inputField->Clear();
 

    }
     inputField->SetFocus();
}



void MainFrame::DeleteSelectedTask()
{
    int selectedIndex = checkListBox->GetSelection();  // return index of selected Item

    if (selectedIndex == wxNOT_FOUND) {
        return;
    }
    checkListBox->Delete(selectedIndex);  // otherwise delete  , using  delete key   ---> have to replace this key with button
}


// --- added   -- on checklistBix item click open file

void MainFrame::OnListItemClicked(wxCommandEvent &event)
{
    int selectedIndex = checkListBox->GetSelection();
    // int selectedIndex = event.GetSelection();

    if (selectedIndex != wxNOT_FOUND)
    {
       return;
    }

     wxString description = checkListBox->GetString(selectedIndex);
        wxString fileName = "notes_" + wxString::Format("%d", selectedIndex + 1) + ".txt";
        // Open the file in a text editor
        wxLaunchDefaultApplication(fileName);
        // wxString command = "kdeinit " + fileName;
        // wxExecute(command);
}


//  -------------------------- menu  -------------

void OnSomeAction(wxCommandEvent &);
void SetupMainMenu();


// void AddDrawingfromDrawing() 
// {

// }


// void MainFrame::OnSomeAction(wxCommandEvent &)
// {
//     wxMessageBox("Some Action!");
// }

// void MainFrame::SetupMainMenu()
// {
//     wxMenuBar *menuBar = new wxMenuBar();

//     wxMenu *fileMenu = new wxMenu();
//     fileMenu->Append(wxID_NEW);
//     fileMenu->Append(wxID_OPEN);
//     fileMenu->AppendSeparator();
//     fileMenu->Append(wxID_SAVE);
//     fileMenu->Append(wxID_SAVEAS);

//     wxMenu *editMenu = new wxMenu();

//     editMenu->Append(wxID_UNDO);
//     editMenu->Append(wxID_REDO);
//     editMenu->AppendSeparator();
//     editMenu->Append(wxID_CUT);
//     editMenu->Append(wxID_COPY);
//     editMenu->Append(wxID_PASTE);

//     wxMenu *customMenu = new wxMenu();

//     this->Bind(wxEVT_MENU, &MainFrame::OnSomeAction, this,
//                customMenu->Append(wxID_ANY, "Some &Action...\tCtrl-Alt-A")->GetId());

//     customMenu->AppendSeparator();
//     customMenu->AppendCheckItem(wxID_ANY, "Check Item &One\tCtrl-1");
//     customMenu->AppendCheckItem(wxID_ANY, "Check Item &Two\tCtrl-2");
//     customMenu->AppendSeparator();

//     wxMenu *customMenuOptionsSubmenu = new wxMenu();

//     customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option One");
//     customMenuOptionsSubmenu->Check(
//         customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option Two")->GetId(),
//         true);
//     customMenuOptionsSubmenu->AppendRadioItem(wxID_ANY, "Radio Option Three");

//     customMenu->AppendSubMenu(customMenuOptionsSubmenu, "&Options");

//     menuBar->Append(fileMenu, "&File");
//     menuBar->Append(editMenu, "&Edit");
//     menuBar->Append(customMenu, "&Custom");

//     SetMenuBar(menuBar);
// }




////-----------------------------------------------------------
void MainFrame::MoveSelectedTask(int offset)
{
    int selectedIndex = checkListBox->GetSelection();

    if (selectedIndex == wxNOT_FOUND) {
        return;
    }
    int newIndex = selectedIndex + offset;

    if (newIndex >= 0 && newIndex < checkListBox->GetCount()) {   // valjda ako je vece od prvog  i manja od zadnjeg notes-a, onda moze swap
        SwapTasks(selectedIndex, newIndex);
        checkListBox->SetSelection(newIndex, true);  // select of new item, is highligted
    }

}

void MainFrame::SwapTasks(int i, int j)
{ // it won't swipte the actual items, but just text on indices "i"  and "j"
    Task taskI{checkListBox->GetString(i).ToStdString(), checkListBox->IsChecked(i)};  // ToStdString  -> get description  of the item
    Task taskJ{checkListBox->GetString(j).ToStdString(), checkListBox->IsChecked(j)};

    checkListBox->SetString(i, taskJ.description); //  it swaps the description and checked state of the items by calling SetString
    checkListBox->Check(i, taskJ.done);

     checkListBox->SetString(j, taskI.description);
    checkListBox->Check(j, taskI.done);


}


//-----
void MainFrame::OnMouseEvent(wxMouseEvent& event) {
    wxPoint mousePos = event.GetPosition();
    wxString message = wxString::Format("Mouse geht (x=%d y=%d)", mousePos.x, mousePos.y);  // wxString::Format is like printf() func, has placeholder, formatting string without concatination ohne + operators
    wxLogStatus(message);  
    event.Skip();
  }
