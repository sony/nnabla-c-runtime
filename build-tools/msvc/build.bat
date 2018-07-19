:: Copyright (c) 2017 Sony Corporation. All Rights Reserved.
::
:: Licensed under the Apache License, Version 2.0 (the "License");
:: you may not use this file except in compliance with the License.
:: You may obtain a copy of the License at
::
::     http://www.apache.org/licenses/LICENSE-2.0
::
:: Unless required by applicable law or agreed to in writing, software
:: distributed under the License is distributed on an "AS IS" BASIS,
:: WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
:: See the License for the specific language governing permissions and
:: limitations under the License.

@ECHO OFF
SETLOCAL

IF NOT DEFINED GENERATETARGET (
  SET GENERATETARGET=Visual Studio 14 2015 Win64
)

IF NOT DEFINED BUILDTYPE (
  SET BUILDTYPE=Release
)


SET NNABLACRUNTIMEROOT=%~dp0..\..
IF NOT DEFINED NNABLACRUNTIMEBUILDFOLDER (
  SET NNABLACRUNTIMEBUILDFOLDER=%NNABLACRUNTIMEROOT%\build
)


IF NOT EXIST %NNABLACRUNTIMEBUILDFOLDER% (
   MD %NNABLACRUNTIMEBUILDFOLDER%
)

CD %NNABLACRUNTIMEBUILDFOLDER%

ECHO OFF
cmake -G "%GENERATETARGET%" %NNABLACRUNTIMEROOT% || GOTO :ERROR

cmake --build . --config %BUILDTYPE% --target package|| GOTO :ERROR

ENDLOCAL
EXIT /b

:ERROR
ECHO failed with error code %ERRORLEVEL%.

ENDLOCAL
EXIT /b %ERRORLEVEL%
