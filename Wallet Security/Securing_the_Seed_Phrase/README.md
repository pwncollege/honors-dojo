# Challenge 1: Securing the Seed Phrase

Your task is to create an obfuscated file with a seed phrase and set its permissions correctly.

## Solution

Run the following commands in your terminal to solve the challenge. This will create the necessary files, obfuscate the content, set the correct permissions, and run the verifier to get the flag.

```bash
echo "word one two three four five six seven eight nine ten eleven twelve" > my_seed.txt
cat my_seed.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m' > obfuscated_seed.txt
chmod 600 obfuscated_seed.txt
./seedPhrase
```