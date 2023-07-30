 ## Malloc from Scratch

 Good course, everything just worked out of the box.

 Gary used shell, I used makefile as easy integration with Vim, so just
 save and running `:make` was all it took.


 ```makefile

all:
	gcc malloc.c -o malloc && ./malloc
```

The code is formatted using clang-format for standard style.

Install `clang-format` like this: `brew install clang-format` on macos.

And then `clang-format malloc.c`

