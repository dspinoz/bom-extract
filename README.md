## BOM Extract

This is a utility that attempts to extract Bill of Materials from PDF documents.

### Development Environment - Getting Started
* Download and install git bash
* download and run mingw-get-setup.exe 
* click Install
* Once the MinGW Installation Manager opens, select Basic Setup and install the following:
 * mingw-developer-toolkit
 * mingw32-base
 * mingw32-gcc-g++
 * msys-base
 * msys-wget-bin
* Installation -> Apply Changes
* Apply

#### Adding git to mingw
* Run C:\MinGW\msys\1.0\msys.bat
* vi .profile
* Add the following lines (i)

 ```
#!/bin/sh 
export PATH=$PATH:/c/Program\ Files\ \(x86\)/Git/bin/
```
* Write and exit (:wq)
* Restart shell
* which git

### Fetching Source, Building and Installing
* Run msys.bat
* git clone https://github.com/dspinoz/bom-extract
* cd bom-extract
* autoreconf -i
* ./configure --prefix=`pwd`/install
* make
* make install
