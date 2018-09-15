# Questions

## What's `stdint.h`?

The <stdint.h> header shall declare sets of integer types having specified widths, and shall define corresponding sets of macros. It shall also define macros that specify limits of integer types corresponding to types defined in other standard headers.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Preserve the correct numerical values of various properties according and to the protocol.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE is 1byte, DWORD is 4bytes, LONG is 4bytes, WORD is 2bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM (in ASCII)

## What's the difference between `bfSize` and `biSize`?

bfSize is the file size and biSize is the BITMAPINFOHEADER.

## What does it mean if `biHeight` is negative?

It would means the bitmap is top-down.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Because the file or path you try to open might not exist.

## Why is the third argument to `fread` always `1` in our code?

Because we only need to return sizeof() once for file header and info header.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

A fuction to move the file position indicator

## What is `SEEK_CUR`?

The current position in file

## Whodunit?

It was Professor Plum with the candlestick in the library.
