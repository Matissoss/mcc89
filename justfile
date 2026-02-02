default:
        @just -l
clean:
        @rm -rf target

build: clean
        @mkdir target
        @cc -std=c89 -pedantic src/*.c -o target/mcc89
