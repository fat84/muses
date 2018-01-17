set GENERATOR=Visual Studio 14 2015
if exist x32win rd x32win /S/Q
mkdir x32win
cd x32win
cmake ../../ -G "%GENERATOR%"
pause