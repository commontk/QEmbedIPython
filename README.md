Qt Embed IPython
================

This project is a playground created during the SciPy 2014 sprint.

It provides a Qt-based python interactor embedding an IPython kernel where a Jupyter notebook can be used
to interact with the object living in the python interpreter embedded in the Qt application.


Motivation
----------

Allow user to interact with C++ Qt-based applications embedding a python interactor (e.g 3D Slicer, Paraview) either
using the interactor or an IPython notebook.

Usage
-----

* 1. Build the project

```bash
git clone git://github.com/commontk/QEmbedIPython
mkdir QEmbedIPython-Release
cd QEmbedIPython-Release
cmake -DQT_QMAKE_EXECUTABLE=/path/to/qmake ../QEmbedIPython
make -j8
```

* 2. Start QEmbedIPython

```bash
./QEmbedIPython-build/QEmbedIPython
```

* 3. Start IPython

```bash
cd QEmbedIPython-build
make StartIPythonServer
```

Features
--------

* Built-in Qt-based python interactor interacts with the IPython kernel
* IPython notebook also interacts with the IPython kernel
* Qt python bindings done using PythonQt

Licensing
---------

Materials in this repository are distributed under the following licenses:

All software is licensed under the Apache 2.0 License.
See LICENSE_Apache_20 file for details.

All Works of Art are licensed under the Creative Commons Attribution-ShareAlike 3.0.
See LICENSE_CC_BY_SA_30 file for details.

Credits
=======

Jean-Christophe Fillion-Robin
Mike Sarahan
