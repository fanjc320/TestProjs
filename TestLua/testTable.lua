tb = {};
tb[5] = 3;
tb[6]=2;


print(""..tb[5]);

print(""..tb[6]);

local a = tb[7];
local b = tb[1];

if a == nil then
print("a==nil");
end

if not b then
print("b==nil");
end;
--------------------------------------------------------
print("-----------------------------------------");
tbtest = {  
    [1] = 1,  
    [2] = 2,  
    [3] = 3,  
    [4] = 4,  
	["a"] = 6,  
	["b"] = 7, 
} 
 
for key, value in pairs(tbtest) do  
    print("key:",key,"value:",value)
end 
print("-----------------------------------------");
--����Ϊ���Ӧ����1��2��3��4��ʵ���ϵ������1��2��4��3������Ϊ��������һ��bug�����Ǻ󻰡�
--Ҳ����˵for k,v in pairs(tbtest) do �����ı���˳�򲢷���tbtest��table������˳�򣬶��Ǹ���tbtest��key��hashֵ���е�˳����������

--��Ȼ��ͬʱluaҲ�ṩ�˰���key�Ĵ�С˳���������ģ�ע�⣬�Ǵ�С˳����Ȼ����key�����˳�����ֱ�����ʽ����for k,v in ipairs(tbtest) do��
--for k,v in ipairs(tbtest) do ������ѭ������Ҫ��tbtest�е�keyΪ˳��ģ����ұ����Ǵ�1��ʼ��ipairsֻ���1��ʼ��������key˳�������key������Ϊֹ��

tbtest = {  
[1] = 1,  
[2] = 2,  
[3] = 3,  
[5] = 5,  
["a"] = 6,  
["b"] = 7, 
} 
 
for k,v in ipairs(tbtest) do  
print("K:",k,"V:",v)  
end 
print("-----------------------------------------");

tbtest = {  
tbaaa = {  
[1] = 1,  
[2] = 2,  
[3] = 3,  
},  
["a"] = 4,  
["b"] = 5,  
} 
for k, v in pairs(tbtest) do  
print("k:",k,"v:" ,v)  
end 
print("-----------------------------------------");
--��ʵ��table�ж���һ��table�����table�����־���key����Ӧ��������ʵ��table�ĵ�ַ��
-----------------------------------------------------------------

ta = {1,2,a=nil,b=4,"d",nil,5}
--ta = {[1]=3,[2]=5,nil,nil}--��һ��nil��[1]��ֵΪnil���ڶ���nil��[2]��ֵΪnil�����������
--ta = {[2]=3,[3]=5,30,50}--���1,30;2,50;3,50��[]��ֵ�ᱻ����
--ta = {1,2,3,nil,nil}--���1,2,3,û��[]��ֵ�����ᱻ����
for i,v in pairs(ta) do
	 print("i ",i,"v ",v)
end
print("-----------------------------------------");
 for i,v in ipairs(ta) do
     print("i:",i,"v:",v)
end
print("-----------------------------------------");
a={"Hello","World";a=1,b=2,z=3,x=10,y=20;"Good","Bye"}  
--fjc:ipairs����[1]=nilֱ������
for i, v in ipairs(a) do  
    print(v)  
end 
print("-----------------------------------------");
for i, v in pairs(a) do  
    print(v)  
end 
print("-----------------------------------------");

if false==0 then
print("fasle==0",false);
else
print("false~=0",false);
end

function callf(str)
print("call ok "..str);
end

callf "fjc"

print("-----------------------------------------");


