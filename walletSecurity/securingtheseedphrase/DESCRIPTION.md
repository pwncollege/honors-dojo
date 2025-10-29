# Securing the Seed Phrase

## Introduction to Seed Phrases

In the world of cryptocurrency and Web3, a **seed phrase** (also called a recovery phrase) is a series of 12-24 words that gives you access to your crypto wallet. It's essentially the master key to all your funds.

**Critical Security Concept:** If someone gets your seed phrase, they own your wallet. Forever.

This is why seed phrases should NEVER be:
- Stored in plain text on your computer
- Saved in cloud storage
- Shared with anyone
- Left with default file permissions that anyone can read

## Cold Storage Best Practice

One approach to securing seed phrases is **cold storage** - keeping them completely offline and protected. In this challenge, you'll simulate cold storage security using Linux commands:

1. **Obfuscation with `tr`:** Transform the text so it's not immediately readable
2. **File Permissions with `chmod`:** Restrict access to owner-only

## The Challenge

In this challenge, you need to:
1. Create a file containing a dummy seed phrase
2. Obfuscate it using the `tr` command (ROT13 cipher)
3. Set proper file permissions so only YOU (the owner) can read/write it

### Commands You'll Use

**`tr` (translate characters):**
```console
hacker@dojo:~$ echo "hello" | tr 'a-z' 'n-za-m'
uryyb
```
The `tr` command translates characters. The format `A-Za-z` to `N-ZA-Mn-za-m` performs ROT13 encryption.

**`chmod` (change mode/permissions):**
```console
hacker@dojo:~$ chmod 600 myfile.txt
```
This sets permissions to `rw-------` (read/write for owner only).

**File permission format:**
- `6` = read(4) + write(2) for owner
- `0` = no permissions for group
- `0` = no permissions for others

## Your Task

Run the `seedPhrase` command to validate your solution. This script will check:
1. Whether you created the obfuscated seed phrase file correctly
2. Whether file permissions are set to 600 (owner read/write only)

If successful, you'll receive the flag!

### Hint

The `tr` command can read from a file and output to another file using:
```bash
cat input.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m' > output.txt
```

Good luck, and remember: In the real world, proper seed phrase security can mean the difference between keeping your crypto safe and losing everything!