local str = "12ab34,eed,56"
local func_itor = string.gmatch(str, "%d+")

-- �鿴func_itor����
print("func_itor is", func_itor)

-- ��һ�ε��ú���func_itor
print("func_itor ret is ", func_itor())

-- �ٴε��ú���func_itor
print("func_itor ret is ", func_itor())

-- ʹ��ѭ������ӡ
local sourcestr = "hello world from Lua"
local index = 1
print("\noutput capture using loop:")
--%a+��ʾ����������1�������ϵ���ĸ�ַ���
for word in string.gmatch(sourcestr, "%a+") do
    print(index, word)
    index = index + 1
end

-- �������Զ�
local attrstr = "from=world, to=Lua, name=AlbertS"
print("\noutput attr pair capture using loop:")
for k,v in string.gmatch(attrstr, "(%w+)=(%w+)") do
    print(k, v)
end

local nonumstr = "fadfasd,.;p[];'asd"
local func_numitor = string.gmatch(nonumstr, "%d+")
local numret = func_numitor()
print("\nnumret ret is", numret)

--[[
string.gmatch()##
ԭ�ͣ�string.gmatch (s, pattern)
���ͣ�����һ��������������ÿһ�ε����������������һ�����ַ���s�ҵ�����һ������pattern�������Ӵ����������pattern�������ַ���û���ҵ���������������nil��
�ɵ�һ�еĴ�ӡ������Կ�������string.gmatch()���ص�������һ����������һ��Ƚ���������ǰ������һ������io.lines()������Ȥ�����ѿ��Կ�һ�¡�
�ɺ���string.gmatch()���صĵ�������ÿһ�ε��ö���õ��µ�ƥ������
����ƥ����ĺ���%a��ʾ����һ����ĸ��%w��ʾ����һ�����ֻ�����ĸ��%d��ʾ����һ�����֣��������+��ʾ1�����߶������%a+��ʾ����������1�������ϵ���ĸ�ַ����������⼸���⻹�кܶ����͵�ƥ������Ժ�Ҫ��ϸȥ˵�������ﲻ���ù����ƪ����
֪����ƥ����ĺ�����Ȼ�����˽�(%w+)=(%w+)�������ˣ�����������Ѱ������key=value���ַ����ġ�
�����һ�����������Կ����������ҵ��ַ�����������Ҫƥ����ַ�ʱ�����صĵ�����������ʱ�᷵��nil
 --]]