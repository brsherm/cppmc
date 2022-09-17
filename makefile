SHELL = /bin/bash
build:
	python3 scripts/build.py

clean:
	python3 scripts/clean.py

monitor:
	tail -F monitor.txt

run:
	python3 scripts/build.py && ./bin/mc

.PHONY: build clean run monitor
