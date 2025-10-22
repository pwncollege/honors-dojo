In the first challenge, your workflow ran as root. From now on, we'll be protecting the flag and the only (intended) way for you to complete these challenges will be to pass the provided conditions.

One of the most common ways to utilize a continuous integration system is to build an application
in some kind of reproducible environment. For example, Sun Devil Rocketry builds its flight firmware apps
in a CI pipeline that follows these steps:

1. Check out the repository's code, and recursively check out the submodules
2. Install the required dependencies (a version of GCC for bare-metal ARM targets called arm-none-eabi-gcc)
3. Invoke all flight firmware makefiles for legacy apps
4. Invoke the current app's makefile in debug mode
5. Invoke the current app's makefile in release mode

By doing this all in a workflow, we're able to verify that someone's changes won't break the build
on any application that is actively supported by the team.

Because of my own familiarity with C and C++ build systems, that's what we'll have you use here. We have provided a Makefile and a source file. You don't need to know how either of them work,
all you need to do is invoke the Makefile in your workflow! The program it builds will be run
as root, and it will print the flag to stdout.

This challenge also has one way to simplify things: instead of simulating a remote run location, this will run in `/challenge/repository`. This is necessary to make sure your compiled program exists after the workflow cleans itself up. In future challenges, this will not be the case.

P.S: If you aren't familiar with Makefiles, they also work kinda like an extended version of a shell script. All you have to do is run the `make` command in the same directory as any file designated as a `Makefile`.