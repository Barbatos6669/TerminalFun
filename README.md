# Raspberry Pi Monitor

A lightweight real-time system monitor for Raspberry Pi written in C++.

## Features

- **CPU Temperature** - Real-time CPU temperature monitoring
- **CPU Usage** - Live CPU usage percentage
- **RAM Usage** - Memory consumption tracking
- **Disk Usage** - Storage utilization monitoring
- **System Uptime** - Formatted uptime display (HH:MM:SS)
- **Auto-refresh** - Configurable refresh rate

## Requirements

- Raspberry Pi (or any Linux system)
- G++ compiler
- C++11 or later

## Installation

1. Clone the repository:
```bash
git clone https://github.com/Barbatos6669/TerminalFun.git
cd TerminalFun
```

2. Build the project:
```bash
chmod +x build.sh
./build.sh
```

3. Run the monitor:
```bash
./monitor
```

## Usage

The monitor displays system stats in real-time with a 1-second refresh rate. Press `Ctrl+C` to exit.

## Configuration

You can adjust the refresh rate by modifying the `refreshrate` variable in `main.cpp`:
```cpp
int refreshrate = 1; // Refresh every 1 second
```

## How It Works

The monitor reads system information from various Linux kernel interfaces:
- `/sys/class/thermal/thermal_zone0/temp` - CPU temperature
- `/proc/stat` - CPU usage statistics
- `/proc/meminfo` - Memory information
- `/proc/uptime` - System uptime
- `statvfs()` - Disk usage

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Contributing

Pull requests are welcome! Feel free to submit issues or suggestions.

## Author

Built with ❤️ on Raspberry Pi
