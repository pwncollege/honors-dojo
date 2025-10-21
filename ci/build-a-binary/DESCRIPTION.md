For this first challenge, let's keep it really simple.

We have provided a makefile and a source file. You don't need to know how either of them work,
all you need to do is invoke the makefile in your workflow!

This challenge also simplifies things further: instead of simulating a remote run location, this will run in `/challenge/repository`.

Our checker script will try to execute your binary at `/challenge/repository/build`. Move the program where it's needed.

NOTE: The directory with the workflows is `/challenge/repository/.github/workflows`. If you try to ls and cd step-by-step, the directory won't be visible!