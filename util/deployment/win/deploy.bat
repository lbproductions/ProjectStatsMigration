mkdir "%1\deploy"
cd "%1"
copy lib\LBDatabase\lbdatabase.dll deploy\lbdatabase.dll
copy lib\LBGui\lbgui.dll deploy\lbgui.dll
copy C:\QtSDK\mingw\bin\mingwm10.dll deploy\mingwm10.dll
copy C:\QtSDK\mingw\bin\libgcc_s_dw2-1.dll deploy\libgcc_s_dw2-1.dll
copy C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin\QtCore4.dll deploy\QtCore4.dll
copy C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin\QtSql4.dll deploy\QtSql4.dll
copy C:\QtSDK\Desktop\Qt\4.8.1\mingw\bin\QtGui4.dll deploy\QtGui4.dll
copy %3\..\frameworks\WinSparkle-0.3\WinSparkle.dll deploy\WinSparkle.dll
copy "%2" deploy\%2
