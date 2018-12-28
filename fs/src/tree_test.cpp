#include <wx/wx.h>
#include "tree_test.h"
#include "tree_frame.h"

IMPLEMENT_APP(TreeTestApp)

bool TreeTestApp::OnInit()
{
    // TreeFrame(name, x, y, width, length)
    std::string rootPath = wxApp::argv[1].ToStdString();
    wxFrame* frame = new TreeFrame(wxT("***Tree Test***"), 2000, 100, 600, 400, rootPath);
    frame->Show(true);
    this->SetTopWindow(frame);
    return true;
}
