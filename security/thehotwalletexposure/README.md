# Challenge 2: The Hot Wallet Exposure - Solution

## Objective
Locate and extract a private key stored as an environment variable using `grep`.

## Solution

### Method 1: Using env and grep
```bash
env | grep WALLET
```

**Output:**
```
WALLET_PRIVATE_KEY=0x1234567890abcdef_FLAG:pwn.college{...}
```

### Method 2: Using printenv
```bash
printenv | grep WALLET
```

### Method 3: Direct variable access
```bash
echo $WALLET_PRIVATE_KEY
```

### Method 4: Searching the .wallet_config file
```bash
cat ~/.wallet_config | grep WALLET_PRIVATE_KEY
```

## Explanation

### How the Environment Variable Got There

The `.init` script ran before your session started and added this line to your `.bashrc`:
```bash
export WALLET_PRIVATE_KEY="0x1234567890abcdef_FLAG:pwn.college{...}"
```

When you logged in, `.bashrc` executed and exported the variable to your shell environment.

### Why `env | grep WALLET` Works

- `env` - Lists all environment variables in the current shell
- `|` - Pipes the output to the next command
- `grep WALLET` - Searches for lines containing "WALLET"

This combination filters the long list of environment variables to show only those related to wallets.

## Key Learnings

1. **Environment variables are not secret storage** - They're visible to any process
2. **Use `env | grep` to search environment variables** - Essential forensics skill
3. **Developers should never export credentials** - Major security vulnerability
4. **Use dedicated secret management tools in production** - Vault, AWS Secrets Manager, etc.

## Security Best Practices

### ✅ DO:
- Use secret management services (HashiCorp Vault, AWS Secrets Manager)
- Encrypt sensitive configuration files
- Use hardware wallets for private keys
- Implement principle of least privilege
- Store secrets in secure enclaves or HSMs

### ❌ DON'T:
- Store private keys in environment variables
- Commit secrets to version control (.env files in git)
- Log environment variables in application logs
- Share credentials through insecure channels
- Use the same keys in development and production

## Real-World Examples

### Environment Variable Leaks in Production

1. **Docker Logs Exposure**
   - Private keys in `ENV` variables get logged by Docker
   - Logs are often sent to centralized logging systems
   - Anyone with log access can extract keys

2. **CI/CD Pipeline Leaks**
   - Build logs may print environment variables for debugging
   - Keys exposed in GitHub Actions, Jenkins, CircleCI logs
   - Public repositories = public keys

3. **Error Messages**
   - Stack traces often dump environment state
   - Error reporting tools (Sentry, Rollbar) capture env vars
   - Keys exposed in bug reports

### Better Alternatives

```bash
# ❌ BAD: Environment variable
export PRIVATE_KEY="0xABC123..."

# ✅ GOOD: Encrypted file with restricted permissions
chmod 600 ~/.wallet/keystore.enc
# Decrypt in memory only when needed

# ✅ BETTER: Hardware wallet
# Keys never leave the device

# ✅ BEST: Secret management service
vault kv get secret/wallet/private-key
```

## Additional Commands for Exploration

```bash
# List ALL environment variables
env

# Search for any crypto-related variables
env | grep -i "key\|wallet\|seed\|private"

# Check process environment (if you know the PID)
cat /proc/PID/environ | tr '\0' '\n' | grep WALLET

# Check your .bashrc for exported variables
cat ~/.bashrc | grep export
```
