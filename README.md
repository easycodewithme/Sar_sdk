# SAR SDK

![Version](https://img.shields.io/badge/version-0.1.0-blue.svg)
![Python](https://img.shields.io/badge/python-3.7%2B-blue.svg)
![License](https://img.shields.io/badge/license-Proprietary-red.svg)

A Python Software Development Kit (SDK) for controlling SAR (Soft Adaptive Robotic) grippers over TCP/IP connections.

## Overview

The SAR SDK provides a simple and intuitive interface for controlling SAR grippers, allowing you to:

- Open and close the gripper with precise control
- Set velocity, stroke range, and maximum contact force
- Monitor gripper status and position
- Wait for grip operations to complete

## Prerequisites

Before installing and using the SAR SDK, ensure you have:

- **Python 3.7 or higher** installed on your system
- **Network connectivity** to the SAR gripper device
- Basic knowledge of Python programming (for custom implementations)
- SAR gripper hardware with TCP/IP connectivity

## Installation

### Option 1: Using pip (Recommended)

The simplest way to install the SAR SDK is using pip:

```bash
pip install sar_sdk
```

### Option 2: Installing from Source

For the latest development version or if you want to modify the SDK:

```bash
# Clone the repository
git clone https://github.com/dexsent/sar_sdk.git

# Navigate to the project directory
cd sar_sdk

# Install the package in development mode
pip install -e .
```

## Quick Start

Here's a simple example to get you started with controlling your SAR gripper:

```python
from sar_sdk import SARModule
import time

# Initialize the SAR module (connects to default IP and port)
sar = SARModule()

# Close the gripper
sar.grip_close()

# Wait for the closing operation to complete
sar.wait_until(sar.is_grasp_attempt_complete)

# Wait for 2 seconds while holding the grip
time.sleep(2)

# Open the gripper
sar.grip_open()

# Wait for the opening operation to complete
sar.wait_until(sar.is_open_attempt_complete)

# Clean up
sar.exit()
```

## Configuration

By default, the SDK connects to IP address `10.42.0.53` on port `4196`. You can specify different connection parameters if needed:

```python
# Connect to a custom IP and port
sar = SARModule(esp_ip="192.168.1.100", esp_port=4200)
```

## Documentation

For detailed documentation, examples, and troubleshooting, please refer to our [Wiki](https://github.com/dexsent/sar_sdk/wiki).

- [Installation Guide](https://github.com/dexsent/sar_sdk/wiki/Installation)
- [Getting Started](https://github.com/dexsent/sar_sdk/wiki/Getting-Started)
- [API Reference](https://github.com/dexsent/sar_sdk/wiki/API-Reference)
- [Examples](https://github.com/dexsent/sar_sdk/wiki/Examples)
- [Troubleshooting](https://github.com/dexsent/sar_sdk/wiki/Troubleshooting)

## Support

If you encounter any issues or have questions, please:

1. Check the [Troubleshooting](https://github.com/dexsent/sar_sdk/wiki/Troubleshooting) guide
2. Search for similar [Issues](https://github.com/dexsent/sar_sdk/issues) on GitHub
3. Contact support at [dexsentrobotics@gmail.com](mailto:dexsentrobotics@gmail.com)

## License

This software is proprietary and is licensed under Sastra Innovation Labs.

© 2025 Dexsent Robotics. All rights reserved.
