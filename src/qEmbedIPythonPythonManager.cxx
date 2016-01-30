
// QT includes
#include <QFile>
#include <QFileInfo>
#include <QApplication>
#include <QTimer>

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
  this->addObjectToPythonMain("_app", qApp);
  this->addObjectToPythonMain("_console", this->parent());
  this->addObjectToPythonMain("_pythonqt", PythonQt::self());
}

//-----------------------------------------------------------------------------
void qEmbedIPythonPythonManager::embedIPythonKernel()
{
  this->executeString("import pythonqt_embed_ipython_kernel as peik");
  this->executeString("peik.embed_kernel()");
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

  QTimer::singleShot(0, this, SLOT(embedIPythonKernel()));
}

