request:

host(a byte) + function type(a byte) + starting register address (two bytes) + number of registers(two bytes) + crc (two bytes)

> 01 
>
> 03
>
> 9c46
> 
> 001c
> 
> 8b86

response:

host(a byte) + function type(a byte) + bytes size(2*number of registers) + data + crc (two bytes)

>01
>
>03
>
>38(56 in hex, which is 2*28 where 001c==28)
>
>000a0a0a00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
>
>168f
