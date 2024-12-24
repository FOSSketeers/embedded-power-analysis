# Directory containing CSV files
DIST_DIR = dist

# Directory to store compressed files
MEASUREMENTS_DIR = measurements

# Find all CSV files in the dist directory
CSV_FILES = $(wildcard $(DIST_DIR)/*.csv)

# Convert CSV files to .xz files
XZ_FILES = $(CSV_FILES:$(DIST_DIR)/%.csv=$(MEASUREMENTS_DIR)/%.csv.xz)

# Default target
.PHONY: all compress decompress clean

# Compress the CSV files into .xz format (only if not already compressed or outdated)
compress: $(XZ_FILES)

# Rule for creating .xz files from .csv files
$(MEASUREMENTS_DIR)/%.csv.xz: $(DIST_DIR)/%.csv
	@mkdir -p $(MEASUREMENTS_DIR)
	xz -z -k -T0 $< -c > $@

# Decompress the .xz files back to CSV format (only if not already decompressed or outdated)
decompress: $(CSV_FILES)

# Rule for decompressing .xz files back to .csv
$(DIST_DIR)/%.csv: $(MEASUREMENTS_DIR)/%.csv.xz
	@mkdir -p $(DIST_DIR)
	xz -d -k $< -c > $@

# Clean target to remove the compressed files
clean:
	rm -f $(XZ_FILES)
