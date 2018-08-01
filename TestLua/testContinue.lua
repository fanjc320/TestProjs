kv = {1,2,3,4,5,6,7,8,9}

for k,v in ipairs(kv) do
    repeat
        if k == 5 then
            break
        end
        print(k)
    until true

	print("k:"..k.." v:"..v);
end