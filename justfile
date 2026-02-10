default:
        @just -l
clean:
        @rm -rf target

build: clean
        @mkdir target
        @cc -std=c89 -pedantic -Wall -Werror src/*.c -o target/mcc89
