.PHONY: all build clean

all: build

build:
	@if command -v opp_makemake >/dev/null 2>&1; then \
		echo "Generating makefiles with opp_makemake..."; \
		opp_makemake -f --deep -O out -o roteadormg; \
		$(MAKE) -C out; \
	else \
		echo "OMNeT++ not found (opp_makemake missing). Please install OMNeT++ 6.x and run: opp_makemake -f --deep -O out -o roteadormg && make -C out"; \
		exit 1; \
	fi

clean:
	@if [ -d out ]; then $(MAKE) -C out clean; fi