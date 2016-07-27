.PHONY: clean All

All:
	@echo "----------Building project:[ Hamming_7_4 - Debug ]----------"
	@"$(MAKE)" -f  "Hamming_7_4.mk"
clean:
	@echo "----------Cleaning project:[ Hamming_7_4 - Debug ]----------"
	@"$(MAKE)" -f  "Hamming_7_4.mk" clean
