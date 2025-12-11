#!/bin/bash

# Air Quality Monitoring - Build All Projects
# This script builds all Java projects in the workspace

set -e  # Exit on error

echo "=========================================="
echo "Air Quality Monitoring - Build All"
echo "=========================================="
echo ""

# Color codes for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if Java 8 is available
JAVA_VERSION=$(java -version 2>&1 | head -1 | cut -d'"' -f2 | sed 's/^1\.//' | cut -d'.' -f1)
if [ "$JAVA_VERSION" != "8" ]; then
    echo -e "${RED}Error: Java 8 is required but not found.${NC}"
    echo "Current Java version: $(java -version 2>&1 | head -1)"
    echo ""
    echo "Please install Java 8 using SDKMAN:"
    echo "  sdk install java 8.0.432-zulu"
    echo "  sdk use java 8.0.432-zulu"
    exit 1
fi

echo -e "${GREEN}✓ Java 8 detected${NC}"
echo ""

# Get the workspace root directory
WORKSPACE_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$WORKSPACE_ROOT"

# Array of projects to build
PROJECTS=(
    "air-quality-crawler"
    "air-quality-serial/ArimAirSerial"
    "air-quality-api"
    "air-quality-client"
    "air-quality-calibration"
)

# Build counter
SUCCESS_COUNT=0
FAILURE_COUNT=0
FAILED_PROJECTS=()

# Build each project
for PROJECT in "${PROJECTS[@]}"; do
    PROJECT_PATH="$WORKSPACE_ROOT/$PROJECT"
    
    if [ ! -d "$PROJECT_PATH" ]; then
        echo -e "${YELLOW}⚠ Skipping $PROJECT (directory not found)${NC}"
        continue
    fi
    
    if [ ! -f "$PROJECT_PATH/pom.xml" ]; then
        echo -e "${YELLOW}⚠ Skipping $PROJECT (no pom.xml found)${NC}"
        continue
    fi
    
    echo "=========================================="
    echo "Building: $PROJECT"
    echo "=========================================="
    
    cd "$PROJECT_PATH"
    
    if mvn clean compile; then
        echo -e "${GREEN}✓ $PROJECT built successfully${NC}"
        ((SUCCESS_COUNT++))
    else
        echo -e "${RED}✗ $PROJECT build failed${NC}"
        ((FAILURE_COUNT++))
        FAILED_PROJECTS+=("$PROJECT")
    fi
    
    echo ""
done

# Summary
echo "=========================================="
echo "Build Summary"
echo "=========================================="
echo -e "Successful builds: ${GREEN}$SUCCESS_COUNT${NC}"
echo -e "Failed builds: ${RED}$FAILURE_COUNT${NC}"

if [ $FAILURE_COUNT -gt 0 ]; then
    echo ""
    echo "Failed projects:"
    for PROJECT in "${FAILED_PROJECTS[@]}"; do
        echo -e "  ${RED}✗${NC} $PROJECT"
    done
    exit 1
else
    echo ""
    echo -e "${GREEN}All projects built successfully!${NC}"
    exit 0
fi
