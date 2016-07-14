

// Qt includes
#include <QApplication>

// PythonQt includes
#include <PythonQt.h>

// CTK includes
#include <ctkCommandLineParser.h>
#include <ctkPythonConsole.h>

// QEmbedIPython includes
#include "qEmbedIPythonPythonManager.h"

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  ctkCommandLineParser parser;
  // Use Unix-style argument names
  parser.setArgumentPrefix("--", "-");

  ctkPythonConsole console;

  qEmbedIPythonPythonManager pythonManager(&console);
  pythonManager.setInitializationFlags(PythonQt::RedirectStdOut);

  console.initialize(&pythonManager);
  console.setAttribute(Qt::WA_QuitOnClose, true);
  console.resize(600, 280);
  console.show();

  QStringList list;
  list << "qt.QPushButton";
  console.completer()->setAutocompletePreferenceList(list);

  return app.exec();
}
