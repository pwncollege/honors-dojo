# Basic Signature Validation

## Digital Signatures in Web3

In cryptocurrency and blockchain systems, **digital signatures** are the fundamental mechanism that proves ownership and authorization. Every transaction you make with your crypto wallet is digitally signed with your private key.

**What a digital signature proves:**
1. **Authentication:** The message was signed by the owner of the private key
2. **Integrity:** The message wasn't altered after being signed
3. **Non-repudiation:** The signer cannot deny having signed it

**Without signatures, crypto wouldn't work** - anyone could spend anyone else's funds!

## How Digital Signatures Work

### The Process

1. **Transaction Creation:** You want to send 1 ETH to someone
2. **Hashing:** The transaction data is hashed into a fixed-size digest
3. **Signing:** Your private key encrypts the hash, creating a signature
4. **Broadcasting:** Transaction + signature sent to the network
5. **Verification:** Nodes use your public key to verify the signature

### The Math (Simplified)

Ethereum uses **ECDSA** (Elliptic Curve Digital Signature Algorithm) with the secp256k1 curve:

- **Private Key:** A random 256-bit number (keep secret!)
- **Public Key:** Derived from private key using elliptic curve math
- **Wallet Address:** Last 20 bytes of the Keccak-256 hash of the public key
- **Signature:** 65 bytes (r, s, v values from ECDSA)

**Ethereum Signature Format:**
```
0x + 64 hex characters = 66 total characters
Example: 0xabcdef1234567890abcdef1234567890abcdef1234567890abcdef12345678
```

## Shell Scripting with Conditionals

For this challenge, we'll simulate signature validation using bash conditionals. Real validation uses cryptographic libraries, but the **conditional logic pattern** is the same.

### Basic If/Then/Else Structure

```bash
#!/bin/bash

if [ condition ]; then
    # Code if condition is true
    echo "Condition met!"
else
    # Code if condition is false
    echo "Condition not met"
fi
```

### Variable Assignment

```bash
# Read file content into a variable
CONTENT=$(cat filename.txt)

# Get character count
LENGTH=$(echo -n "$CONTENT" | wc -c)

# Command line arguments
FIRST_ARG=$1
SECOND_ARG=$2
```

### Comparison Operators

**Numeric Comparisons:**
- `-eq` → equal to
- `-ne` → not equal to
- `-lt` → less than
- `-le` → less than or equal to
- `-gt` → greater than
- `-ge` → greater than or equal to

**String Comparisons:**
- `=` → equal to
- `!=` → not equal to
- `-z` → string is empty
- `-n` → string is not empty

**Examples:**
```bash
if [ $NUMBER -eq 42 ]; then
    echo "The answer!"
fi

if [ "$STRING" = "hello" ]; then
    echo "Greeting found"
fi

if [ $COUNT -gt 100 ]; then
    echo "More than 100"
fi
```

## The Challenge

In this challenge, you'll write a bash script that validates Ethereum signatures by checking their format.

### The Scenario

You're building a transaction validator for a Web3 application. Before attempting cryptographic verification (which is expensive), you need to check if signatures have the correct format.

**Valid Ethereum signatures must be exactly 66 characters:**
- `0x` prefix (2 characters)
- 64 hexadecimal characters

**Your task:** Write a validation script that:
1. Reads a transaction file
2. Reads a signature file (passed as argument)
3. Counts the signature's characters
4. Checks if it's exactly 66 characters
5. Awards the flag if valid, shows error if invalid

## Your Task

Run the `signatureValidator` command to set up the challenge files.

Then, write a bash script called `validate.sh` that implements the validation logic using `if/then/else` conditionals.

**The flag will be awarded when your script correctly validates the signature format.**

### Files Provided

After running `signatureValidator`, you'll have:
- `transaction.txt` - A JSON transaction object
- `valid_signature.txt` - A properly formatted signature (66 chars)
- `invalid_signature.txt` - An improperly formatted signature (wrong length)

### Hints

1. Use `wc -c` to count characters in a file
2. Use `echo -n "$VAR" | wc -c` to count variable length
3. Ethereum signatures are exactly 66 characters
4. Use `-eq` for numeric equality in bash
5. The script should accept a filename as its first argument (`$1`)
6. Make your script executable with `chmod +x validate.sh`

### Script Template

Here's the structure (you need to fill in the logic):

