SHELL = /bin/bash
build:
	python3 scripts/build.py

clean:
	python3 scripts/clean.py

monitor:
	tail -F monitor.txt

run: build
	./bin/mc

.PHONY: build clean run monitor
