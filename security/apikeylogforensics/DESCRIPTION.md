# API Key Log Forensics

## The Logging Vulnerability

Server logs are essential for debugging, monitoring, and security analysis. However, they can also become a **massive security liability** when sensitive information is accidentally logged.

**Common Secrets Leaked in Logs:**
- API keys and access tokens
- Private keys and wallet seeds
- User passwords and session tokens
- Database credentials
- OAuth tokens and JWT secrets
- Credit card numbers (PCI compliance violation)

**The Problem:** A single exposed API key buried in millions of log lines can lead to:
- Complete system compromise
- Data breaches affecting millions of users
- Cryptocurrency wallet drains
- Unauthorized access to cloud resources
- Regulatory fines (GDPR, PCI-DSS violations)

## Real-World Log Security Incidents

**Uber (2016):** Engineers stored AWS keys in private GitHub repo, which were then logged. Cost: $148M settlement.

**Capital One (2019):** Misconfigured logging exposed 100M customer records. Cost: $80M fine.

**DeFi Protocol Exploit (2022):** API key logged in error messages. Result: $3.6M stolen.

**Docker Hub (2021):** Authentication tokens exposed in container logs. Result: 190,000 accounts compromised.

## The Scenario

You're a security analyst at a Web3 infrastructure company. Yesterday morning, attackers drained $500,000 from the company's hot wallet using an unauthorized API key.

Your job: Find the compromised API key that was accidentally logged during a security incident.

**The challenge:** The log file contains **over 50,000 lines** of mixed operational logs, errors, warnings, and debug messages from various services.

## The `grep` Command: Searching Through Noise

`grep` is a powerful command-line tool for searching text using patterns.

**Basic syntax:**
```console
hacker@dojo:~$ grep "pattern" filename.txt
```

**Example:**
```console
hacker@dojo:~$ grep "ERROR" server.log
[2024-01-15 10:23:45] [ERROR] NetworkService: Connection timeout
[2024-01-15 10:24:12] [ERROR] APIGateway: Rate limit exceeded
[2024-01-15 10:25:33] [ERROR] WalletService: Transaction failed
```

## Pipelining: Multi-Stage Filtering

The real power of `grep` comes from **pipelining** - chaining multiple grep commands together to progressively narrow down results.

**Pipe symbol `|`:** Sends output from one command as input to the next command.

**Example - Three-stage filter:**
```console
hacker@dojo:~$ cat server.log | grep "ERROR" | grep "API" | grep "KEY"
```

**How it works:**
1. `cat server.log` - Reads the entire file (50,000+ lines)
2. `| grep "ERROR"` - Filters to only ERROR level logs (~500 lines)
3. `| grep "API"` - Further filters to API-related errors (~50 lines)
4. `| grep "KEY"` - Final filter for lines containing "KEY" (~1 line)

**More efficient syntax (skip cat):**
```console
hacker@dojo:~$ grep "ERROR" server.log | grep "UNAUTHORIZED" | grep "API_KEY"
```

## Log Levels Explained

**DEBUG:** Verbose developer information (usually too detailed)
- Example: "Cache hit for key: wallet_balance_abc123"

**INFO:** General informational messages
- Example: "Transaction added to pool: 0x1234..."

**WARN:** Warning messages that aren't errors yet
- Example: "Rate limit approaching for IP: 192.168.1.1"

**ERROR:** Error events that need attention
- Example: "Connection timeout to peer node"

**CRITICAL:** Severe errors requiring immediate action
- Example: "Database connection pool exhausted"

## Your Task

Run the `logForensics` command to generate the breach log file.

Then, use multi-stage `grep` pipelining to:
1. Filter the 50,000+ line log to only ERROR entries
2. Further filter to UNAUTHORIZED access attempts
3. Finally, extract the line containing the compromised API_KEY

**The flag is embedded in the API key value.**

### Hints

1. The `logForensics` command will create a large log file for you
2. Start by filtering for ERROR level logs
3. The breach involved "UNAUTHORIZED" access
4. Look for a line containing "API_KEY="
5. Use pipes (|) to chain grep commands together
6. Each stage should significantly reduce the number of lines

### Commands You'll Need

