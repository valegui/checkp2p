# Check GPU P2P

Check if the system has multi GPU availables and returns a list with the index of those GPUs that can communicate with the GPU 0.

## Example
```bash
$ ./p2pDevices
./p2pDevices Starting...

Detected 1 CUDA Capable device
0
```

```bash
$ ./p2pDevices
./p2pDevices Starting...

Detected 2 CUDA Capable devices
0,1
```