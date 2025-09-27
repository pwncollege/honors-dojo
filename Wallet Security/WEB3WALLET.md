# DELETE THIS FILE BEFORE FINALIZING THE MODULE

# 5 Progressive Web3 Wallet Security Challenges (Linux Command Line)

This document outlines five hands-on challenges designed to teach core Web3 wallet security concepts using a standard Linux command-line environment. Each challenge builds upon the last, moving from fundamental file security to advanced analysis and scripting.

---

### Challenge 1: Securing the Seed Phrase (The Obfuscated Vault)

**Core Concept:** File Permissions, Input/Output Redirection, and Basic Text Obfuscation (Simulating Encryption).

**Explanation:** The fundamental defense for your private key (or seed phrase) is to keep it inaccessible. We simulate this by ensuring the key file is not readable by others (`chmod`) and that its contents are text-manipulated (obfuscated) so that it is not immediately readable if someone bypasses the permissions.

| Objective | Challenge Explanation |
| :--- | :--- |
| **Create a highly restricted, obfuscated file.** | **Your Task:** <br> 1. Use `touch` to create a file named `my_seed.txt`. <br> 2. Use `cat` and output redirection (`>`) to write a dummy 12-word seed phrase into the file. <br> 3. Use the `tr` command to apply a simple substitution cipher on the file's content, redirecting the output to a new file, `obfuscated_seed.txt`. <br> 4. Use `chmod` to set the permissions on `obfuscated_seed.txt` so **only the file owner** can read and write to it. |
| **Success Condition** | You successfully use `cat` and a pipe to `tr` to read and obfuscate the data, and a check using `ls -l` confirms the restrictive permissions. |

---

### Challenge 2: The Hot Wallet Exposure

**Core Concept:** Environment Variables, Process Hunting, and Pipelining.

**Explanation:** A Hot Wallet often leaves keys in a vulnerable state, such as in memory or as an environment variable (`WEB3_KEY`). An attacker can easily search the current shell environment to find and extract these values, compromising the wallet.

| Objective | Challenge Explanation |
| :--- | :--- |
| **Locate and extract a "leaked" private key from the shell environment.** | **Your Task:** <br> 1. **Setup:** The challenge environment simulates a vulnerable application using: `export WEB3_PRIVATE_KEY="0xdeadbeef"`. <br> 2. **Attack:** Use the command for printing exported variables and pipe (`|`) the output to `grep` to isolate the private key variable and its value. |
| **Success Condition** | Your single, piped command extracts the exact value: `0xdeadbeef`. |

---

### Challenge 3: Phishing Content Analysis

**Core Concept:** File Comparison and Filtering Text (`grep`).

**Explanation:** Phishing websites are often clones of legitimate sites, differing only in a few critical lines of code, such as the form's submission URL. By comparing the legitimate and malicious HTML files, you can quickly spot the subtle change that leads to a security failure.

| Objective | Challenge Explanation |
| :--- | :--- |
| **Identify the malicious code injection using file comparison.** | **Your Task:** <br> 1. **Setup:** Two files are provided: `legit_login.html` and `phish_login.html`. The phishing file has one line where the form action submits to a fake site. <br> 2. **Analyze:** Use the `diff` command to show the differences between the two files. <br> 3. **Filter:** Use the output of `diff` and pipe it to the `grep` command to isolate the line that contains the word "malicious" to pinpoint the exact failure. |
| **Success Condition** | You successfully use a `diff` and `grep` pipeline to output only the line containing the phishing destination. |

---

### Challenge 4: API Key Log Forensics (Breach Simulation)

**Core Concept:** Multi-stage Filtering, Pipelining, and Extracting Specific Text Sections.

**Explanation:** In a real exchange hack, security analysts must sift through massive server logs to find the single, unauthorized transaction. We use multi-stage filtering to narrow down thousands of lines to the one key element: the attacker's API key.

| Objective | Challenge Explanation |
| :--- | :--- |
| **Isolate the unauthorized API key from a large log file.** | **Your Task:** <br> 1. **Setup:** A large log file named `server_access.log` is provided. The malicious transaction is the only one containing both the tag `UNAUTHORIZED_WITHDRAWAL` and the string `API_KEY`. <br> 2. **Analyze:** Create a multi-stage command line using the pipe (`|`) to connect multiple `grep` commands, first filtering for `UNAUTHORIZED_WITHDRAWAL` and then for `API_KEY`. <br> 3. **Extract:** Use your knowledge of text extraction to output only the key itself: `BX0293J-MALICIOUS-KEY`. |
| **Success Condition** | Your complete command pipeline returns *only* the specific malicious API key string. |

---

### Challenge 5: Basic Signature Validation with a Shell Script

**Core Concept:** Shell Scripting, Arguments, Conditionals, and Reading Files.

**Explanation:** EIP-712 is about verifying that signed data has not been tampered with. We can simulate the failure of verification using a shell script that checks the integrity of the files. The goal is to prove understanding that a valid signature depends on the integrity of the signed data.

| Objective | Challenge Explanation |
| :--- | :--- |
| **Simulate a signature verification failure using a shell script.** | **Your Task:** <br> 1. **Setup:** You are given an executable, `verify.sh`, which fails if a signature is exactly 50 characters long. <br> 2. **Scripting:** Write a shell script (`check_sig.sh`) that takes a signature file as an argument and uses an `if/then/else` block to check if the character count (using `cat` and `wc -c`) is 50. <br> 3. **Execute:** Run your script on `good_sig.txt` (40 chars) and `bad_sig.txt` (50 chars), and correctly report which one will cause the verification failure. |
| **Success Condition** | Your shell script correctly predicts which file will fail validation based on the character count conditional. |