In the last challenge, you built your program on a remote runner! This is a great first step 
towards unlocking CI/CD in your own projects, and you've hit the first of the three prongs I 
mentioned in the lectures. Now, it's time to look at the second prong.

It's really useful to be able to run automated tests in your CI pipelines. This is a huge step
towards promoting code quality, since every change will verify that core functionality hasn't 
been broken. The tests themselves are out of scope for this module, since there's so much to 
cover in the world of SQA and testing. Depending on your language or environment, there are
so many different tools for this and we definitely couldn't cover it all as a tangent. If you
don't have any experience with software testing coming into this, I highly recommend you go out 
and do some research to see what it's all about.

For this module, we'll keep it simple and just simulate the invocation of a test using a bash
script. You can use your imagination and fill in the blanks based on whatever framework you
might be used to (if this were Sun Devil Rocketry, the command would be "make test").

You'll want to perform two steps in your workflow:
1. Compile the program, same as before.
2. Invoke `tst/check-sha.sh`

The checker script will verify that you ran the test correctly. Good luck!