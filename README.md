# shared_memory_object demo

Point `BOOST_PATH` variable to the Boost installation, then compile and run the demo:

```bash
g++ -I${BOOST_PATH} shmem.cpp -o shmem
./shmem object1
```

You should see the following output:

> creating shared_memory_object named "object1"  
> permissions: 666  
> success


## A problem on macOS

The demo compiled with Boost 1.78 or 1.79 may fail on macOS, if the first `shared_memory_object` 
was created under a different user, e.g. *root*. Reboot macOS to ensure that.

> sudo ./shmem object1  
> ...  
> ./shmem object2  
> creating shared_memory_object named "object2"  
> permissions: 666  
> error: Dynamic exception type: boost::interprocess::interprocess_exception
> std::exception::what: Operation not permitted

It fails even if the object name is different. 
There are no errors, if the demo is compiled with Boost 1.77.
