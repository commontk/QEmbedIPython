
#ifndef __qEmbedIPythonPythonManager_h
#define __qEmbedIPythonPythonManager_h

// CTK includes
# include <ctkAbstractPythonManager.h>

// QEmbedIPython includes
#include "qembedipythonlib_export.h"

class PythonQtObjectPtr;

class QEMBEDIPYTHONLIB_EXPORT qEmbedIPythonPythonManager : public ctkAbstractPythonManager
{
  Q_OBJECT

public:
  typedef ctkAbstractPythonManager Superclass;
  qEmbedIPythonPythonManager(QObject* parent=0);
  ~qEmbedIPythonPythonManager();
  
protected:

  virtual QStringList pythonPaths();
  virtual void preInitialization();
  virtual void executeInitializationScripts();

};


#endif
