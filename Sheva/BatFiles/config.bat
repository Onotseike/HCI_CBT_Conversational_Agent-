:: _____________________________________________________________________________
:: 
:: 	File:		config.bat
:: 	This batch script initializes the common batch variables. It is called
:: 	by the other batch scripts which start up nuance.
:: 
:: _____________________________________________________________________________
::
:: Configure the first 5 variables to fit the environment
:: The NUANCE folder should point to a depth where bin,include,lib and java can be found
set NUANCE=C:\Nuance85\V8.5.0
set VOCALIZER=C:\Nuance85\Vocalizer4.0
set APPHOME=D:\onots\source\Workspaces\AINT512\Sheva
set EXECAPP=%APPHOME%\Debug\Sheva.exe
set PKGHOME=%APPHOME%\Grammar\Core

:: The variables below do not need to be changed
set Path=%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%VOCALIZER%\bin\win32;%NUANCE%\scripts;%NUANCE%\bin\win32;
set CLASSPATH=%NUANCE%\java\nsc.jar;%NUANCE%\java\vcomsc.jar;%NUANCE%\java\swingall.jar;
set JNUANCE=%NUANCE%\java
set INCLUDE=%INCLUDE%;%NUANCE%\include
set LIB=%LIB%;%NUANCE%\lib\win32
set BATHOME=%APPHOME%\
set LOGHOME=%APPHOME%\logs
SET MACHINE_TYPE=win32
:: set OBJHOME=%APPHOME%\obj
:: set SRCHOME=%APPHOME%\src
set AP=%APPHOME%
