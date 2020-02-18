call config.bat
%NUANCE%\bin\win32\nuance-compile %PKGHOME%.grammar English.America -i %AP%\package -o %PKGHOME% -auto_pron -merge_dictionary %PKGHOME%.dictionary
pause