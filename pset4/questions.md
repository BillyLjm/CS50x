0.  `GIF` only support 256 colours. Conversely, Typical `BMP`, `JPEG` & `PNG` support 2^24 colours although higher bit depth versions of the 3 formats are also available.  
1.  Only `GIF` have inherent animation support. There is a  `PNG` extension called `APNG` which also supports animation, but it is not popular.  
2.  Lossless compression allows the original data to be fully reconstructed from the compressed data. Lossy compression does not allow this.  
3.  Only `JPEG` is lossy. `BMP`, `GIF` & `PNG` are all lossless.  
4.  The data clusters are removed from the File Allocation Table (`FAT`), allowing them to be overwritten in the future. However, the actual bits remain in those clusters until they are overwritten.  
5.  The data clusters can be overwritten with zeroes or garbage values. There are several data erasure software to choose from.  
6.  `stdint.h` is a library which defines several integer structs and related macros.  
7.  It is to specify the specific integer structure used and thus its range.  
8.  A `BYTE` is 1 byte, a `WORD` is 2 bytes and both `LONG` and `DWORD` are 4 bytes.  
9.  The first 2 bytes of a `BMP` is `BM` in `ASCII`  
10. `bfSize` is the size of the entire BMP file. `biSize` is the size of a specific part of the BMP file, called the `BITMAPINFOHEADER`.  
11. A negative `biHeight` means the pixels are listed top-down with the first pixel listed corresponding to the upper-left corner.  
12. `biBitCount` sepcifies the colour depth of a `BMP`  
13. `fopen` in `copy.c` returns `NULL` if the output file couldn't be created due to write permissions or lack of space among other things.  
14. The 3rd argument of `fread` is always 1 as we only want to read 1 element at a time.  
15. The `padding` will be 3 if `bi.biWidth` is 3.  
16. `fseek` moves the current position in a file stream by a specified number of bytes from a specified point.  
17. `SEEK_CUR` is the current poision in a file stream  
18. Rob Bowden, from CS50!  
