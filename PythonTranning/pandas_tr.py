# -*- coding: utf-8 -*-
"""
Created on Sat May 26 11:15:52 2018

@author: zhongqi
"""

#==============================================================================
import pandas as pd
import os
 
work_dir=os.getcwd()
input_file = work_dir+'/Result-M.csv'
print(input_file)
 
#input_file='F:/Work/市场/培训/专业技能分享/Python培训/exec/ch05/Movie_Ratings.csv'
df_movie = pd.read_csv(input_file, encoding='utf-8', delimiter=',', error_bad_lines=False)

print(df_movie.columns)
print(df_movie.index)
print(df_movie.info())
#==============================================================================


#import pandas as pd
#import numpy as np
#import matplotlib.pyplot as plt


##df = pd.DataFrame(np.random.randn(10,4),index=pd.date_range('2018/12/18',
##   periods=10), columns=list('ABCD'))
##
##df.plot()
#
#df = pd.DataFrame(np.random.rand(10,4),columns=['a','b','c','d'])
##df.plot.bar()
#
#df.info()


#==============================================================================
# # Series的创建 
# # 通过一维数组创建序列
# arr1 = np.arange(10)
# print(arr1)
# print(type(arr1))
# s1 = pd.Series(arr1)
# print(s1)
# print(type(s1))
# 
# 
# # 通过字典的方式创建序列
# dic1 = {'a':10,'b':20,'c':30,'d':40,'e':50}
# type(dic1)
# s2 = pd.Series(dic1)
# s2
# type(s2)
# 
# #通过列表的方式创建序列
# list1 = ['a', 'd', 'c','f','g']
# s3 = pd.Series(list1)
# s3
# type(s3)
# 
#==============================================================================


#==============================================================================
# # DataFrame的创建
# 
# # 通过二维数据创建
# arr2 = np.array(np.arange(12)).reshape(4,3)
# print(arr2)
# print(type(arr2))
# df1=pd.DataFrame(arr2)
# print(df1)
# print(type(df1))
# 
# # 通过字典的方式创建数据框
# dic2 = {'a':[1,2,3,4],'b':[5,6,7,8],'c':[9,10,11,12],'d':[13,14,15,16]}
# print(dic2)
# print(type(dic2))
# df2 = pd.DataFrame(dic2)   # 以列为单位构建
# print(df2)
# print(type(df2))
# 
# 
# # 嵌套字典
# dic3 = {'one':{'a':1,'b':2,'c':3,'d':4},'two':{'a':5,'b':6,'c':7,'d':8},'three':{'a':9,'b':10,'c':11,'d':12}}
# print(dic3)
# print(type(dic3))
# df3 = pd.DataFrame(dic3)   # 以列为单位构建
# print(df3)
# print(type(df3))
# 
# # 以列为单位构建：最外面字典对应的是列，内嵌的字典是其中的索引和值。
# 
# # Series
# dic4 = {'one' : pd.Series([1., 2., 3.], index=['a', 'd', 'c']),'two' : pd.Series([5., 7., 6., 4.], index=['a', 'd', 'c', 'b'])}
# print(dic4)
# print(type(dic4))
# df4 = pd.DataFrame(dic4)   # 以列为单位构建
# print(df4)
# print(type(df4))
# ## 以列为单位构建：最外面字典对应的是列，内嵌的Series是其中的值。
# 
# # 字典构成的列表
# list5 = [{'one' : 1,'two':5},{'one' : 2,'two' : 6},{'one' : 3,'two' : 7},{'two' : 8}]
# print(list5)
# print(type(list5))
# df5 = pd.DataFrame(list5,index=['a','b','c','d'],columns=['one','two'])  # 以行为单位构建
# print(df5)
# print(type(df5))
# #以行为单位构建：指定索引和列名，内嵌的字典是其中的列名和值。
# 
# #通过数据框的方式创建数据框
# df6 = df3[['one','three']]	 # 取多列，则结果还是 DataFrame
# print(df6)
# print(type(df5))
# s3 = df3['one']	# 只取一列，则结果为 Series
# print(s3)
# print(type(s3))
# 
#==============================================================================


#==============================================================================
# # 索引
# #s = pd.Series([1,3,5,np.nan,6,8])
# #print(s)
# #print(s.index) # RangeIndex(start=0, stop=6, step=1)
# #
# ## 自定义索引标签
# #s.index=['a','b','c','d','e','f']
# #print(s[1])
# #print(s['b'])
# #
# #print(s[[1,3,5]])
# #print(s['b':'e'])
# 
# 
# # 通过索引自动对齐
# s5 = pd.Series( [10,15,20,30,55,80], index = ['a','b','c','d','e','f'])
# print(s5)
# s6 = pd.Series( [12,11,13,15,14,16], index = ['a','c','g','b','d','f'])
# print(s6)
# print(s5 + s6)
# print(s5 / s6)
#==============================================================================


## Pandas 数据查询
#Head()和tail()方法可以显示DataFrame前N条和后N条记录，N为对应的参数，默认值为5。这通常是拿到DataFrame后的第一个命令，可以方便的了解数据内容和含义。
#df3.head()
#df3.tail()
#
#index（行）和columns（列）属性，可以获得DataFrame的行和列的标签。这也是了解数据内容和含义的重要步骤。
#df3.index
#df3.columns
#
#values（值）属性，可以仅获得DataFrame的值。
#df3.values



























