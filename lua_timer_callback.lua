start_time = os.date('%S')
while 1 do
	now = os.date('%S')
	if now - start_time > 1 or start_time>now then
		start_time = now
		--code here
	end
end
