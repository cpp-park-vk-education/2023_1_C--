make:
	docker build -f ./Dockerfile.builder -t builderimage .

client:
	cmake -B ./build -S . && cd ./build/client && make && cd ../../

build:
	docker compose build

run:
	docker compose up

down:
	docker compose down