rem @echo off
SET program="%1"
if %program% == "" goto err

echo Test1 > out.txt
%program% input.txt output1.txt ma mama >> out.txt
if ERRORLEVEL 1 goto testFailed
if ERRORLEVEL 0 echo ...OK >> out.txt

echo Test2 >> out.txt
%program% input.txt output2.txt 1231234 chicken >> out.txt
if ERRORLEVEL 1 goto testFailed
if ERRORLEVEL 0 echo ...OK >> out.txt

echo Test3 >> out.txt
%program% input.txt output3.txt ma mama mamo4ka >> out.txt
if NOT ERRORLEVEL 1 goto testFailed
if ERRORLEVEL 0 echo ...OK >> out.txt

echo Test4 >> out.txt
%program% input.txt output4.txt Ann ASDABSJDGABSJDGBASBDJBASDHBKAHSBDHBASDBAKHSDBHASBHDKASBHDBHJASBHDASBHDABJHSDBHASDASDASDASDASDASDASDASDASDASDASDASDGASGDGASDVGASGDVDJVHAGSDVASDASDGHASHGDAGVSDGHSADASGHDGHASDGHASGHDASGVD >> out.txt
if ERRORLEVEL 1 goto testFailed
if ERRORLEVEL 0 echo ...OK >> out.txt

echo Test5 >> out.txt
%program% input.txt output4_false.txt ma >> out.txt
if NOT ERRORLEVEL 1 goto testFailed
if ERRORLEVEL 0 echo ...OK >> out.txt

echo Test6 >> out.txt
%program% input.txt input.txt output7_false.txt "" empty >> out.txt
if NOT ERRORLEVEL 1 goto testFailed
if ERRORLEVEL 0 echo ...OK >> out.txt

echo OK
pause
exit /B

:testFailed
echo Testing failed
pause
exit /B

:err
echo Usage: test.bat <Path to program>