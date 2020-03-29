# howmanysquares

This program is being developed under Docker and is meant to run under Docker. If you want to use a different environment for compilation and execution, use Dockerfiles as a guide to how to set up your environment.


### frequently used and useful commands:

 `docker-compose run --rm compile_gcc920 && docker-compose run --rm testrun_ubuntu1804`

 `bash testrun.sh`
 
 `bash testrun_rebuild.sh`



### debug:

 ```
 docker-compose run --rm compile_gcc920_debug
  #then launch gdb debug in Visual Studio Code
 ```
 
 ```
 docker-compose run --rm compile_ubuntu1804clang_debug
  #then launch gdb in lldb mode debug in Visual Studio Code
 ```



### *.vscode/launch.json* config for debugging
```
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "gdb Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/volumes/hmsbin/showsquares",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${workspaceFolder}",
            "environment": [
                {"name": "HMSBIN_INPUT", "value": "${workspaceFolder}/volumes/input"},
                {"name": "HMSBIN_OUTPUT", "value": "${workspaceFolder}/volumes/output"}
            ],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        },
        {
            "name": "gdb (lldb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/volumes/hmsbin/showsquares",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${workspaceFolder}",
            "environment": [
                {"name": "HMSBIN_INPUT", "value": "${workspaceFolder}/volumes/input"},
                {"name": "HMSBIN_OUTPUT", "value": "${workspaceFolder}/volumes/output"}
            ],
            "externalConsole": false,
            "MIMode": "lldb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```
