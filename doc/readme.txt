1. ENVIRONMENT
Debian + Eclipse + GCC + Doxygen + Papyrus

1.1. Debian
Description: Debian GNU/Linux 9.6 (stretch)
Release:	 9.6
Codename:	 stretch

1.2. Eclipse IDE
Eclipse IDE for C/C++ Developers
Version: Photon Release (4.8.0)
Build id: 20180619-1200
OS: Linux, v.4.9.0-4-amd64, x86_64 / gtk 3.22.11, WebKit 2.18.6
Java version: 1.8.0_212

1.3. GCC
gcc (Debian 6.3.0-18+deb9u1) 6.3.0 20170516
g++ (Debian 6.3.0-18+deb9u1) 6.3.0 20170516

1.4. Doxygen
Plug-in Name: Doxygen binaries 
Version: 1.8.13.v20180118

1.5. Papyrus
Go to Help -> About Eclipse IDE -> Installation Details -> Installed Software.
Type "papyrus".


2. COMPILATION / RUN

2.1. Compilation with C++11/14 in Eclipse

2.1.1. Support&compilation for C++11

2.1.1.1. Using "Dialect" in "Tool Settings"
In Eclipse, go to menu item Project -> Properties.
In C/C++ Build -> Settings, set/configure the relevant configuration.
Click on C/C++ build -> Settings -> Tool Settings tab -> Dialect.
Select language standard ISO C++11 (-std=c++0x).
Press Apply button and rebuild.

2.1.1.2. Using "Other flags" build
In Eclipse, go to menu item Project -> Properties.
In C/C++ Build -> Settings, set/configure the relevant configuration.
Click on C/C++ build -> Settings -> Tool Settings tab -> Miscellaneous.
Copy to "Other flags" field build -std=c++11 or -std=gnu++11.
Press Apply button and rebuild.

2.1.2. Support&compilation for C++14 in Eclipse

2.1.2.1. Using "Dialect" in "Tool Settings"
In Eclipse, go to menu item Project -> Properties.
In C/C++ Build -> Settings, set/configure the relevant configuration.
Click on C/C++ build -> Settings -> Tool Settings tab -> Dialect.
Select language standard ISO C++1y (-std=c++1y).
Press Apply button and rebuild.

2.1.2.2. Using "Other flags" build
In Eclipse, go to menu item Project -> Properties.
In C/C++ Build -> Settings, set/configure the relevant configuration.
Click on C/C++ build -> Settings -> Tool Settings tab -> Miscellaneous.
Copy to "Other flags" field build -std=c++14 or -std=gnu++14.
Press Apply button and rebuild.

At the moment, current build configuration, both Release and Debug,
use -std=gnu++14 compilation flag. 

2.2. Compilation with C++14 in terminal
cd dns_forwarder/Release
make clean
make all

2.3 Run application
cd dns_forwarder/Release
./dns_forwarder -v 62.241.198.245 53

3. DOCUMENTATION

3.1. Coding conventions.
Please, check the file coding_conventions.txt in doc folder.

3.2. Doxygen's documentation.
Please, open the file dns_forwarder/doc/doxygen/outputDir/html/index.html

3.3. Papyrus
Please, check the class diagram.
Path: dns_forwarder/doc/papyrus/class_diagram.png
