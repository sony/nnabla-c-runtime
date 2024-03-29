REM Copyright 2018,2019,2020,2021 Sony Corporation.
REM Copyright 2021 Sony Group Corporation.
REM
REM Licensed under the Apache License, Version 2.0 (the "License");
REM you may not use this file except in compliance with the License.
REM You may obtain a copy of the License at
REM
REM     http://www.apache.org/licenses/LICENSE-2.0
REM
REM Unless required by applicable law or agreed to in writing, software
REM distributed under the License is distributed on an "AS IS" BASIS,
REM WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
REM See the License for the specific language governing permissions and
REM limitations under the License.

@ECHO OFF
SETLOCAL

IF NOT DEFINED generate_target (
  SET generate_target=Visual Studio 16 2019
)

IF NOT DEFINED build_type (
  SET build_type=Release
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
cmake -G "%generate_target%" %NNABLACRUNTIMEROOT% || GOTO :ERROR

cmake --build . --config %build_type% --target package|| GOTO :ERROR

ENDLOCAL
EXIT /b

:ERROR
ECHO failed with error code %ERRORLEVEL%.

ENDLOCAL
EXIT /b %ERRORLEVEL%
