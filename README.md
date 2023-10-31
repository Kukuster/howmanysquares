# howmanysquares

Goal: write a deterministic algorithm that counts how many squares are in a given image, e.g.:
![51](https://github.com/Kukuster/howmanysquares/assets/12045236/9c4542a7-a08a-4209-b603-9c90223fd2ec)
(answer here is 51)


Run under Docker, or use Dockerfiles as a guide to how to set up your environment.


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
