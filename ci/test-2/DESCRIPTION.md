Great job! Being able to run tests like that is a huge reason why I love CI so much.

Now, let's expand upon this a little bit. Most projects won't just have one test to run.
There are a bunch of ways to run multiple tests, but my favorite is built in to Github Actions
for exactly this purpose. In your .yaml file, you can specify a list of jobs that use the same specification with keywords swapped out. It's hard to explain in text, but I'll show you what I mean here:

```
jobs:
  test-runner:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        tests: [test-1, test-2]
    steps:
      - name: Build and run the app/${{ matrix.tests }} tests
        run: |
          cd ${{ github.workspace }}/test/app/${{ matrix.tests }}
          make test
```

Note the "strategy: matrix: tests: [...]" here, that's doing a lot of heavy lifting. What happens is the list under "steps" runs *twice*, once for each item in the list. When it runs, it'll fill in this ${{ matrix.tests }} variable with every value enumerated in the list, letting you re-use your specification with only the replacements you need.

For this challenge, you'll do the same thing. In addition to the `tst/check-sha.sh` from the last challenge, there's now a `tst/check-sha2.sh`. You'll invoke it the same way, and the checker script will look for both in your output.