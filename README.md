# Air Quality Monitoring System

[![Java](https://img.shields.io/badge/Java-8-orange.svg)](https://www.java.com)
[![Maven](https://img.shields.io/badge/Maven-3.6+-blue.svg)](https://maven.apache.org)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Open Source](https://img.shields.io/badge/Open%20Source-Yes-brightgreen.svg)](https://opensource.org)

> Open-source air quality monitoring system - Comprehensive solution integrating data collection, calibration, and API server

## 📋 Project Overview

An open-source air quality monitoring platform originally developed in collaboration with Korea Testing & Research Institute (KTR) and Paichai University PCU Lab. Provides complete pipeline from data collection (AirKorea API integration, sensor communication) to multi-sensor calibration and REST API server.

## 🏗 Project Structure

```
air-quality-monitoring/
├── air-quality-device/         # Arduino-based monitoring device (ESP32 + sensors)
├── air-quality-crawler/        # Air quality data collector (AirKorea API)
├── air-quality-serial/         # Serial communication module (4-channel)
├── air-quality-api/            # REST API server (Google App Engine)
├── air-quality-client/         # API test client
└── air-quality-calibration/    # Data calibration system (multi-sensor)
```

## 🛠 Technology Stack

| Category | Technologies |
|----------|--------------|
| **Language** | Java 1.8, C++ (Arduino) |
| **Build Tool** | Maven, Arduino IDE |
| **Hardware** | ESP32, SPS30, SGP30, SHT30, TCA9548A |
| **Server** | Google App Engine, Servlet API |
| **Communication** | Jersey REST Client, jSerialComm, I2C |
| **Data** | CSV, JSON (Gson) |
| **Logging** | Logback, SLF4J |
| **Filtering** | Median-Kalman Filter, Moving Average |

## 📦 Quick Start

### 1. Environment Setup

#### Install Java 8
```bash
# Install SDKMAN
curl -s "https://get.sdkman.io" | bash
source "$HOME/.sdkman/bin/sdkman-init.sh"

# Install Java 8
sdk install java 8.0.432-zulu
sdk use java 8.0.432-zulu

# Verify installation
java -version
```

#### Configure Environment Variables
```bash
# Create .env file
cp .env.example .env

# Set required environment variables
nano .env
```

### 2. Build Projects

```bash
# Build all projects
./build-all.sh

# Or build individually
cd air-quality-crawler && mvn clean install
cd ../air-quality-serial/ArimAirSerial && mvn clean install
cd ../../air-quality-calibration && mvn clean install
cd ../air-quality-api && mvn clean package
```

### 3. Run Applications

```bash
# Start data collector
cd air-quality-crawler
mvn exec:java

# Start sensor data collection
cd ../air-quality-serial/ArimAirSerial
mvn exec:java

# Start API server
cd ../../air-quality-api
mvn appengine:run
```

## 🔧 Key Features

### 1. IoT Device (air-quality-device)
- ✅ ESP32-based multi-sensor integration (SPS30×3, SGP30, SHT30)
- ✅ Advanced filtering algorithms (Median-Kalman Filter)
- ✅ Real-time data processing (1Hz sampling)
- ✅ 3D printable case design (STL files included)
- ✅ Visual air quality indicator (WS2812 RGB LED)

### 2. Data Collection (air-quality-crawler)
- ✅ AirKorea Open API integration
- ✅ Timer-based periodic collection
- ✅ Daejeon region monitoring station data

### 3. Sensor Communication (air-quality-serial)
- ✅ Multi-port concurrent processing (4 channels)
- ✅ Real-time sensor data reading
- ✅ Automatic CSV logging

### 4. Data Calibration (air-quality-calibration)
- ✅ Multi-sensor cross-validation
- ✅ Automatic outlier correction (3-sensor average)
- ✅ 1-hour/24-hour rolling average calculation
- ✅ Data compression (99.4% reduction)

### 5. API Server (air-quality-api)
- ✅ RESTful API endpoints
- ✅ Device management
- ✅ Air quality data storage/retrieval
- ✅ User authentication

## 📊 System Architecture

```
┌──────────────────────────────────────────────────────────────────┐
│                      IoT Device Layer                            │
│  ┌────────────────┐  ┌────────────────┐  ┌────────────────┐    │
│  │  ESP32 Device  │  │  ESP32 Device  │  │  ESP32 Device  │    │
│  │  (RA200)       │  │  (RA200)       │  │  (RA200)       │    │
│  │  • SPS30×3     │  │  • SPS30×3     │  │  • SPS30×3     │    │
│  │  • SGP30       │  │  • SGP30       │  │  • SGP30       │    │
│  │  • SHT30       │  │  • SHT30       │  │  • SHT30       │    │
│  │  • RS9A        │  │  • RS9A        │  │  • RS9A        │    │
│  └───────┬────────┘  └───────┬────────┘  └───────┬────────┘    │
│          │ Serial            │ Serial            │ Serial       │
└──────────┼───────────────────┼───────────────────┼──────────────┘
           ↓                   ↓                   ↓
┌──────────────────────────────────────────────────────────────────┐
│                   Data Collection Layer                          │
│  ┌────────────────────────────────────────────────────────┐     │
│  │  air-quality-serial (4-channel concurrent processing)  │     │
│  │  • COM port multiplexing                               │     │
│  │  • Real-time data streaming                            │     │
│  │  • CSV logging                                         │     │
│  └───────────────────────┬────────────────────────────────┘     │
│                          │                                       │
│  ┌───────────────────────┴────────────────────────────────┐     │
│  │  air-quality-crawler (AirKorea API)                    │     │
│  │  • Public API integration                              │     │
│  │  • Periodic data fetching                              │     │
│  └───────────────────────┬────────────────────────────────┘     │
└────────────────────────┼─────────────────────────────────────────┘
                         ↓
┌──────────────────────────────────────────────────────────────────┐
│                   Processing Layer                               │
│  ┌────────────────────────────────────────────────────────┐     │
│  │  air-quality-calibration                               │     │
│  │  • Multi-sensor cross-validation                       │     │
│  │  • Outlier detection & correction                      │     │
│  │  • Rolling averages (1h/24h)                           │     │
│  │  • Data compression (99.4%)                            │     │
│  └───────────────────────┬────────────────────────────────┘     │
└────────────────────────┼─────────────────────────────────────────┘
                         ↓
┌──────────────────────────────────────────────────────────────────┐
│                     Storage & API Layer                          │
│  ┌────────────────────────────────────────────────────────┐     │
│  │  air-quality-api (Google App Engine)                   │     │
│  │  • RESTful API endpoints                               │     │
│  │  • Device management                                   │     │
│  │  • Data storage & retrieval                            │     │
│  │  • User authentication                                 │     │
│  └───────────────────────┬────────────────────────────────┘     │
└────────────────────────┼─────────────────────────────────────────┘
                         ↓
┌──────────────────────────────────────────────────────────────────┐
│                    Client Applications                           │
│  ┌────────────────┐  ┌────────────────┐  ┌────────────────┐    │
│  │  Web Dashboard │  │  Mobile App    │  │  API Client    │    │
│  │                │  │                │  │  (Testing)     │    │
│  └────────────────┘  └────────────────┘  └────────────────┘    │
└──────────────────────────────────────────────────────────────────┘
```

## 📖 Documentation

Detailed documentation for each project:

- [air-quality-device README](./air-quality-device/README.md) - ESP32 IoT device
- [air-quality-crawler README](./air-quality-crawler/README.md) - AirKorea API collector
- [air-quality-serial README](./air-quality-serial/README.md) - Serial communication
- [air-quality-calibration README](./air-quality-calibration/README.md) - Data calibration
- [air-quality-api README](./air-quality-api/README.md) - REST API server

## 🔐 Security

### Environment Variables

**Never commit these files to Git:**
- `application.properties`
- `config.properties`
- `AirKoreaAPI.txt`
- `.env`

Usage example:
```java
String apiKey = System.getenv("AIRKOREA_API_KEY");
```

### API Key Registration

1. Visit [Korea Environment Corporation Open API Portal](https://www.data.go.kr)
2. Search for "한국환경공단_에어코리아_대기오염정보" (Korea Environment Corporation AirKorea Air Pollution Information)
3. Apply for API key
4. Add to `.env` file

## 🧪 Testing

```bash
# Run unit tests
mvn test

# Run integration tests
mvn verify

# Test specific project
cd air-quality-calibration
mvn test
```

## 📈 Performance Metrics

| Metric | Value |
|--------|-------|
| **IoT Device Sampling Rate** | 1 Hz (1 sample/second) |
| **Sensor Data Processing** | 125K+ records |
| **Data Compression Ratio** | 99.4% |
| **Concurrent Sensor Processing** | 4 channels |
| **API Response Time** | < 200ms |
| **Filtering Latency** | < 2.5s |
| **Multi-sensor Accuracy** | ±10% @ 100 μg/m³ |

## 🐛 Troubleshooting

### Java Version Error
```bash
# Check Java version
java -version

# Switch to Java 8
sdk use java 8.0.432-zulu
```

### Maven Build Failure
```bash
# Clean Maven cache
mvn clean

# Re-download dependencies
mvn dependency:purge-local-repository
```

### Arduino Upload Error
```bash
# Check ESP32 board installation
# Verify USB driver installation
# Select correct COM port
# Try lower upload speed (115200)
```

### Sensor Not Detected
```bash
# Run I2C scanner
# Check wiring (SDA/SCL)
# Verify power supply (3.3V/5V)
# Check I2C pull-up resistors (4.7kΩ)
```

### API Connection Error
- Verify API key validity
- Check network connectivity
- Confirm rate limits not exceeded
- Review firewall settings

## 📅 Roadmap

### Phase 1: Infrastructure Setup ✅
- [x] Java 8 installation (SDKMAN)
- [x] .gitignore configuration
- [x] Environment variables setup
- [x] Documentation (English)
- [x] Project rebranding (Arim → air-quality-*)
- [x] ESP32 device firmware (RA200)
- [x] 3D printable case design

### Phase 2: Technical Debt Resolution ✅
- [x] Dependency updates (Jersey, OpenCSV, Logback, Gson)
- [x] OpenCSV 5.9 API migration
- [x] air-quality-api compilation fixes
- [x] air-quality-calibration configuration externalization
- [x] Build automation script (build-all.sh)
- [x] Full project build verification
- [ ] Code refactoring
- [ ] Unit test coverage

### Phase 3: Architecture Improvements (Planned)
- [ ] Database integration (InfluxDB/TimescaleDB)
- [ ] Microservices architecture
- [ ] Docker containerization
- [ ] CI/CD pipeline (GitHub Actions)
- [ ] WiFi connectivity for ESP32 devices
- [ ] MQTT protocol integration

### Phase 4: Advanced Features (Planned)
- [ ] Machine learning-based anomaly detection
- [ ] Real-time dashboard (Grafana)
- [ ] Mobile application (React Native)
- [ ] AI-powered air quality prediction
- [ ] Multi-device management system
- [ ] Cloud data synchronization



## 📝 License

MIT License - See [LICENSE](LICENSE) file for details.


---

**⭐ 이 프로젝트가 도움이 되었다면 Star를 눌러주세요!**
