build:
	python3 scripts/build.py

clean:
	python3 scripts/clean.py

run: build
	./bin/mc

.PHONY: build clean run