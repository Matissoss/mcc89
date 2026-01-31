default:
        @just -l
clean:
        @rm -rf target

build: clean
        @mkdir target
        @cc src/*.c -o target/mcc89 --std=c89
