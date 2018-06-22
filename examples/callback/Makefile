# Copyright (c) 2017 Sony Corporation. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

all: callback.exe

CFLAGS = /nologo \
	/I..\..\include \
	/I..\..\src\runtime \
	/DWIN32 /D_WINDOWS /W3 /MD /Zi /Ob0 /Od /RTC1  /FS -c 
LDFLAGS = /nologo /version:0.0 /subsystem:console \
	/LIBPATH:..\..\build\src\runtime\Release \
	/LIBPATH:..\..\build\src\functions\Release \
	nnablart_runtime.lib \
	nnablart_functions.lib \
	kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib

callback.obj: callback.c
	cl /c $(CFLAGS) /Focallback.obj callback.c

callback.exe: callback.obj
	link /out:callback.exe /implib:callback.lib /pdb:callback.pdb $(LDFLAGS) callback.obj

clean:
	del callback.obj
	del callback.exe
	del *.pdb
