# -*- coding: utf-8 -*-
"""
Created on Tue May 22 23:19:31 2018

@author: zhongqi
"""

#
#range() 函数
#range() 函数返回的是一个可迭代对象（类型是对象），而不是列表类型， 所以打印的时候不会打印列表。
#
## range()返回的是可迭代对象，每次循环返回一个
##print(i)			# 每次循环打印一次
#print(range(10))
#for i in range(10):
#    print(i)
#    
#dict1={'customer1':7, 'customer2':9, 'customer3':11}
#dict2={ key:value for key, value in dict1.items() if value>10 }  
#
#for i in dict2:
#    print(i)

#==============================================================================
# enumerate 函数
# 
# 传统的 for 循环
# i = 0  
# for value in collection:
#     # use value for something
#     i + = 1 
# 
# 优雅的 enumerate
# for i, value in enumerate(collection):  
#     # use value for something
# 
#==============================================================================
    
    
#==============================================================================
# # 读取文件
# import sys
# 
# input_file = sys.argv[1]
# 
# file_reader=open(input_file,'r',)
# 
# for row in file_reader:
#     print(row.strip())
#     
# file_reader.close()
#==============================================================================


#==============================================================================
# # with是一种上下文的管理协议，用于简化try…except…finally的处理流程。
# # 有一些任务，可能事先需要设置，事后做清理工作，with语句提供了一种非常方便的处理方式。
# # with 语句会在结束时，自动关闭文件。
# 
# import sys
# 
# with open(sys.argv[1], 'r') as file_reader:
#     for row in file_reader:
#         print((row.strip()))
#==============================================================================


#==============================================================================
# # 文件读写练习
# 
# import sys
# 
# input_file=sys.argv[1]
# output_file=sys.argv[2]
# 
# with open(output_file, 'w') as file_writer:
#     with open(input_file, 'r') as file_reader:
#         for i,row in enumerate(file_reader):
#             file_writer.write(str(i)+'\t'+row.strip()+'\n')
# 
# print('Ending...')
# 
#==============================================================================


#==============================================================================
# #导入 os 模块和 glob 模块，用于处理目录
# #import glob
# #import os
# #os.path.join 函数可以将一个或多个路径成分连接在一起
# #glob 模块可以找出与特定模式相匹配的所有路径名
# #os 模块和 glob 模块一起使用，可以找出符合特定模式的某文件夹下的所有文件
# 
# #import sys
# import os
# import glob
# 
# input_path='F:\Work\Python\exec\ch03' #sys.argv[1]
# 
# with open('all.txt', 'w') as file_writer:
#     for input_file in glob.glob(os.path.join(input_path, '*.txt')):
#         print(input_file)
#         with open(input_file, 'r') as file_reader:
#             for row in file_reader:
#                 file_writer.write(row.strip()+'\n')
# 
# print('Ending...')
#==============================================================================



#==============================================================================
# # 固定长度数据处理
# 
# # 文件样例：
# #50     Scandinavian Clothing A/S       NO
# #109    Petterson AB                    SE
# #316    Prime Sports Ltd                GB
# #755    Top Sports                      DK
# #772    AllSeasons Outdoor Clothing     US
# #798    Sportico                        ES
# #1280   British Sports Ltd              GB
# 
# 
# input_file='F:\Work\Python\exec\ch03\ch0301-supplier.txt'
# data1=[]
# 
# with open(input_file, 'r') as file_reader:
#     for row in file_reader:
#         str_row=row.strip()
#         f1=str_row[:7]
#         f2=str_row[7:39]
#         f3=str_row[39:]
#         data1.append([f1.strip(),f2.strip(),f3.strip()])
#         
# for row in enumerate(data1):
#     print(row)
# 
#==============================================================================


#==============================================================================
# # 固定分隔符数据处理
# 
# # # 文件样例：
# #"James Kvarniq" 4 M 27JUN1974 33 "31-45 years"
# #"Sandrina Stephano" 5 F 09JUL1979 28 "15-30 years"
# #"Karen Ballinger" 10 F 18OCT1984 23 "15-30 years"
# 
# 
# import sys
# import shlex # 用于处理双引号里面有分隔符的情况
# 
# input_file='F:\Work\Python\exec\ch03\ch0302-custus.txt'
# 
# data2=[]
# 
# with open(input_file,'r') as file_reader:
#         for row in file_reader:
#             data22=shlex.split(row.strip()) # shlex默认以空格为分割符，忽略引号里的空格
#             data2.append(data22)
# 
# for row in enumerate(data2):
#     print(row)
# 
# 
#==============================================================================


















