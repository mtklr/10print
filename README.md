# 10print

[10 PRINT...](https://10print.org) for wallpaper, backgrounds, etc.

One-liner:

``` console
while :; do printf '\e#6%b' "\0342\0225\026$((RANDOM % 2 + 1))"; done
```

![10print background](images/10print.png)

`10print` script:

``` console
usage: 10print [option ...]
10 PRINT CHR$(205.5+RND(1)); : GOTO 10

options:
  -a  alternate character set
  -c  color (256 color terminal)
  -g  grayscale (256 color terminal)
  -h  display this help and exit
  -l  large output
  -m  medium output
  -p  pause after each screenful of output, `q' quits
  -u  unicode
```

## Hmm...

Is the banding pattern seen in zoomed-out views of these images the result of bash's pseudo-random number generator?

(No, it's how the Finder column view preview shows the images initially, or when resizing the window).
