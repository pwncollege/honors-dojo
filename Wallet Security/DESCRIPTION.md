# Web3 Wallet Security Fundamentals: A Linux Command Line Approach

A practical, hands-on module focused on Web3/Crypto wallet security, using only the Linux command-line utilities you have learned in class(CSE365).

- **Objective:** Learn fundamental and advanced wallet security concepts by using core Linux commands to simulate real-world security failures and forensic analysis.
- **Commands Used:** `cat`, `grep`, `diff`, `touch`, `tr`, `chmod`, Pipelining, Shell Scripting with Conditionals (`if/then/else`), and Environment Variable usage.

### Challenge Progression

| Challenge Name | Core Concept | Key Commands Used |
| :--- | :--- | :--- |
| **1. Securing the Seed Phrase** | Cold Storage Simulation, File Permissions, Simple Obfuscation | `touch`, `cat`, `tr` (Translating chars), `chmod` (Changing Permissions) |
| **2. The Hot Wallet Exposure** | Environment Variable Attacks, Private Key Leakage | `grep` (on Exported Variables) |
| **3. Phishing Content Analysis** | Content Forensics, Identifying Subtle Fraud | `diff` (comparing files), `grep` |
| **4. API Key Log Forensics** | Multi-Stage Log Filtering, Data Pipelining | `grep` (Pipelining/Grepping live output), Text Extraction |
| **5. Basic Signature Validation** | Integrity Check Simulation, Scripting Logic | `Scripting with Conditionals` (`if/then/else`), `cat` |

It is recommended to have a solid understanding of the commands listed above to successfully complete this module.

This module was created by [Jacob Blemaster](https://github.com/j-ble).