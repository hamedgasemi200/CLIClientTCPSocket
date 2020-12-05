A lightweight TCP client socket generator.

## Compilation

```
qmake TCPClientSocket.pro
make
```
## Software Flags

+ `-p`, `--port`: to set the port number.
+ `-u`, `--url`: to set the host address (DN or IP).
+ `-w`, `--write`: to set a file path (containing request packets) to write its data to the request socket.
+ `--headers`: to set a file path to read its lines as request headers.
