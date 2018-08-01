

-- ʵ�� pairs ipairs for ��������
local function ipairs_next_func(tab, key)
	key = key + 1
	value = tab[key]
	if value then
		return key, value
	end
end
local function ipairs_func(tab)
	return ipairs_next_func, tab, 0
end

local function pairs_next_func(tab, key)
	key = next(tab, key)
	value = tab[key]
	if value then
		return key, value
	end
end
local function pairs_func(tab, key)
	return pairs_next_func, tab, nil
end
local function for_func(iter_func, test_table, user_func)
	local next, var, state = iter_func(test_table)
	while true do
		local k, v = next(var, state)
		if not k then break end	
		state = k
		user_func(k, v)
	end
end

-- ����һ��
local test_table = 
{
	a = 1,
	2,
	x = 'x',
	3,
}

print('ipairs:')
for k, v in ipairs(test_table) do
	print(k,v)
end

print("ipairs_func:")
for_func(ipairs_func, test_table, print)

print('pairs:')
for k, v in pairs(test_table) do
	print(k,v)
end

print("pairs_func:")
for_func(pairs_func, test_table, print)	

--[[
test next function
--]]

print("------------null table----------");
local ta = {

}

print(#ta)
print(next(ta))

print("------------no explit key----------");
local ta = {
--'}' expected (to close '{' at line 71) near '='
--1 = "ma"
       "ma"
}

print(#ta)
print(next(ta))
print(next(ta,nil))
--lua: invalid key to 'next'
--print(next(ta,0))
print(next(ta,1))

print("------------[numb] as key----------");
local ta = {
[1] = "ma"
}

print(#ta)
print(next(ta))
print(next(ta,nil))
--lua: invalid key to 'next'
--print(next(ta,0))
print(next(ta,1))

print("------------rr as key----------");
local ta = {
rr = "ma"
}

print(#ta)
print(ta[rr])
print(ta["rr"])
print(next(ta))
print(next(ta,nil))
print(next(ta,rr))
-- invalid key to 'next'
--print(next(ta,1))

print("------------[rr] as key----------");
local ta = {
-- table index is nil
--[rr] = "ma"
--'}' expected (to close '{' at line 106) near '='
--"rr" = "ma"
}
ta["rr"] = "ma";
print(next(ta,rr))
print(ta[rr])
print(ta["rr"])
print(next(ta,"rr"))
--table index is nil
--ta[rr]="ma";

--[[next (table [, index])
���ܣ��������������е�ÿһ���ֶΣ�������һ�����͸�������ֵ��
������table��Ҫ�����ı�
������index��Ҫ���ص�������ǰһ���еĺţ���indexΪnil[]ʱ�������ص�һ��������ֵ����������Ϊ���һ���������Ϊ��ʱ������nil
ע��������next(t)�������Ƿ�Ϊ��(�˺���ֻ�����������������ı���ipairs������)--]]

 --[[����lua table�Ƿ�Ϊ�յ��ж�
����Ŀ�Ľű�lua�о���������������

1��local a = {}

2����a���д���

3����a�Ƿ�Ϊ�ձ�����ж�

���ڶ�a�Ƿ�Ϊ�ձ���жϣ��ҷ�����Щ�����������

if a == {} then

�����Ľ������a == {}��Զ����false����һ���߼�������Ϊ����Ƚϵ���table a��һ������table���ڴ��ַ��

Ҳ��Щ�����������

if table.maxn(a) == 0 then

������Ҳ�����գ�����table��key�������֣���û��hash���֡�

�ѵ����Ҫ����table�����ж�����return false�������ܶ϶����Ƿ�Ϊ��������д���ٴ���̫�ѿ�. 

����С����һ�£�����ԭ���ٷ��ֲ������Ѿ����˴𰸣��Ǿ��ǿ�lua���õ�next����

������ã�if next(a) == nil then

next��ʵ����pairs����tableʱ����ȡ��һ�����ݵĺ���.

����Ŀ��module����÷�װһ�£����module����Ҳ��next����

���Ƿ�װ���жϵ�lua table�Ƿ�Ϊ�յĺ������£�

function table_is_empty(t)

        return _G.next( t ) == nil

end
--]]


--[[
pairs �� ipairs ����
--]]

--[[��׼���ṩ�˼��е����������������ļ�ÿ�е�(io.lines)��
����tableԪ�ص�(pairs)����������Ԫ�ص�(ipairs)�������ַ����е��ʵ� 
(string.gmatch)
LUA�ֲ��ж���pairs,ipairs�������£�

ipairs (t)
Returns three values: an iterator function, the table t, and 0, so that the construction
for i,v in ipairs(t) do body end
will iterate over the pairs (1,t[1]), (2,t[2]), ������, up to the first integer key absent from the table.

pairs (t)
Returns three values: the next function, the table t, and nil, so that the construction
for k,v in pairs(t) do body end
will iterate over all key�Cvalue pairs of table t.
See function next for the caveats of modifying the table during its traversal.

�����Ϳ��Կ���  ipairs�Լ�pairs �Ĳ�ͬ��
pairs���Ա����������е�key�����ҳ��˵����������Լ������������Է���nil;
����ipairs���ܷ���nil,ֻ�ܷ�������0���������nil���˳�����ֻ�ܱ��������г��ֵĵ�һ������������key
--]]

--����ٸ����Ӱɣ�

local tabFiles = {
[3] = "test2",
[6] = "test3",
[4] = "test1"
}
 
for k, v in ipairs(tabFiles) do
print(k, v)
end
 
 --[[
�²�������������ʲô�أ�
 
���ݸղŵķ��������� ipairs(tabFiles) �����У���key=1ʱ��value����nil������ֱ������ѭ��������κ�ֵ��
 
>lua -e "io.stdout:setvbuf 'no'" "Test.lua"
>Exit code: 0
 
��ô�������
for k, v in pairs(tabFiles) do
print(k, v)
end
���������� ��
>lua -e "io.stdout:setvbuf 'no'" "Test.lua" 
3 test2
6 test3
4 test1
>Exit code: 0
���ڸı�һ�±����ݣ�
local tabFiles = {
[1] = "test1",
[6] = "test2",
[4] = "test3"
}
for k, v in ipairs(tabFiles) do
print(k, v)
end
���ڵ��������Զ��׼�����key=1ʱ��valueֵtest1
 >lua -e "io.stdout:setvbuf 'no'" "Test.lua" 
1 test1
>Exit code: 0 
--[ʾ��1.]--
local tt =
{
    [1] = "test3",
    [4] = "test4",
    [5] = "test5"
}

for i,v in pairs(tt) do        -- ��� "test4" "test3" "test5"
    print( tt[i] )
end

for i,v in ipairs(tt) do    -- ��� "test3" k=2ʱ�Ͽ�
    print( tt[i] )
end





-- [ʾ��2.] --
tbl = {"alpha", "beta", [3] = "uno", ["two"] = "dos"}

for i,v in ipairs(tbl) do    --���ǰ����
    print( tbl[i] )
end

for i,v in pairs(tbl) do    --ȫ�����
    print( tbl[i] )
end
--]]
