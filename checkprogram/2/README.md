README
-----
将自己写的数算2作业生成的`main.exe`（重命名一下）拷到文件目录下 
win8 64位系统可以直接执行`check.exe`  
其余的。。。自编译一下`check.cpp`，生成的.exe文件也要在此目录下  
运行`check.exe`
会生成5个r*.txt  和`result.txt`的文件，里面就是结果

-----
#结果说明
		1: Start Point 	Correct
		1: Data 	Correct
		1: Route 	Correct
		1: Stop Point 	Correct
		1: 0 steps 
前面的数字表示第几组测试数据  
如果有`File Wrong`则表示读取文件错误  
`Start Point`为起点，若起点不对则为`Wrong `   
`Data`为你的结果是否在原迷宫中为`‘0’`的判断 有错误就为`Wrong `   
`Route`为你的结果是否符合逻辑，两步之间的绝对值为`1 `有错误就为`Wrong `   

`Stop Point`为终点是否正确的判断  
`n steps`为你的结果比最短路径多几步

-----



以上
By [jas0n1ee](mailto:lijisheng@thuee25.cn)