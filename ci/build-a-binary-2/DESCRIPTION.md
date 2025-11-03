In the last challenge, your workflow ran in `/challenge/repository`. Obviously, on a real remote
runner, you would need to be able to set everything up yourself. This might include compilers,
SDKs, other external libraries, etc. Fortunately, since this project is built in C and runs on an `ubuntu-latest` runner, GCC comes pre-installed (both on our dojo CI run simulator and on actual Ubuntu runners)!

If you're curious about what tools come pre-installed on each runner for your own projects, check out the following resources:
- [MacOS](https://github.com/actions/runner-images/blob/main/images/macos/macos-26-arm64-Readme.md)
- [Ubuntu](https://github.com/actions/runner-images/blob/main/images/ubuntu/Ubuntu2404-Readme.md)
- [Windows](https://github.com/actions/runner-images/blob/main/images/windows/Windows2025-Readme.md)

However, nothing new gets downloaded onto your runner without you telling it to, including the code from the repository that triggered the run. There's a pretty easy solution for this, luckily! GitHub packages its own set of steps to do this for you.

```
- name: Check out repository code
  uses: actions/checkout@v4
```

This step checks out your repository to the root of the runner (the runner's root directory == the repository's root directory). From there, you can proceed as you did previously -- almost. Since we're no longer in `/challenge/repository`, we can't see your compiled binary once you're done! The runner cleans up after itself. The fix for this is just to run it (remember the binary is called `program` and lives in the `build` directory).

P.S: If you aren't familiar with Makefiles, they also work kinda like an extended version of a shell script. All you have to do is run the `make` command in the same directory as any file designated as a `Makefile`.