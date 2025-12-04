# The Hot Wallet Exposure

## What is a Hot Wallet?

A **hot wallet** is a cryptocurrency wallet that's connected to the internet and actively used for transactions. Unlike cold storage (offline wallets), hot wallets prioritize convenience over security, making them vulnerable to various attacks.

**The Risk:** Hot wallets are especially vulnerable when private keys are exposed through:
- Environment variables
- Log files
- Process memory dumps
- Temporary files
- Error messages

## Environment Variables: A Hidden Threat

In Linux, environment variables are dynamic values that affect running processes. Developers sometimes make a critical mistake: storing sensitive information (API keys, passwords, **private keys**) in environment variables.

**Why is this dangerous?**
1. Environment variables are **inherited by child processes** - any program you run can see them
2. They can be **accidentally logged** by applications or system tools
3. They're **visible to anyone** who can run commands on the system
4. Many debugging tools and error messages **dump environment variables**
5. They persist in shell history and process listings

### Real-World Example

A developer might do this thinking it's "secure":
```bash
export WALLET_PRIVATE_KEY="0x1234567890abcdef..."
```

But now ANY process can access it:
```bash
# Other users or processes can see it
ps aux -e  # Shows environment variables of all processes
/proc/PID/environ  # Kernel exposes env vars in filesystem
```

## Viewing Environment Variables

### The `env` Command

The `env` command displays all environment variables in your current shell:

```console
hacker@dojo:~$ env
USER=hacker
HOME=/home/hacker
PATH=/usr/local/bin:/usr/bin:/bin
SHELL=/bin/bash
WALLET_PRIVATE_KEY=0xABCD1234...
...
```

### The `grep` Command for Searching

Since `env` outputs many variables, we use `grep` to filter:

```console
hacker@dojo:~$ env | grep WALLET
WALLET_PRIVATE_KEY=0xABCD1234567890...
```

**How this works:**
- `env` lists all environment variables
- `|` (pipe) sends the output to the next command
- `grep WALLET` searches for lines containing "WALLET"

### Other Useful Commands

**`printenv`** - Another way to display environment variables:
```console
hacker@dojo:~$ printenv WALLET_PRIVATE_KEY
0xABCD1234567890...
```

**Direct variable access:**
```console
hacker@dojo:~$ echo $WALLET_PRIVATE_KEY
0xABCD1234567890...
```

## The Scenario

You're a security analyst investigating a cryptocurrency theft. A careless developer exported their wallet's private key as an environment variable named `WALLET_PRIVATE_KEY` during development.

The private key is still exposed in the environment, and you need to find it before an attacker does.

## Your Task

Run `bin/walletExposure` to set up the challenge environment. This will export the `WALLET_PRIVATE_KEY` variable to your shell configuration.

Use `grep` to search through the environment variables and locate the exposed `WALLET_PRIVATE_KEY`.

**Optional:** Run the `walletExposure` command to see challenge instructions and hints.

**The flag is embedded in the private key value.**

### Hints

1. Use the `env` command to list all environment variables
2. Pipe the output to `grep` to search for patterns: `env | grep PATTERN`
3. Look for a variable named `WALLET_PRIVATE_KEY`
4. The private key contains your flag

### Commands You'll Need

```bash
# List all environment variables
env

# Search for a specific pattern
env | grep WALLET

# Alternative approach
printenv | grep WALLET
```

## Security Best Practices

**DO:**
- Use **hardware wallets** (Ledger, Trezor) for storing private keys
- Use **secret management tools** (HashiCorp Vault, AWS Secrets Manager, 1Password)
- Use **encrypted configuration files** with restricted permissions
- Keep private keys in **cold storage** for long-term holdings
- Use **environment-specific secrets** that are never committed to version control

**DON'T:**
- Store private keys in environment variables
- Log environment variables in application logs
- Share environment variables across services
- Commit `.env` files to Git repositories
- Use the same keys in development and production

**Remember:** In production Web3 applications, use proper key management systems and hardware security modules (HSMs). Never expose private keys in environment variables, even "temporarily" during development!
