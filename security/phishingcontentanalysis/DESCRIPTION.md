# Phishing Content Analysis

## The Phishing Threat in Web3

**Phishing** is one of the most dangerous and common attack vectors in the cryptocurrency ecosystem. Attackers create fake websites that look nearly identical to legitimate services (MetaMask, Coinbase, Uniswap, OpenSea) to steal users' credentials, private keys, or trick them into sending funds to attacker-controlled wallets.

**The Statistics:**
- Over $100 million stolen through phishing attacks in 2023 alone
- 80% of crypto theft starts with phishing
- Average time to detect a phishing site: 12-24 hours
- Victims rarely recover stolen funds

## Common Phishing Techniques

### 1. Domain Spoofing
Using similar-looking domains that are easy to miss:
- Legitimate: `metamask.io`
- Phishing: `metarnask.io` (rn looks like m)
- Phishing: `metamask.io` (Cyrillic 'а' instead of Latin 'a')

### 2. Visual Cloning
Creating pixel-perfect copies of legitimate sites:
- Identical logos, colors, fonts
- Same page layout and structure
- Copied error messages and help text

### 3. Subtle Content Changes
The most dangerous type - everything looks legitimate except:
- Wallet addresses where funds are sent
- Smart contract addresses for token swaps
- Transaction confirmations
- One character different in a 42-character address

### 4. URL Manipulation
Using Unicode homoglyphs and look-alike characters:
- `һ` (Cyrillic) vs `h` (Latin)
- `а` (Cyrillic) vs `a` (Latin)
- `О` (Cyrillic) vs `O` (Latin)

## The `diff` Command: Finding Differences

The `diff` command compares two files line by line and shows what's different.

**Basic syntax:**
```console
hacker@dojo:~$ diff file1.txt file2.txt
```

**Example:**
```console
hacker@dojo:~$ diff legitimate.txt phishing.txt
3c3
< Send funds to: 0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb
---
> Send funds to: 0xDEADBEEF1234567890ABCDEF...
```

**Understanding the output:**
- `3c3` means "line 3 changed" (c = change)
- `<` shows content from the first file (legitimate.txt)
- `---` is a separator
- `>` shows content from the second file (phishing.txt)

**Other diff notations:**
- `5a6` - line added after line 5
- `7d6` - line 7 deleted
- `2,4c2,5` - lines 2-4 changed to lines 2-5

## Using `grep` with `diff`

You can filter diff output to find specific changes:

```console
hacker@dojo:~$ diff file1.txt file2.txt | grep ">"
> Send funds to: 0xDEADBEEF...
```

This shows only lines from the **second file** that are different.

```console
hacker@dojo:~$ diff file1.txt file2.txt | grep "0x"
< Send funds to: 0x742d35Cc6634C0532925a3b844Bc9e7595f0bEb
> Send funds to: 0xDEADBEEF1234567890ABCDEF...
```

This shows both lines containing wallet addresses.

## The Scenario

You're a security analyst at a cryptocurrency exchange. Multiple users have reported losing funds after "confirming" MetaMask transactions.

Upon investigation, you've obtained two HTML files:
1. **legitimate_metamask.html** - The real MetaMask transaction confirmation page
2. **phishing_metamask.html** - A suspected phishing page from a malicious site

The files look **visually identical**, but somewhere in the code there's a subtle change: the destination wallet address has been swapped to the attacker's address.

**Your mission:** Find the malicious wallet address that's stealing user funds.

## Your Task

Run the `phishingDetector` command to set up the challenge files. Then use `diff` to compare the legitimate and phishing HTML files to identify the exact line that was changed.

**The flag is embedded in the phishing wallet address.**

### Hints

1. The `phishingDetector` command will create two files for you to compare
2. Use `diff` to compare both HTML files
3. Look for lines showing destination wallet addresses
4. The `>` symbol in diff output shows content from the phishing file
5. Try combining with `grep` to filter for specific patterns
6. The malicious address contains the flag

### Commands You'll Need

```bash
# Compare two files
diff legitimate_metamask.html phishing_metamask.html

# Show only lines from the phishing file (second file)
diff legitimate_metamask.html phishing_metamask.html | grep ">"

# Filter for wallet addresses (0x pattern)
diff legitimate_metamask.html phishing_metamask.html | grep "0x"

# Show just the changed lines with context
diff -u legitimate_metamask.html phishing_metamask.html
```

## Real-World Phishing Detection

In production environments, security teams use:

**Automated Tools:**
- **PhishTank** - Community-driven phishing site database
- **Google Safe Browsing** - Real-time phishing detection API
- **MetaMask's phishing detector** - Checks domains against known phishing lists
- **OpenPhish** - Machine learning phishing detection

**Manual Analysis:**
- Visual inspection of page source
- SSL certificate verification
- WHOIS domain registration checks
- File hash comparison
- Network traffic analysis

**Browser Extensions:**
- **MetaMask** - Built-in phishing detection
- **Pocket Universe** - Transaction simulation before signing
- **Fire** - Warns about malicious smart contracts
- **Wallet Guard** - Blocks known phishing sites

## Security Best Practices

**DO:**
- Always verify URLs character by character before entering credentials
- Bookmark legitimate sites and only use bookmarks
- Check SSL certificates (look for the padlock icon)
- Verify contract addresses on multiple block explorers
- Use hardware wallets with address verification on-device
- Double-check wallet addresses before confirming transactions
- Enable transaction simulation (Pocket Universe, Fire)

**DON'T:**
- Click links in emails, Discord, Telegram, or Twitter DMs
- Trust sites from Google search results (attackers buy ads)
- Ignore browser security warnings
- Rush through transaction confirmations
- Share your screen during transactions
- Enter seed phrases anywhere except your hardware wallet

**Critical Rule:** If a site asks for your seed phrase, it's 100% a scam. Legitimate services never ask for seed phrases.

## Real-World Examples

**1. Fake Uniswap (2023):** $8M stolen via fake swap interface
**2. MetaMask Phishing (2022):** Thousands of users lost funds to fake "verify wallet" pages
**3. OpenSea Clone (2022):** Users tricked into listing NFTs on fake marketplace
**4. Ledger Phishing (2021):** Fake firmware update emails led to seed phrase theft

**Remember:** In crypto, you are your own bank. There's no customer support to reverse fraudulent transactions. Once your private keys are compromised or you send funds to an attacker, they're gone forever.

Stay vigilant, verify everything, and when in doubt, don't click!
