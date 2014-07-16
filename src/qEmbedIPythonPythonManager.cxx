
// QT includes
#include <QFile>
#include <QFileInfo>
#include <QApplication>

// PythonQT includes
#include <PythonQt.h>

// CTK includes
#include "qEmbedIPythonPythonManager.h"

//-----------------------------------------------------------------------------
qEmbedIPythonPythonManager::qEmbedIPythonPythonManager(QObject* _parent) : Superclass(_parent)
{
}

//-----------------------------------------------------------------------------
qEmbedIPythonPythonManager::~qEmbedIPythonPythonManager()
{
}

//-----------------------------------------------------------------------------
QStringList qEmbedIPythonPythonManager::pythonPaths()
{
  QStringList paths;
  //paths << Superclass::pythonPaths();

  return paths;
}

//-----------------------------------------------------------------------------
void qEmbedIPythonPythonManager::preInitialization()
{
  this->Superclass::preInitialization();

}

//-----------------------------------------------------------------------------
void qEmbedIPythonPythonManager::executeInitializationScripts()
{
  //QString self_dir = QFileInfo(qApp->applicationFilePath()).absolutePath();

  //QString initFile = self_dir;
  //#if defined(CMAKE_INTDIR)
  //initFile.append("/..");
  //#endif
  //initFile.append("/Python/ctkSimplePythonShell.py");

  //Q_ASSERT(QFile::exists(initFile));

  // Evaluate application script
  //this->executeFile(initFile);
}

