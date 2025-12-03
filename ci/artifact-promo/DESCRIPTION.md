You're nearly there! The last thing we're gonna look at is the basics of CD, or more 
accurately: how to link your CI pipeline up to a delivery mechanism. Now, there are
limits to what we can simulate in the dojo, but luckily, our tools allow us to set up a fake 
artifact server. So, we're gonna do Build a Binary 2 again, but with one little extra step this 
time.

```
- name: "Promote Artifacts"
  uses: actions/upload-artifact@v4
  id: promote-results
  with:
    name: program
    path: ${{ github.workspace }}/build/program
```

In an actual environment, this would upload a file from your workflow run to Github! I use this
to preserve test artifacts after a run, including results and coverage reports. I'm also 
starting to use it for CD, building binaries and making pre-releases for me on Github 
automatically. You're going to use it to upload your compiled program, and then the checker 
script is gonna run it. Simple!