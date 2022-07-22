function hex2bin(x)
	ret=""
	while x~=1 and x~=0 do
		ret=tostring(x%2)..ret
		x=math.modf(x/2)
	end
	ret=tostring(x)..ret
    while(#ret<16)do
        ret='0'..ret
    end
	return ret
end
