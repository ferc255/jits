How to install libjit
#####################

1. Install dependencies
   All of them are necessary.

   .. code-block:: bash

       $ sudo apt install autoconf automake libtool flex bison texinfo pkg-config

2. Clone the repository of libjit

   .. code-block:: bash

       $ git clone git://git.savannah.gnu.org/libjit.git

3. Configure

   .. code-block:: bash

       $ cd ./libjit
       $ sudo ./bootstrap
       $ sudo ./configure
       $ sudo make
       $ sudo make install

4. Compile

   .. code-block:: bash

       $ gcc my_app.c -ljit -lpthread -lm -ldl -o app

   Before you can run it, add /usr/local/lib/ (or any other directory that contains libjit.so.0) to LD_LIBRARY_PATH.

   .. code-block:: bash

       $ LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
       $ ./app