```bash
# Count total lines in the log
wc -l ~/web3_server.log

# Filter for ERROR logs and count them
grep "ERROR" ~/web3_server.log | wc -l

# Three-stage pipeline to find the API key
grep "ERROR" ~/web3_server.log | grep "UNAUTHORIZED" | grep "API_KEY"

# Alternative: Use regex for more precise matching
grep -E "ERROR.*UNAUTHORIZED.*API_KEY" ~/web3_server.log

# Show line numbers with matches
grep -n "UNAUTHORIZED" ~/web3_server.log

# Case-insensitive search
grep -i "api_key" ~/web3_server.log
```

## Advanced `grep` Options

**`grep -n`:** Show line numbers
```console
hacker@dojo:~$ grep -n "ERROR" server.log
523:[2024-01-15 10:23:45] [ERROR] Connection timeout
1247:[2024-01-15 11:15:22] [ERROR] Invalid token
```

**`grep -i`:** Case-insensitive search
```console
hacker@dojo:~$ grep -i "api" server.log
# Matches API, api, Api, etc.
```

**`grep -c`:** Count matching lines
```console
hacker@dojo:~$ grep -c "ERROR" server.log
523
```

**`grep -v`:** Invert match (show lines that DON'T match)
```console
hacker@dojo:~$ grep -v "DEBUG" server.log
# Show all logs except DEBUG level
```

**`grep -A 3`:** Show 3 lines AFTER match
**`grep -B 3`:** Show 3 lines BEFORE match
**`grep -C 3`:** Show 3 lines of context (before and after)

## Production Log Security Best Practices

### DO:

**Log Sanitization:**
- Strip sensitive data before logging
- Use placeholder values: `API_KEY=***REDACTED***`
- Implement structured logging (JSON) with field filtering

**Secure Storage:**
- Encrypt logs at rest
- Restrict access with IAM policies
- Use log aggregation services (ELK, Splunk, Datadog)
- Implement log rotation and retention policies

**Monitoring:**
- Set up alerts for suspicious patterns
- Monitor for leaked credentials in logs
- Scan logs for accidental PII exposure
- Use automated secret scanning tools

### DON'T:

- Log full API keys, passwords, or private keys
- Store logs in world-readable locations
- Keep logs indefinitely without review
- Log request/response bodies without sanitization
- Include user PII in debug logs
- Disable logging in production (you need it for security!)

## Log Forensics Tools

**For Local Analysis:**
- `grep` - Pattern matching (what we're using!)
- `awk` - Text processing and filtering
- `sed` - Stream editing and substitution
- `jq` - JSON log parsing
- `cut`, `sort`, `uniq` - Data manipulation

**For Production:**
- **ELK Stack** (Elasticsearch, Logstash, Kibana) - Log aggregation and search
- **Splunk** - Enterprise log management and SIEM
- **Datadog** - Cloud monitoring and log analytics
- **AWS CloudWatch** - AWS-native log management
- **Google Cloud Logging** - GCP log aggregation
- **Grafana Loki** - Open-source log aggregation

## The Investigation Process

1. **Understand the incident:** API key was used to drain hot wallet
2. **Identify the timeframe:** Breach occurred yesterday morning
3. **Locate relevant logs:** server.log contains all service logs
4. **Filter progressively:** ERROR → UNAUTHORIZED → API_KEY
5. **Extract evidence:** Find the exact API key used
6. **Report findings:** Document the compromised credential

## Security Lessons

**Why was the API key logged?**
- Developer left debug logging enabled in production
- Error handler printed full request context
- Exception stack trace included environment variables
- Middleware logged all API request headers

**How to prevent this:**
- Use secret management services (Vault, AWS Secrets Manager)
- Implement log sanitization middleware
- Review all logging statements before deployment
- Set up automated secret scanning (GitGuardian, TruffleHog)
- Regular security audits of logging practices
- Train developers on secure logging

**Remember:** Logs are permanent. Once a secret is logged, assume it's compromised. Rotate keys immediately, review access logs, and implement monitoring.

In production systems, security teams often scan logs retroactively for accidentally exposed secrets. This challenge simulates that real-world forensics workflow!
