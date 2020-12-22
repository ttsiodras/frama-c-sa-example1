all:	| dockerImage
	@echo "[-] Analysing 'why.c' with Frama-C v22 EVA plugin..."
	@docker run --rm -v $$(pwd):/work framac/frama-c:22.0 \
		/bin/bash -c 'cd /work ; \
			frama-c -eva -eva-precision 1 -main someFunc why.c'

dockerImage:
	@echo "[-] Verifying dependencies..."
	@docker images --format='{{.Repository}}:{{.Tag}}' | \
		grep framac/frama-c:22.0 >/dev/null || \
		docker pull  framac/frama-c:22.0
