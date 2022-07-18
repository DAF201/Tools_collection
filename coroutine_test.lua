coutner = 0
function a()
	while 1 do
		if coutner % 2 == 0 then 
			coroutine.yield(c1)
		end
		print("function 1")
		coutner = coutner + 1
		coroutine.resume(c2)
	end
end

function b()
	while 1 do
		if coutner % 2 == 1 then 
			coroutine.yield(c2)
		end
		print("function 2")
		coutner = coutner + 1
		coroutine.resume(c1)
	end
end
c1=coroutine.create(a)
c2=coroutine.create(b)
coroutine.resume(c1)
coroutine.resume(c2)
