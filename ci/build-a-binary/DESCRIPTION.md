In the first challenge, your workflow ran as root. From now on, we'll be protecting the flag and the only (intended) way for you to complete these challenges will be to pass the provided conditions.

We have provided a makefile and a source file. You don't need to know how either of them work,
all you need to do is invoke the makefile in your workflow! The program it builds will be run
as root, and it will print the flag to stdout.

This challenge also has one way to simplify things: instead of simulating a remote run location, this will run in `/challenge/repository`. This is necessary to make sure your compiled program exists after the workflow cleans itself up. In future challenges, this will not be the case.