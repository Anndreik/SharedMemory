Ex 3 - shared resource

Write a program that will do the following:

    create a shared memory segment and will generate initial random data, that it will put into that segment
    create 3 child processes and keep track of their PIDs
    once every second, regenerate some random data to put into the segment
    every time new data is generated, it will signal the child processes

The child processes will exec and load a program that will do the following:

    open the shared memory segment
    wait for the signal from the first process
    read the data and output it to stdout

Assure proper synchronization on data access.
The shared memory identifier is known beforehand - no need to communicate it between processes.
You can use signals to notify new data.
