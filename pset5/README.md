dictionary.c
by Billy.Ljm

---

These are the run times of my `dictionary.c` on all the texts provided in `~/cs50/pset5/texts/` with the dictionary provided in `~/cs50/pset5/dictionaries/large` and in the default CS50 VM.  

The name of the texts are in the first line of each code block and the timing outputs of `speller.c` are below them.  

Note that theses are single run run times and thus are not accurate and will only give ballpark estimates. Also, the hash table size was only very roughly optimised solely for `austinpowers.txt` and thus, additional performance can be squeezed out by adjusting the hash table size.  

```
>> alice.txt

WORDS MISSPELLED:     295
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        29758
TIME IN load:         0.04
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.07
```

```
>> constitution.txt

WORDS MISSPELLED:     30
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        7573
TIME IN load:         0.03
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04
```

```
>> frankenstein.txt

WORDS MISSPELLED:     2451
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        80527
TIME IN load:         0.03
TIME IN check:        0.05
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.09
```

```
>> hugo.txt

WORDS MISSPELLED:     16934
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        573396
TIME IN load:         0.03
TIME IN check:        0.24
TIME IN size:         0.00
TIME IN unload:       0.02
TIME IN TOTAL:        0.28
```

```
>> package.txt

WORDS MISSPELLED:     62
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        3161
TIME IN load:         0.03
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.05
```

```
>> ralph.txt

WORDS MISSPELLED:     1
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        20
TIME IN load:         0.03
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.02
TIME IN TOTAL:        0.04
```

```
>> tolstoy.txt

WORDS MISSPELLED:     13008
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        567967
TIME IN load:         0.03
TIME IN check:        0.21
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.25
```

```
>> whittier.txt

WORDS MISSPELLED:     10111
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        585394
TIME IN load:         0.03
TIME IN check:        0.22
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.26
```

```
>> xueqin2.txt

WORDS MISSPELLED:     12544
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        265867
TIME IN load:         0.02
TIME IN check:        0.12
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.16
```

```
>> austen.txt

WORDS MISSPELLED:     1614
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        125203
TIME IN load:         0.03
TIME IN check:        0.03
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.07
```

```
>> daffodils.txt

WORDS MISSPELLED:     0
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        158
TIME IN load:         0.02
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04
```

```
>> grimm.txt

WORDS MISSPELLED:     718
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        103614
TIME IN load:         0.02
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.06
```

```
>> iliad.txt

WORDS MISSPELLED:     9339
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        192975
TIME IN load:         0.03
TIME IN check:        0.10
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.14
```

```
>> pneumonoultramicroscopicsilicovolcanoconiosis.txt

WORDS MISSPELLED:     0
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        20
TIME IN load:         0.03
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04
```

```
>> shakespeare.txt

WORDS MISSPELLED:     45691
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        904612
TIME IN load:         0.03
TIME IN check:        0.37
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.41
```

```
>> tom.txt

WORDS MISSPELLED:     1134
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        74451
TIME IN load:         0.03
TIME IN check:        0.04
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.08
```

```
>> witch.txt

WORDS MISSPELLED:     23
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        372
TIME IN load:         0.02
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04
```

```
>> austinpowers.txt

WORDS MISSPELLED:     644
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        19190
TIME IN load:         0.03
TIME IN check:        0.01
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04
```

```
>> dracula.txt

WORDS MISSPELLED:     2415
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        163834
TIME IN load:         0.02
TIME IN check:        0.09
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.12
```

```
>> holmes.txt

WORDS MISSPELLED:     17845
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        1150970
TIME IN load:         0.02
TIME IN check:        0.51
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.55
```

```
>> kjv.txt

WORDS MISSPELLED:     33441
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        799460
TIME IN load:         0.03
TIME IN check:        0.30
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.34
```

```
>> prince.txt

WORDS MISSPELLED:     1422
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        52538
TIME IN load:         0.03
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.06
```

```
>> sherlock.txt

WORDS MISSPELLED:     924
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        107602
TIME IN load:         0.02
TIME IN check:        0.05
TIME IN size:         0.00
TIME IN unload:       0.02
TIME IN TOTAL:        0.09
```

```
>> ulysses.txt

WORDS MISSPELLED:     14848
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        266235
TIME IN load:         0.02
TIME IN check:        0.11
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.14
```

```
>> wonderland.txt

WORDS MISSPELLED:     295
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        29758
TIME IN load:         0.03
TIME IN check:        0.02
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.06
```

```
>> christmas.txt

WORDS MISSPELLED:     383
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        31927
TIME IN load:         0.03
TIME IN check:        0.01
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.05
```

```
>> federalist.txt

WORDS MISSPELLED:     935
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        196784
TIME IN load:         0.03
TIME IN check:        0.07
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.11
```

```
>> huck.txt

WORDS MISSPELLED:     3644
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        115244
TIME IN load:         0.02
TIME IN check:        0.04
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.08
```

```
>> men.txt

WORDS MISSPELLED:     3
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        298
TIME IN load:         0.02
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04
```

```
>> quote.txt

WORDS MISSPELLED:     0
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        117
TIME IN load:         0.02
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04
```

```
>> surgery.txt

WORDS MISSPELLED:     3681
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        198251
TIME IN load:         0.03
TIME IN check:        0.08
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.12
```

```
>> usa.txt

WORDS MISSPELLED:     2434
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        206799
TIME IN load:         0.03
TIME IN check:        0.08
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.12
```

```
>> xueqin1.txt

WORDS MISSPELLED:     7934
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        189138
TIME IN load:         0.02
TIME IN check:        0.05
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.08
```

