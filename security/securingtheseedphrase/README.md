# Challenge 1: Securing the Seed Phrase - Solution

## Objective
Create an obfuscated seed phrase file with proper permissions using `tr` and `chmod`.

## Solution Commands

Run the following commands in your terminal to solve the challenge:

```bash
# Step 1: Create a file with the dummy seed phrase
echo "word one two three four five six seven eight nine ten eleven twelve" > my_seed.txt

# Step 2: Obfuscate using tr (ROT13 cipher)
cat my_seed.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m' > obfuscated_seed.txt

# Step 3: Set file permissions to owner-only (600)
chmod 600 obfuscated_seed.txt

# Step 4: Run the validator to get the flag
seedPhrase
```

## Explanation

### Step 1: Create the seed phrase file
```bash
echo "word one two three four five six seven eight nine ten eleven twelve" > my_seed.txt
```
- Creates `my_seed.txt` containing the dummy 12-word seed phrase
- This simulates storing your actual seed phrase initially

### Step 2: Obfuscate with ROT13
```bash
cat my_seed.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m' > obfuscated_seed.txt
```
- `cat my_seed.txt` reads the original file
- `|` pipes the output to the next command
- `tr 'A-Za-z' 'N-ZA-Mn-za-m'` performs ROT13 character translation
  - Each letter is rotated 13 positions in the alphabet
  - 'a' becomes 'n', 'b' becomes 'o', etc.
  - Numbers and spaces remain unchanged
- `> obfuscated_seed.txt` saves the obfuscated output

**Example transformation:**
```
Original: word one two
ROT13:    jbeq bar gjb
```

### Step 3: Set permissions to 600
```bash
chmod 600 obfuscated_seed.txt
```
- Sets file permissions to `rw-------` (owner read/write only)
- `6` = read (4) + write (2) for owner
- `0` = no permissions for group
- `0` = no permissions for others

**Verify permissions:**
```bash
ls -l obfuscated_seed.txt
# Should show: -rw------- ... obfuscated_seed.txt
```

### Step 4: Validate and get flag
```bash
seedPhrase
```
The validator script checks:
1. ✓ `obfuscated_seed.txt` exists
2. ✓ Content is ROT13-encoded
3. ✓ Permissions are exactly 600

If all checks pass, you'll see:
```
Success! Here is your flag:
pwn{...}
```

## Key Learnings

### `tr` Command
- **Purpose:** Translate or delete characters
- **ROT13:** Simple substitution cipher (not secure, just obfuscation)
- **Usage:** `tr 'SET1' 'SET2'`

### `chmod` Command
- **Purpose:** Change file permissions
- **Format:** `chmod [permissions] [file]`
- **Octal notation:**
  - 4 = read (r)
  - 2 = write (w)
  - 1 = execute (x)
  - Sum for combinations: 6 = read + write

### File Permissions
```
Permission  Octal  Meaning
----------  -----  -------
-rw-------  600    Owner: read/write, Group: none, Others: none
-rw-r--r--  644    Owner: read/write, Group: read, Others: read
-rwx------  700    Owner: read/write/execute, Group: none, Others: none
```

## Security Best Practices

### ✅ DO:
- **Use hardware wallets** for seed phrase storage
- **Write seed phrases on paper** and store in secure location (safe, vault)
- **Use cold storage** for long-term holdings
- **Verify file permissions** on sensitive files
- **Never store seed phrases digitally** in plain text

### ❌ DON'T:
- **Don't store in cloud** (Google Drive, Dropbox, iCloud)
- **Don't email seed phrases** to yourself
- **Don't take screenshots** of seed phrases
- **Don't use weak permissions** (world-readable files)
- **Don't share** seed phrases with anyone

## Real-World Analogy

Think of your seed phrase like:
- 🏦 **Bank vault combination** - Keep it secret and secure
- 🔑 **Master key** - One key controls everything
- 💎 **Irreplaceable treasure** - Once lost, funds are gone forever

**Remember:** In real cryptocurrency:
- ROT13 is NOT secure encryption (easily reversible)
- Professional solutions use proper encryption (AES-256, etc.)
- Hardware wallets (Ledger, Trezor) are the gold standard