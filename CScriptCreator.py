"""CScriptCreator.py Version 0.0.1-release-1
functionalities{
    -> Requires Four arguments <pythonScript> [command] [ScriptName] [ScriptLocation]
    -> [command] -c -> creates source files in given dir
    -> [command] -r -> recompiles shared object
    -> Creates .hpp and .cpp files by taking name as first CL argument
    -> Creates Start, Update and Exit Functions in the source File
}
"""

import sys
import os
args = sys.argv
command = args[1]
sourcename = args[2]
location = args[3]
cpplines = []
hpplines = []
cppname = sourcename + ".cpp"
hppname = sourcename + ".hpp"


def createHeader():
    hdr = open(location + "/" + hppname, 'w+')
    hpplines.append('#ifndef ' + sourcename + '\n')
    hpplines.append('#define ' + sourcename + '\n')
    hpplines.append('extern "C" void Init();\n')
    hpplines.append('extern "C" void Start();\n')
    hpplines.append('extern "C" void Update();\n')
    hpplines.append('extern "C" void Exit();\n')
    hpplines.append('#endif\n')
    hdr.writelines(hpplines)
    hdr.close()


def createSource():
    src = open(location + "/" + cppname, 'w+')
    cpplines.append('#include "' + hppname + '"\n\n\n')
    cpplines.append(
        "// This function runs at the start of the application after editor/Application post start\n// -----Init-----\n")
    cpplines.append('void Init(){}\n\n\n')
    cpplines.append(
        "// This function runs at the start of the application after editor/Application post start\n// -----Start-----\n")
    cpplines.append('void Start(){}\n\n\n')
    cpplines.append(
        "// This function runs once every frame\n// -----Update-----\n")
    cpplines.append('void Update(){}\n\n\n')
    cpplines.append(
        "// This function runs after editor/application post update\n// -----Exit-----\n")
    cpplines.append('void Exit(){}\n')
    src.writelines(cpplines)
    src.close()


def createSharedObject():
    print("Creating shared object functionality on development...")
    print('g++ -shared '+location+'/'+cppname+' -fPIC -o ' +location+'/'+
              sourcename+'.so'+' -Wl,--export-dynamic')
    os.system('g++ -shared '+location+'/'+cppname+' -fPIC -o ' +location+'/SO'+'/'+
              sourcename+'.so'+' -Wl,--export-dynamic')


if(len(args) != 4):
    print("Please give script and its location respectively")


else:
    if(command == '-c'):
        createHeader()
        createSource()
        createSharedObject()
    elif(command == '-r'):
        """ Recompile Shared object """
        createSharedObject()
