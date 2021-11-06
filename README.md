# Cache Simulator

Computer System Architectures's Assignment II – Cache Design

### Table of Contents

- [Problem](#Problem)
- [Getting Start](#Getting-Start)
- [Report](#Report)

### Problem

Please design an experiment (using the cache simulator) for studying the factors that affect the
performance of cache accesses. We will address traces from `gcc_ld_trace.txt` or `go_ld_trace.txt` as
benchmarks. Please fill your results and plot graph of each table. In particular, what does the
results suggest about the design of cache.

1. Block Size Tradeoff on direct mapped cache

<table>
    <thead>
        <tr>
            <th colspan="5">
              <center>Direct mapped</center>
            </th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="2">Block Size (Bytes)</td>
            <td colspan="4">Cache Size (KB)</td> 
        </tr>
        <tr>
          <td>4</td>
          <td>8</td>
          <td>16</td>
          <td>32</td>
        </tr>
        <tr>
          <td>4</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>8</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>16</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>32</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
    </tbody>
</table>

2. N-way associative cache with replacement algorithms: Least recently used (LRU), and Round Robin (RR).

<table>
    <thead>
        <tr>
            <th colspan="5">
              <center>Associativity</center>
            </th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="2">Cache Size (KB) </td>
            <td colspan="2">Two-way</td> 
            <td colspan="2">Four-way</td> 
        </tr>
        <tr>
          <td>LRU</td>
          <td>RR</td>
          <td>LRU</td>
          <td>RR</td>
        </tr>
        <tr>
          <td>1</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>4</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>8</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>32</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>512</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>1024</td>
          <td></td>
          <td></td>
          <td></td>
          <td></td>
        </tr>
    </tbody>
</table>

Note that simulation code and traces can be downloaded from [https://www.cp.eng.chula.ac.th/~krerk/books/Computer%20Architecture/CacheSim/](https://www.cp.eng.chula.ac.th/~krerk/books/Computer%20Architecture/CacheSim/)

### Getting Start

1. clone this repository

   ```bash
    git clone https://github.com/saenyakorn/cache-simulator.git
   ```

2. If you use [VSCode](https://code.visualstudio.com), you need to install essential extension such as [Microsoft C/C++ extension](https://code.visualstudio.com/docs/languages/cpp)

3. Make sure you have `gcc` and `g++` command. Please try this command on your terminal

   ```bash
   gcc --version
   # or
   g++ --version
   ```

   You shouldn't receive error message on your terminal.

4. To compile the original program

   ```bash
   gcc -o CacheSim CacheSim.c
   ```

   You should get `CahceSim.exe` or `CacheSim` on your workspace.

5. To start the original program

   ```bash
   ./CacheSim gcc_ld_trace.txt
   # or
   ./CacheSim go_ld_trace.txt
   ```

   It'll inform you about simulation of cache hit and cache miss.

   **But the original program can't adjust set size and replacement policy. I suggest you to use `./CustomCacheSim` instead**

   ```bash
   g++ -o CustomCacheSim CustomCacheSim.cpp
   # then
   ./CustomCacheSim gcc_ld_trace.txt
   # or
   ./CustomCacheSim go_ld_trace.txt
   ```

6. To answer all of the problems, you need to adjust `CacheSim.h` by yourself. Then compile the program and run again.

### Report

Please ask @saenyakorn for this.
