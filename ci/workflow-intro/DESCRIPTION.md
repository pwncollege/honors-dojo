Let's try something really simple to start.

As you'll recall from the videos, the .yml functions almost like a bash script. For this challenge (and only this challenge), `/flag` will be owned by the runner. The output from the challenge runner will be displayed in stdout. Can you get the flag?

The checker script for the whole module is at `/challenge/check`. The directory with the workflows is `/challenge/repository/.github/workflows`. Remember what happens when you try to run `ls` on a directory with a `.` in front of it? Don't worry, it's definitely there!