# What

(2024-05/2024-10)

Arduino library to parse ASCII to integer.

## Reference output

```
[me_ParseInteger] Okay, we are here.

We will parse integers fro[me_ParseInteger] Okay, we are here.

We will parse integers from -32768 to 32767.
Enter something...
fk
'fk'?
3
Value ( +00003 )
345435
'345435'?
324
Value ( +00324 )
-34
Value ( -00034 )
-0
Value ( +00000 )
+0
'+0'?
```

## Code

* [Interface][Interface]
* Implementation
  * [Exported functions][me_ParseInteger]
  * [Freetown][Freetown]
* [Example][Example]


## Requirements

  * arduino-cli
  * bash


## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.


## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]


[Interface]: src/me_ParseInteger.h
[me_ParseInteger]: src/me_ParseInteger.cpp
[Freetown]: src/me_ParseInteger_Freetown.cpp
[Example]: examples/me_ParseInteger/me_ParseInteger.ino

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
