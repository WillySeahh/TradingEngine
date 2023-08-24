# Utils Folder

This folder contains commonly used components in our trading system. These components are designed with consideration into
1. low latency
2. cache friendly
3. reducing mutex/semaphores

We would heavily reuse these components in our trading system and hence we categorize them under `utils`


## Different folder explained

### Threads


### Memory Pool


### Lock Free Queue


## Code Repo Structure
```
├── CMakeLists.txt
├── threads
├── lockFreeQueue
├── memoryPool
├── README.md
```

