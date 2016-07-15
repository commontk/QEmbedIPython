Notes
-----

* Setting up environment

eval $(/home/jcfr/Projects/QEmbedIPython-Release/python-install/bin/QEmbedIPython --launcher-show-set-environment-commands)

* To embed an IPython kernel:

(1) Start /home/jcfr/Projects/QEmbedIPython-Release/QEmbedIPython-build/QEmbedIPython

(2) Type:

  import IPython
  IPython.embed_kernel()


* To start ipython with a different kernel manager:

(1) Setup env.

   eval $(/home/jcfr/Projects/QEmbedIPython-Release/python-install/bin/QEmbedIPython --launcher-show-set-environment-commands)

   export PYTHONPATH=$PYTHONPATH:/home/jcfr/Projects/QEmbedIPython-Release/existingkernel

(2) Edit existingkernel/managers.py to change reference to connection file

(3) ipython notebook --NotebookApp.kernel_manager_class=existingkernel.managers.ExistingMappingKernelManager --no-browser