```bash
#!/bin/bash

# Read the transaction (for context)
TRANSACTION=$(cat ~/transaction.txt)

# Get signature filename from first argument
SIGNATURE_FILE=$1

# Read the signature content
SIGNATURE=$(cat "$SIGNATURE_FILE")

# Count signature length
SIG_LENGTH=$(echo -n "$SIGNATURE" | wc -c)

# Validate length
if [ $SIG_LENGTH -eq 66 ]; then
    echo "✓ Valid signature format!"
    echo "✓ Length correct: 66 characters"
    echo "✓ Transaction can proceed"
    # Award flag here
else
    echo "✗ Invalid signature format"
    echo "✗ Expected: 66 characters"
    echo "✗ Got: $SIG_LENGTH characters"
    echo "✗ Transaction rejected"
fi
```

## Real-World Signature Verification

In production systems, signature verification involves cryptographic operations:

### JavaScript (ethers.js)

```javascript
const ethers = require('ethers');

// Message to sign
const message = "Transfer 1 ETH";

// Sign with private key
const wallet = new ethers.Wallet(privateKey);
const signature = await wallet.signMessage(message);

// Verify signature
const recoveredAddress = ethers.utils.verifyMessage(message, signature);
console.log(recoveredAddress === wallet.address); // true
```

### Python (web3.py)

```python
from eth_account import Account
from eth_account.messages import encode_defunct

# Message to sign
message = encode_defunct(text="Transfer 1 ETH")

# Sign with private key
signed_message = Account.sign_message(message, private_key)
signature = signed_message.signature.hex()

# Verify signature
recovered_address = Account.recover_message(message, signature=signature)
print(recovered_address == wallet_address)  # True
```

### Solidity (Smart Contract)

```solidity
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract SignatureVerifier {
    function verifySignature(
        bytes32 messageHash,
        bytes memory signature,
        address signer
    ) public pure returns (bool) {
        // Recover signer address from signature
        address recovered = recoverSigner(messageHash, signature);
        return recovered == signer;
    }

    function recoverSigner(
        bytes32 messageHash,
        bytes memory signature
    ) internal pure returns (address) {
        (bytes32 r, bytes32 s, uint8 v) = splitSignature(signature);
        return ecrecover(messageHash, v, r, s);
    }
}
```

## Security Implications

**Why signature validation matters:**

**Without Validation:**
- Malformed signatures could crash your app
- Attackers could bypass authentication
- Invalid transactions processed
- Gas wasted on verification attempts

**With Validation:**
- Early rejection of invalid signatures
- Reduced computational cost
- Better error messages for users
- Protection against malformed input attacks

**Real attacks prevented by validation:**
- **Replay attacks:** Reusing signatures on different chains
- **Signature malleability:** Modifying signature values
- **Invalid parameter attacks:** Crafted inputs to break verification
- **DoS attacks:** Flooding with invalid signatures

## Advanced Bash Scripting

### File Tests

```bash
if [ -f filename.txt ]; then
    echo "File exists"
fi

if [ -r filename.txt ]; then
    echo "File is readable"
fi

if [ -x script.sh ]; then
    echo "File is executable"
fi
```

### Logical Operators

```bash
# AND
if [ $AGE -gt 18 ] && [ $AGE -lt 65 ]; then
    echo "Working age"
fi

# OR
if [ $DAY = "Saturday" ] || [ $DAY = "Sunday" ]; then
    echo "Weekend!"
fi

# NOT
if [ ! -f temp.txt ]; then
    echo "Temp file doesn't exist"
fi
```

### Case Statements

```bash
case $RESPONSE in
    yes|YES|y|Y)
        echo "Proceeding..."
        ;;
    no|NO|n|N)
        echo "Cancelled"
        ;;
    *)
        echo "Invalid response"
        ;;
esac
```

## Testing Your Script

```bash
# Create your validation script
nano validate.sh

# Make it executable
chmod +x validate.sh

# Test with valid signature (should succeed)
./validate.sh ~/valid_signature.txt

# Test with invalid signature (should fail with error)
./validate.sh ~/invalid_signature.txt
```

### Expected Outputs

**Valid Signature:**
```
✓ Valid signature format!
✓ Length correct: 66 characters
✓ Transaction can proceed
pwn{...your_flag...}
```

**Invalid Signature:**
```
✗ Invalid signature format
✗ Expected: 66 characters
✗ Got: 9 characters
✗ Transaction rejected
```

## Security Best Practices

**DO:**
- Always validate input before cryptographic operations
- Check signature format (length, encoding, structure)
- Verify signatures match expected addresses
- Implement replay protection (nonces, chainID)
- Use hardware wallets for signing high-value transactions
- Test signature verification with known test vectors

**DON'T:**
- Skip format validation ("it's probably fine")
- Trust user-provided signatures without verification
- Reuse signatures across different chains
- Store private keys in code or environment variables
- Implement your own cryptography (use audited libraries)

**Remember:** In Web3, signature verification is the only thing protecting your funds. Every transaction must be properly signed and verified. A single bypass could mean complete loss of funds with no recovery possible!
