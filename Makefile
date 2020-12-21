all:
	docker run --rm -v $$(pwd):/work framac/frama-c:22.0 \
		/bin/bash -c 'cd /work ; \
			frama-c -eva -eva-precision 1 -main someFunc why.c'
